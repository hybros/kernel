#include "../include/system_terminal.hpp"

#include <HSystemManager>
#include <cMemory>
#include <cString>

const uchar bin = 2;
const uchar oct = 8;
const uchar dec = 10;
const uchar hex = 16;

const char half = '\x80';
const char endl = '\n';


HSystem::Terminal::Terminal() :
    terminal_color(MakeColor(HForeground::YELLOW, HBackground::BLACK)),
    terminal_standard_color(terminal_color),
    terminal_memory(reinterpret_cast<ushort*>(0xB8000)),
    terminal_num_base(dec)
{
//	DisableCursor();
//  MakeVgaEntry(terminal_blank, MakeColor(foreground::black, background::black));
//  Clear();
}

//HSystem::Terminal::~Terminal()
//{
//}

void HSystem::Terminal::Clear()
{
    for(size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for(size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = terminal_memory[index] = MakeVgaEntry(' ', terminal_color);
        }
    }
}

ushort HSystem::Terminal::MakeVgaEntry(char c, uchar color)
{
    ushort c16 = c;
    ushort color16 = color;
    return c16 | (color16 << 8);
}

uchar HSystem::Terminal::MakeColor(HForeground foreground_color, HBackground background_color)
{
    return static_cast<uchar>(foreground_color) | static_cast<uchar>(background_color) << 4;
}

void HSystem::Terminal::SetColor(uchar color)
{
    terminal_color = color;
}

void HSystem::Terminal::DisableCursor()
{
    WritePort<uchar>(0x3D4, 0x0A);
    WritePort<uchar>(0x3D5, 0x20);
}

void HSystem::Terminal::UpdateCursor()
{
    uint tmp = terminal_y * 80 + terminal_x;
    // cursor LOW port to vga INDEX register
    WritePort<uchar>(0x3D4, 14);
    WritePort<uchar>(0x3D5, tmp >> 8);
    // cursor HIGH port to vga INDEX register
    WritePort<uchar>(0x3D4, 15);
    WritePort<uchar>(0x3D5, tmp);
}

void HSystem::Terminal::Scroll()
{
//    uint tmp = terminal_y - VGA_WIDTH + 1;
//    memcpy(terminal_memory, terminal_buffer + tmp * 80, (25 - tmp) * 80 * 2);

    for(int i = 0 * 80; i < (24 * 80); i++)
        terminal_buffer[i] = terminal_memory[i] = terminal_buffer[i + 80];

    for(int i = 24 * 80; i < (25 * 80); i++)
        terminal_buffer[i] = terminal_memory[i] = MakeVgaEntry(' ', terminal_color);

    terminal_y--;
//   memsetw(terminal_buffer + (25 - tmp) * 80, terminal_blank, 80);
}

void HSystem::Terminal::PutEntryAt(char c, uchar color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = terminal_memory[index] = MakeVgaEntry(c, color);
}

void HSystem::Terminal::PutChar(char c)
{
    if((terminal_x >= 80) || (c == endl))
    {
        terminal_x = 0;
        terminal_y++;
        return;
    }
    else if(terminal_y >= 25)
    {
        Scroll();
    }
    else if((c == half) && (terminal_x < half))
    {
        terminal_x = 40;
        return;
    }

    UpdateCursor();
    PutEntryAt(c, terminal_color, terminal_x, terminal_y);
    terminal_x++;
}

void HSystem::Terminal::WriteString(const char* string)
{
    for(size_t i = 0; i < strlen(string); i++)
        PutChar(string[i]);
}

void HSystem::Terminal::WriteString(const char* string, size_t string_length)
{
    for(size_t i = 0; i < string_length; i++)
        PutChar(string[i]);
}

void HSystem::Terminal::WriteString(const HString &string)
{
    for(size_t i = 0; i < string.GetLength(); i++)
        PutChar(string[i]);
}

void HSystem::Terminal::WriteNumber(const ulong number, uchar base)
{
    if(terminal_color == terminal_standard_color)
        terminal_color = MakeColor(HForeground::GREEN, HBackground::BLACK);

    char string[sizeof(ulong) * 8 + 1];
    size_t length = IntegerToString(number, string, base);
    WriteString(string, length);
}

HTerminal& HSystem::Terminal::operator << (const HForeground foreground_color)
{
    terminal_frgr_color = foreground_color;
    terminal_color = MakeColor(terminal_frgr_color, terminal_bagr_color);
    return *this;
}

HTerminal& HSystem::Terminal::operator << (const HBackground background_color)
{
    terminal_bagr_color = background_color;
    terminal_color = MakeColor(terminal_frgr_color, terminal_bagr_color);
    return *this;
}

HTerminal &HSystem::Terminal::operator <<(const uchar &number_base)
{
    terminal_num_base = number_base;
    return THIS;
}

HTerminal& HSystem::Terminal::operator << (const HInfoLevel info)
{
    switch(info)
    {
    case CHECK:
        terminal_color = MakeColor(HForeground::LIGHT_GREY, HBackground::BLACK);
        PutChar('[');
        terminal_color = MakeColor(HForeground::YELLOW, HBackground::BLACK);
        WriteString("HYBROS");
        terminal_color = MakeColor(HForeground::LIGHT_GREY, HBackground::BLACK);
        PutChar(']');
        terminal_color = terminal_standard_color;
        break;
    case SUCC:
        terminal_color = MakeColor(HForeground::GREEN, HBackground::BLACK);
        PutChar('[');
        PutChar('+');
        PutChar(']');
        PutChar(' ');
        terminal_color = terminal_standard_color;
        break;
    case INFO:
        terminal_color = MakeColor(HForeground::LIGHT_BLUE, HBackground::BLACK);
        PutChar('[');
        PutChar('I');
        PutChar(']');
        PutChar(' ');
        terminal_color = terminal_standard_color;
        break;
    case WARN:
        terminal_color = MakeColor(HForeground::BROWN, HBackground::BLACK);
        PutChar('[');
        PutChar('!');
        PutChar(']');
        PutChar(' ');
        terminal_color = terminal_standard_color;
        break;
    case ERROR:
        terminal_color = MakeColor(HForeground::RED, HBackground::BLACK);
        PutChar('[');
        PutChar('-');
        PutChar(']');
        PutChar(' ');
        terminal_color = terminal_standard_color;
        break;
    default:
        break;
    }
    return THIS;
}

HTerminal& HSystem::Terminal::operator << (const HMathUnits unit)
{
    if(terminal_color == terminal_standard_color)
        terminal_color = MakeColor(HForeground::BLUE, HBackground::BLACK);

    if((unit == BIT) || (unit == b))
    {
        PutChar(' ');
        PutChar('b');
    }
    else if((unit == BYTE) || (unit == B))
    {
        PutChar(' ');
        PutChar('B');
    }
    else if((unit == KILO_BYTE) || (unit == kB))
    {
        PutChar(' ');
        PutChar('k');
        PutChar('B');
    }
    else if((unit == MEGA_BYTE) || (unit == MB))
    {
        PutChar(' ');
        PutChar('M');
        PutChar('B');
    }
    else if((unit == GIGA_BYTE) || (unit == GB))
    {
        PutChar(' ');
        PutChar('G');
        PutChar('B');
    }
    else if((unit == TERA_BYTE) || (unit == TB))
    {
        PutChar(' ');
        PutChar('T');
        PutChar('B');
    }

    return THIS;
}

HTerminal& HSystem::Terminal::operator <<(const ulong number)
{
    WriteNumber(number, terminal_num_base);
    return THIS;
}

auto HSystem::Terminal::operator <<(const uint16 number) -> HTerminal &
{
    WriteNumber(number, terminal_num_base);
    return THIS;
}

auto HSystem::Terminal::operator <<(const uint32 number) -> HTerminal &
{
    WriteNumber(number, terminal_num_base);
    return THIS;
}

auto HSystem::Terminal::operator <<(const uint64 number) -> HTerminal &
{
    WriteNumber(number, terminal_num_base);
    return THIS;
}

HTerminal& HSystem::Terminal::operator << (const void *pointer)
{
    WriteNumber(reinterpret_cast<ulong>(pointer), hex);
    return THIS;
}

HTerminal& HSystem::Terminal::operator << (const char c)
{
    if(terminal_color != terminal_standard_color)
        terminal_color = MakeColor(HForeground::YELLOW, HBackground::BLACK);

    PutChar(c);
    return THIS;
}

HTerminal& HSystem::Terminal::operator << (const char *s)
{
    if(terminal_color != terminal_standard_color)
        terminal_color = MakeColor(HForeground::YELLOW, HBackground::BLACK);

    WriteString(s);
    return THIS;
}

HTerminal& HSystem::Terminal::operator << (const HString &s)
{
    if(terminal_color != terminal_standard_color)
        terminal_color = MakeColor(HForeground::YELLOW, HBackground::BLACK);

    WriteString(s);
    return THIS;
}

