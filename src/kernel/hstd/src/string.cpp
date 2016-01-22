#include "../include/string.hpp"

#include <cMemory>
#include <cString>
#include <HStdHelper>

char a_byte_of_nothing = ' ';

extern "C" size_t strlen(const char *str)
{
    size_t length = 0;
    while(*str++ != '\0')
        length++;
    return length;
}

// ~ HString

HString::HString() : string_pointer(nullptr), string_size(0), string_length(0) {}

HString::HString(const char character)
{
    CopyFrom(character);
}

HString::HString(const char *string)
{
    CopyFrom(string);
}

HString::HString(const HString &string)
{
    CopyFrom(string);
}

HString::HString(HString &&string) : string_pointer(string.GetUnicodeString()), string_size(string.GetSize()), string_length(string.GetLength())
{
    string.Free();
}

HString::~HString()
{
    Free();
}

auto HString::IsEmpty() const -> bool
{
    if(string_pointer == nullptr || string_length == 0)
        return true;
    else
        return false;
}

auto HString::GetSize() const -> size_t
{
    return string_size;
}

auto HString::GetSize(const char *other_string) const -> size_t
{
    return GetLength(other_string);
}

auto HString::GetLength() const -> size_t
{
    return string_length;
}

auto HString::GetLength(const char *other_string) const -> size_t
{
    return strlen(other_string);
}

auto HString::GetUnicodeString() const -> char *
{
    return string_pointer;
}

void HString::Free()
{
    if(string_pointer !=  nullptr)
        delete string_pointer;

    string_length = 0;
    string_size = 0;
}

auto HString::CopyFrom(const char character) -> bool
{
    Free();

    string_pointer = new char[1];
    string_pointer[0] = character;
    string_length = 1;
    string_size = 1;
    return true;
}

auto HString::CopyFrom(const char *string) -> bool
{
    if(string == nullptr)
        return false;

    Free();

    string_size = GetSize(string);
    string_length = GetLength(string);
    string_pointer = new char[string_size];
    memcpy(string_pointer, string, string_size);
    return true;
}

auto HString::CopyFrom(const HString &string) -> bool
{
    if(string.IsEmpty() == true)
        return false;

    Free();

    string_size = string.GetSize();
    string_length = string.GetLength();
    string_pointer = new char[string_size];
    memcpy(string_pointer, string.GetUnicodeString(), string_size);
    return true;
}

auto HString::MoveFrom(char *string) -> bool
{
    if(string == nullptr)
        return false;

    Free();

    string_size = GetSize(string);
    string_length = GetLength(string);
    string_pointer = string;
    return true;
}

auto HString::MoveFrom(HString &string) -> bool
{
    if(string.IsEmpty() == true)
        return false;

    Free();

    string_size = string.GetSize();
    string_length = string.GetLength();
    string_pointer = string.GetUnicodeString();

    string.Free();
    return true;
}

auto HString::Append(const char append) -> HString &
{
    if((string_size + 1) >= string_size)
        string_pointer[string_length++] = append;
    else
    {
        string_pointer = CreateNewBuffer(string_size + 2);
        string_pointer[string_length++] = append;
    }
    return THIS;
}

auto HString::Append(const char *append) -> HString &
{
    if(append == nullptr)
        return THIS;

    size_t append_size = GetSize(append);
    if((string_size + append_size) >= append_size)
        memcpy(string_pointer + string_size, append, append_size);
    else
    {
        string_pointer = CreateNewBuffer(string_size + append_size + 1);
        memcpy(string_pointer + string_size, append, append_size);
    }

    string_size += append_size;
    return THIS;
}

auto HString::Append(const HString &append) -> HString &
{
    size_t append_size = append.GetSize();
    if((string_size + append_size) >= append_size)
        memcpy(string_pointer + string_size, append.GetUnicodeString(), append_size);
    else
    {
        string_pointer = CreateNewBuffer(string_size + append_size + 1);
        memcpy(string_pointer + string_size, append.GetUnicodeString(), append_size);
    }

    string_size += append_size;
    return THIS;
}

auto HString::operator = (const char character) -> HString &
{
    CopyFrom(character);
    return THIS;
}

auto HString::operator = (const char *string) -> HString &
{
    CopyFrom(string);
    return THIS;
}

auto HString::operator = (const HString &string) -> HString &
{
    CopyFrom(string);
    return THIS;
}

auto HString::operator [] (const size_t position) -> char &
{
    if(string_pointer != nullptr)
        return string_pointer[position];
    else
        return a_byte_of_nothing;
}

auto HString::operator [] (const size_t position) const -> char
{
    if(string_pointer != nullptr)
        return string_pointer[position];
    else
        return a_byte_of_nothing;
}

void HString::operator += (const char append)
{
    Append(append);
}

void HString::operator += (const char *append)
{
    Append(append);
}

void HString::operator += (const HString &append)
{
    Append(append);
}

auto HString::operator + (const char character) -> HString
{
    HString new_string(THIS);
    new_string.Append(character);
    return new_string;
}

auto HString::operator + (const char *string) -> HString
{
    HString new_string(THIS);
    new_string.Append(string);
    return new_string;
}

auto HString::operator + (const HString &string) -> HString
{
    HString new_string(THIS);
    new_string.Append(string);
    return new_string;
}

char *HString::CreateNewBuffer(size_t size)
{
    string_size = size;
    char *tmp = new char[string_size];
    memcpy(tmp, string_pointer, string_size);
    delete string_pointer;
    return tmp;
}
