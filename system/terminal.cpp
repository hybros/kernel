#include "terminal.hpp"
#include "system_asm.hpp"
#include "../std/memory.hpp"
using namespace kernel;
using namespace kernel::video;
using namespace kernel::std;

const char video::endl = '\n';

char kernel::term_reserved[sizeof(Terminal)];

Terminal::Terminal() : terminal_color(MakeColor(foreground::yellow, background::black)), terminal_standard_color(terminal_color), terminal_memory(reinterpret_cast<ushort*>(0xB8000)), terminal_num_base(dec)
{
//	DisableCursor();
//  MakeVgaEntry(terminal_blank, MakeColor(foreground::black, background::black));
//  Clear();
}

Terminal::~Terminal()
{
}

void Terminal::Clear()
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

ushort Terminal::MakeVgaEntry(char c, uchar color)
{
    ushort c16 = c;
    ushort color16 = color;
    return c16 | color16 << 8;
}

void Terminal::DisableCursor()
{
    WritePort<uchar>(0x3D4, 0x0A);
    WritePort<uchar>(0x3D5, 0x20);
}

void Terminal::UpdateCursor()
{
    uint tmp = terminal_y * 80 + terminal_x;
    // cursor LOW port to vga INDEX register
    WritePort<uchar>(0x3D4, 14);
    WritePort<uchar>(0x3D5, tmp >> 8);
    // cursor HIGH port to vga INDEX register
    WritePort<uchar>(0x3D4, 15);
    WritePort<uchar>(0x3D5, tmp);
}

void Terminal::Scroll()
{
//    uint tmp = terminal_y - VGA_WIDTH + 1;
//    memcpy(terminal_memory, terminal_buffer + tmp * 80, (25 - tmp) * 80 * 2);

    for(int i = 0 * 80; i < 24 * 80; i++)
        terminal_buffer[i] = terminal_memory[i] = terminal_buffer[i + 80];

    for(int i = 24 * 80; i < 25 * 80; i++)
        terminal_buffer[i] = terminal_memory[i] = MakeVgaEntry(' ', terminal_color);

    terminal_y--;
//   memsetw(terminal_buffer + (25 - tmp) * 80, terminal_blank, 80);
}

void Terminal::PutEntryAt(char c, uchar color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = terminal_memory[index] = MakeVgaEntry(c, color);
}

void Terminal::PutChar(char c)
{
    if(terminal_x >= 80)
    {
        terminal_x = 0;
        terminal_y++;
    }
    else if(terminal_y >= 25)
    {
        /*
        Clear();
        terminal_x = 0;
        terminal_y = 0;
        */
        Scroll();
    }
    else if(c == video::endl)
    {
        terminal_x = 0;
        terminal_y++;
        return;
    }

    UpdateCursor();
    PutEntryAt(c, terminal_color, terminal_x, terminal_y);
    terminal_x++;
}

void Terminal::WriteString(const char* string)
{
    size_t string_length = strlen(string);
    for(size_t i = 0; i < string_length; i++)
        PutChar(string[i]);
}

//template<typename T>
//void Terminal::WriteNumber(const T number, video::num_base base)
//{
//    char c[33];
//    char* s = ntoa(number, c, base);
//    WriteString(s);
//}

Terminal& Terminal::operator << (const foreground::color foreground_color)
{
    terminal_frgr_color = foreground_color;
    terminal_color = MakeColor(terminal_frgr_color, terminal_bagr_color);
    return *this;
}

Terminal& Terminal::operator << (const background::color background_color)
{
    terminal_bagr_color = background_color;
    terminal_color = MakeColor(terminal_frgr_color, terminal_bagr_color);
    return *this;
}

Terminal& Terminal::operator << (const NumberBase number_base)
{
    terminal_num_base = number_base;
    return *this;
}

Terminal& Terminal::operator << (const InfoLevel info)
{
    switch(info)
    {
    case kernel::check:
        terminal_color = MakeColor(foreground::light_grey, background::black);
        PutChar('[');
        terminal_color = MakeColor(foreground::yellow, background::black);
        WriteString("HYBROS");
        terminal_color = MakeColor(foreground::light_grey, background::black);
        PutChar(']');
        terminal_color = terminal_standard_color;
        break;
    case success:
        terminal_color = MakeColor(foreground::green, background::black);
        WriteString("[+] ");
        terminal_color = terminal_standard_color;
        break;
    case kernel::info:
        terminal_color = MakeColor(foreground::light_blue, background::black);
        WriteString("[|] ");
        terminal_color = terminal_standard_color;
        break;
    case warning:
        terminal_color = MakeColor(foreground::brown, background::black);
        WriteString("[!] ");
        terminal_color = terminal_standard_color;
        break;
    case error:
        terminal_color = MakeColor(foreground::red, background::black);
        WriteString("[-] ");
        terminal_color = terminal_standard_color;
        break;
    default:
        break;
    }
    return THIS;
}

Terminal& Terminal::operator << (const MathUnits unit)
{
    if(terminal_color == terminal_standard_color)
        terminal_color = MakeColor(foreground::blue, background::black);

    if((unit == BIT) || (unit == b))
        WriteString(" b");
    else if((unit == BYTE) || (unit == B))
        WriteString(" B");
    else if((unit == KILO_BYTE) || (unit == kB))
        WriteString(" kB");
    else if((unit == MEGA_BYTE) || (unit == MB))
        WriteString(" MB");
    else if((unit == GIGA_BYTE) || (unit == GB))
        WriteString(" GB");
    else if((unit == TERA_BYTE) || (unit == TB))
        WriteString(" TB");
    else {}
    return THIS;
}

Terminal& Terminal::operator << (const void *pointer)
{
    if(terminal_color == terminal_standard_color)
        terminal_color = MakeColor(foreground::green, background::black);

    WriteNumber(reinterpret_cast<ulong>(pointer), hex);
    return THIS;
}

Terminal& Terminal::operator << (const char c)
{
    if(terminal_color != terminal_standard_color)
        terminal_color = MakeColor(foreground::yellow, background::black);

    PutChar(c);
    return THIS;
}

Terminal& Terminal::operator << (const char *s)
{
    if(terminal_color != terminal_standard_color)
        terminal_color = MakeColor(foreground::yellow, background::black);

    WriteString(s);
    return THIS;
}

Terminal& Terminal::operator << (const String &s)
{
    if(terminal_color != terminal_standard_color)
        terminal_color = MakeColor(foreground::yellow, background::black);

    WriteString(s.GetString());
    return THIS;
}

