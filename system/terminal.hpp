#ifndef __KERNEL_TERMINAL__
#define __KERNEL_TERMINAL__

#include "system_infos.hpp"
#include "../std/data_types.hpp"
#include "../std/helper.hpp"
#include "../std/math.hpp"
#include "../std/string.hpp"
#include "../std/memory.hpp"

namespace kernel
{
namespace video
{

namespace foreground
{

enum color
{
    black         = 0x00,
    blue          = 0x01,
    green         = 0x02,
    cyan          = 0x03,
    red           = 0x04,
    magenta       = 0x05,
    brown         = 0x06,
    light_grey    = 0x07,
    dark_grey     = 0x08,
    light_blue    = 0x09,
    light_green   = 0x0A,
    light_cyan    = 0x0B,
    light_red     = 0x0C,
    light_magenta = 0x0D,
    yellow        = 0x0E,
    white         = 0x0F
};

}

namespace background
{

enum color
{
    black         = 0x00,
    blue          = 0x01,
    green         = 0x02,
    cyan          = 0x03,
    red           = 0x04,
    magenta       = 0x05,
    rown          = 0x06,
    light_grey    = 0x07,
    dark_grey     = 0x08,
    light_blue    = 0x09,
    light_green   = 0x0A,
    light_cyan    = 0x0B,
    light_red     = 0x0C,
    light_magenta = 0x0D,
    yellow        = 0x0E,
    white         = 0x0F
};

}

extern const char endl;

}

#define KPANIC 0x88
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

extern char term_reserved[];

class DLL_PUBLIC Terminal
{
public:
    Terminal();
    ~Terminal();

    inline void  Clear();
    inline uchar MakeColor(video::foreground::color foreground_color, video::background::color background_color);
    inline void  SetColor(uchar color);
    inline void  PutEntryAt(char c, uchar color, size_t x, size_t y);
    inline void  PutChar(char c);

    void WriteString(const char* string);
    template<typename T> void WriteNumber(const T number, kernel::std::NumberBase base);

    inline Terminal &operator << (short  number);
    inline Terminal &operator << (int    number);
    inline Terminal &operator << (long long number);
    inline Terminal &operator << (uchar  number);
    inline Terminal &operator << (ushort number);
    inline Terminal &operator << (uint   number);
    inline Terminal &operator << (ulong  number);
    inline Terminal &operator << (size_t number);
    Terminal &operator << (const video::foreground::color foreground_color);
    Terminal &operator << (const video::background::color background_color);
    Terminal &operator << (const kernel::std::NumberBase number_base);
    Terminal &operator << (const kernel::InfoLevel info);
    Terminal &operator << (const std::MathUnits);
    Terminal &operator << (const void *pointer);
    Terminal &operator << (const char character);
    Terminal &operator << (const char *string);
    Terminal &operator << (const std::String &string);

protected:
    DLL_LOCAL inline ushort MakeVgaEntry(char c, uchar color);
    DLL_LOCAL inline void DisableCursor();
    DLL_LOCAL void UpdateCursor();
    DLL_LOCAL void Scroll();
    template<typename T> inline Terminal &HandleNumber(const T data);

private:
    DLL_LOCAL size_t  terminal_x, terminal_y;
    DLL_LOCAL uchar   terminal_color, terminal_standard_color, terminal_blank;
    DLL_LOCAL ushort* terminal_memory;
    DLL_LOCAL kernel::std::NumberBase terminal_num_base;
    DLL_LOCAL video::foreground::color terminal_frgr_color;
    DLL_LOCAL video::background::color terminal_bagr_color;
    DLL_LOCAL ushort terminal_buffer[2000];
};

// ~ Terminal

uchar Terminal::MakeColor(video::foreground::color foreground_color, video::background::color background_color)
{
    return foreground_color | background_color << 4;
}

void Terminal::SetColor(uchar color)
{
    terminal_color = color;
}

template<typename T>
void Terminal::WriteNumber(const T number, std::NumberBase base)
{
    char c[sizeof(T) * 8 + 1];
    char* s = std::ntoa<T>(number, c, base);
    WriteString(s);
}

template<typename T>
Terminal &Terminal::HandleNumber(const T data)
{
    if(terminal_color == terminal_standard_color)
        terminal_color = MakeColor(video::foreground::green, video::background::black);

    WriteNumber(data, terminal_num_base);
    return THIS;
}

Terminal& Terminal::operator << (short number)
{
    return HandleNumber(number);
}

Terminal& Terminal::operator << (int number)
{
    return HandleNumber(number);
}

Terminal& Terminal::operator << (long long number)
{
    return HandleNumber(number);
}

Terminal& Terminal::operator << (uchar number)
{
    return HandleNumber(number);
}

Terminal& Terminal::operator << (ushort number)
{
    return HandleNumber(number);
}

Terminal& Terminal::operator << (uint number)
{
    return HandleNumber(number);
}

Terminal& Terminal::operator << (ulong number)
{
    return HandleNumber(number);
}

Terminal& Terminal::operator << (size_t number)
{
    return HandleNumber(number);
}

}

#endif
