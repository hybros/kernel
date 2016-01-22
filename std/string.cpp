#include "string.hpp"
#include "memory.hpp"
using namespace kernel::std;

size_t strlen(const char *str)
{
    size_t count = 0;
    while(str[count] != '\0')
        count++;
    return count;
}

char *strcpy(char *destination, const char *source)
{
    while((*destination++ = *source++) != '\0');
    return destination;
}

char *strcpy_s(char *destination, const char *source, size_t length)
{
    while(length--)
    {
        *destination++ = *source++;
    }
    return destination;
}

char *strcat(char *destination, const char *source)
{
    while(*destination != '\0')
        *destination++;

    do
    {
        *destination++ = *source++;
    }
    while(*source != '\0');
}

char* itoa(int number, char *string, int base)
{
    int length = IntegerToString(number, string, base);
    string[length++] = '\0';
    return string;
}

// ~ String

String::~String()
{
    if(string_pointer !=  nullptr)
        delete string_pointer;
}

String &String::Append(const char append)
{
    if(string_size > string_length)
        string_pointer[string_length++] = append;
    else
    {
        string_pointer = CreateNewBuffer(string_size + 2);
        string_pointer[string_length++] = append;
    }
}

String &String::Append(const char *append)
{
    if(append == nullptr)
        return THIS;

    size_t append_length = strlen(append);
    if(string_size > append_length)
        memcpy(string_pointer + string_length, append, append_length);
    else
    {
        string_pointer = CreateNewBuffer(string_size + append_length + 1);
        memcpy(string_pointer + string_length, append, append_length);
    }
    string_length += append_length;
    return THIS;
}

String &String::Append(const String &append)
{
    size_t append_length = append.GetLength();
    if(string_size > append_length)
        memcpy(string_pointer + string_length, append.GetString(), append_length);
    else
    {
        string_pointer = CreateNewBuffer(string_size + append_length + 1);
        memcpy(string_pointer + string_length, append.GetString(), append_length);
    }
    string_length += append_length;
    return THIS;
}

size_t String::CopyString(char *destination, const char *source, size_t length)
{
    if(destination == nullptr || source == nullptr)
            return 0;

    if(length > 0)
        strcpy_s(destination, source, length);

    return length;
}

size_t String::CopyString(String &destination, const String &source)
{
    if(source.GetLength() > destination.GetSize() || destination.GetString() == nullptr || source.GetString() == nullptr)
            return 0;

    strcpy_s(destination.GetString(), source.GetString(), source.GetLength());
}

char String::operator [] (const uint position)
{
    if(string_pointer != nullptr)
        return string_pointer[position];
    else
        return ' ';
}

void String::operator = (const char character)
{
    string_length = 1;
    string_size = 1;
    string_pointer = new char[1];
    string_pointer[0] = character;
}

void String::operator = (const char *string)
{
    if(string == nullptr)
        return;

    if(string_pointer)
        delete string_pointer;

    string_length = strlen(string);
    string_size = string_length + 1;
    string_pointer = new char[string_size];
    CopyString(string_pointer, string, string_length);
}

void String::operator = (const String &string)
{
    string_pointer = string.GetString();
    string_size = string.GetSize();
    string_length = string.GetLength();
}

char *String::CreateNewBuffer(size_t size)
{
    string_size = size;
    char *tmp = new char[string_size];
    memcpy(tmp, string_pointer, string_size);
    delete string_pointer;
    return tmp;
}
