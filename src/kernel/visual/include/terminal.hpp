#ifndef __TERMINAL_INTERFACE__
#define __TERMINAL_INTERFACE__

#include <HSystemManager>
#include <HStdTypes>
#include <HString>
#include <HSystemInfos>
#include <HStdMath>

extern const uchar bin;
extern const uchar oct;
extern const uchar dec;
extern const uchar hex;

extern const char half;
extern const char endl;

enum class HForeground : uchar
{
    BLACK         = 0x00,
    BLUE          = 0x01,
    GREEN         = 0x02,
    CYAN          = 0x03,
    RED           = 0x04,
    MAGENTA       = 0x05,
    BROWN         = 0x06,
    LIGHT_GREY    = 0x07,
    DARK_GREY     = 0x08,
    LIGHT_BLUE    = 0x09,
    LIGHT_GREEN   = 0x0A,
    LIGHT_CYAN    = 0x0B,
    LIGHT_RED     = 0x0C,
    LIGHT_MAGENTA = 0x0D,
    YELLOW        = 0x0E,
    WHITE         = 0x0F
};

enum class HBackground : uchar
{
    BLACK         = 0x00,
    BLUE          = 0x01,
    GREEN         = 0x02,
    CYAN          = 0x03,
    RED           = 0x04,
    MAGENTA       = 0x05,
    BROWN         = 0x06,
    LIGHT_GREY    = 0x07,
    DARK_GREY     = 0x08,
    LIGHT_BLUE    = 0x09,
    LIGHT_GREEN   = 0x0A,
    LIGHT_CYAN    = 0x0B,
    LIGHT_RED     = 0x0C,
    LIGHT_MAGENTA = 0x0D,
    YELLOW        = 0x0E,
    WHITE         = 0x0F
};

#define KPANIC 0x88
#define VGA_WIDTH  80
#define VGA_HEIGHT 25


class HTerminal : public HSystem::Manager
{
public:
    inline HTerminal();

    virtual void WriteString(const char* string) = 0;
    virtual void WriteString(const HString &string) = 0;
    virtual void WriteNumber(const ulong number, uchar base) = 0;

    virtual auto operator <<(const HForeground foreground_color) -> HTerminal & = 0;
    virtual auto operator <<(const HBackground background_color) -> HTerminal & = 0;
    virtual auto operator <<(const uchar &number_base) -> HTerminal & = 0;
    virtual auto operator <<(const HInfoLevel info) -> HTerminal & = 0;
    virtual auto operator <<(const HMathUnits) -> HTerminal & = 0;
    inline virtual auto operator <<(const char character) -> HTerminal &;
    inline virtual auto operator <<(const char *string) -> HTerminal &;
    inline virtual auto operator <<(const HString &string) -> HTerminal &;
    inline virtual auto operator <<(const void *pointer) -> HTerminal &;
    inline virtual auto operator <<(const uint16 number) -> HTerminal &;
    inline virtual auto operator <<(const uint32 number) -> HTerminal &;
    inline virtual auto operator <<(const uint64 number) -> HTerminal &;
    inline virtual auto operator <<(const size_t number) -> HTerminal &;
};

#endif
