#ifndef __KERNEL_TERMINAL__
#define __KERNEL_TERMINAL__

#include <HSystem>
#include <HTerminal>

extern const uchar bin;
extern const uchar oct;
extern const uchar dec;
extern const uchar hex;

extern const char endl;

#define KPANIC 0x88
#define VGA_WIDTH  80
#define VGA_HEIGHT 25

class HSystem::Terminal : public HTerminal
{
public:
    Terminal();
    ~Terminal() = default;

    void Clear();
    auto MakeColor(HForeground foreground_color, HBackground background_color) -> uchar;
    void SetColor(uchar color);
    void PutEntryAt(char c, uchar color, size_t x, size_t y);
    void PutChar(char c);

    void WriteString(const char *string);
    void WriteString(const char *string, size_t string_length);
    void WriteString(const HString &string);
    void WriteNumber(const ulong number, uchar base);

    HTerminal &operator <<(const HForeground foreground_color);
    HTerminal &operator <<(const HBackground background_color);
    HTerminal &operator <<(const uchar &number_base);
    HTerminal &operator <<(const HInfoLevel info);
    HTerminal &operator <<(const HMathUnits);
    HTerminal &operator <<(const char character);
    HTerminal &operator <<(const char *string);
    HTerminal &operator <<(const HString &string);
    HTerminal &operator <<(const void *pointer);
    HTerminal &operator <<(const ulong number);
    auto operator <<(const uint16 number) -> HTerminal &;
    auto operator <<(const uint32 number) -> HTerminal &;
    auto operator <<(const uint64 number) -> HTerminal &;

protected:
    auto MakeVgaEntry(char c, uchar color) -> ushort;
    void DisableCursor();
    void UpdateCursor();
    void Scroll();
    template<typename T> inline HTerminal &HandleNumber(const T data);

private:
    size_t  terminal_x, terminal_y;
    uchar   terminal_color, terminal_standard_color, terminal_blank;
    ushort* terminal_memory;
    uchar terminal_num_base;
    HForeground terminal_frgr_color;
    HBackground terminal_bagr_color;
    ushort terminal_buffer[2000];
};


#endif
