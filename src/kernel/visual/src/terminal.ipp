#include "../include/terminal.hpp"

HTerminal::HTerminal() : HManager(HManager::TERMINAL) {}

HTerminal &HTerminal::operator <<(const char character)
{
    WriteString(character);
    return *this;
}

HTerminal &HTerminal::operator <<(const char *string)
{
    WriteString(string);
    return *this;
}

HTerminal &HTerminal::operator <<(const HString &string)
{
    WriteString(string);
    return *this;
}

HTerminal &HTerminal::operator <<(const void *pointer)
{
    WriteNumber(reinterpret_cast<ulong>(pointer), hex);
    return *this;
}

HTerminal &HTerminal::operator <<(const uint16 number)
{
    WriteNumber(number, dec);
    return *this;
}

HTerminal &HTerminal::operator <<(const uint32 number)
{
    WriteNumber(number, dec);
    return *this;
}

HTerminal &HTerminal::operator <<(const uint64 number)
{
    WriteNumber(number, dec);
    return *this;
}

HTerminal &HTerminal::operator <<(const size_t number)
{
    WriteNumber(number, dec);
    return *this;
}
