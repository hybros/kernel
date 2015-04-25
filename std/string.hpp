#ifndef __STRING_MANIPULATION_FUNCTIONS__
#define __STRING_MANIPULATION_FUNCTIONS__

#include "data_types.hpp"
#include "helper.hpp"

extern "C"
{

DLL_PUBLIC size_t strlen(const char *str);
DLL_PUBLIC char *strcpy(char *destination, const char *source);
DLL_PUBLIC char *strcpy_s(char *destination, const char *source, size_t length);
DLL_PUBLIC char *strcat(char *destination, const char *source);
DLL_PUBLIC char *itoa(int number, char *string, int base);

}

namespace kernel
{
namespace std DLL_PUBLIC
{

class String
{
public:
    inline String();
    DLL_LOCAL inline String(void *memory_address, size_t size);                   // INFO: Dangerous!
    inline String(const char character);
    inline String(const char *string);
    inline String(const String &string);
    ~String();

    String &Append(const char append);
    String &Append(const char *append);
    String &Append(const String &append);

    static size_t CopyString(char *destination, const char *source, size_t length);
    static size_t CopyString(String &destination, const String &source);

    inline size_t GetSize() const;
    inline size_t GetLength() const;
    inline char *GetString() const;

    char operator [] (const uint position);

    void operator = (const char source);
    void operator = (const char *source);
    void operator = (const String &source);

    inline void operator += (const char append);
    inline void operator += (const char *append);
    inline void operator += (const String &append);

    inline String operator + (const char character);
    inline String operator + (const char *string);
    inline String operator + (const String &string);

protected:
    char *CreateNewBuffer(size_t size);

private:
    char *string_pointer;
    size_t string_size;
    size_t string_length;
};

// # IntegerToString

// based on itoa from http://stackoverflow.com/questions/3440726/what-is-the-proper-way-of-implementing-a-good-itoa-function
// answered by Minh Nguyen, edited by dodgy_coder
template<typename T>
inline T IntegerToString(T number, char *string, int base)
{
    bool sign_bin = (base == 2)                ? true : false;
    bool sign_dec = (base == 10 && number < 0) ? true : false;
    bool sign_hex = (base == 16)               ? true : false;

    ulong v = 0;                    /*(unsigned)*/
    if(sign_dec == true)
        v = -number;
    else
        v = number;                 /*(unsigned)*/

    char tmp[33];                   // be careful with the length of the buffer
    char *tp = tmp;
    while(v || tp == tmp)
    {
        T i = v % base;
        v /= base;
        if(i < 10)
          *tp++ = i + '0';
        else
          *tp++ = i + 'A' - 10;
    }

    T len = tp - tmp;

    if(sign_dec == true)
    {
        *string++ = '-';
        len++;
    }
    else if(sign_hex == true)
    {
        *string++ = '0';
        *string++ = 'x';
        len += 2;
    }

    while(tp > tmp)
        *string++ = *--tp;

    if(sign_bin == true)
    {
        *string++ = 'b';
        len++;
    }

    return len;
}

// # ntoa

template<typename T>
char* ntoa(T number, char *string, int base)
{
    T length = IntegerToString<T>(number, string, base);
    string[length++] = '\0';
    return string;
}

// ~ String

String::String() : string_pointer(nullptr), string_size(0), string_length(0) {}

String::String(void *memory_address, size_t size) : string_size(size), string_length(0)
{
    if(memory_address != nullptr)
        string_pointer = reinterpret_cast<char*>(memory_address);
}

String::String(const char character)
{
    this->operator = (character);
}

String::String(const char *string)
{
    this->operator = (string);
}

String::String(const String &string)
{
    this->operator = (string);
}

size_t String::GetSize() const
{
    return string_size;
}

size_t String::GetLength() const
{
    return string_length;
}

char *String::GetString() const
{
    return string_pointer;
}

void String::operator += (const char append)
{
    Append(append);
}

void String::operator += (const char *append)
{
    Append(append);
}

void String::operator += (const String &append)
{
    Append(append);
}

String String::operator + (const char character)
{
    String new_string(THIS);
    new_string.Append(character);
    return new_string;
}

String String::operator + (const char *string)
{
    String new_string(THIS);
    new_string.Append(string);
    return new_string;
}

String String::operator + (const String &string)
{
    String new_string(THIS);
    new_string.Append(string);
    return new_string;
}

}
}

#endif
