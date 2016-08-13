#include "../include/string.hpp"

#include <HStdHelper>

// based on itoa from http://stackoverflow.com/questions/3440726/what-is-the-proper-way-of-implementing-a-good-itoa-function
// answered by Minh Nguyen, edited by dodgy_coder
template<typename T>
auto IntegerToString(T number, char *string, int base) -> T
{
    bool sign_bin = (base == 2)                ? true : false;
    bool sign_dec = (base == 10 && number < 0) ? true : false;
    bool sign_hex = (base == 16)               ? true : false;

    ulong v = 0;                    /*(unsigned)*/
    if(sign_dec == true)
        v = -number;
    else
        v = number;                 /*(unsigned)*/

    char tmp[sizeof(T) * 8 + 1];                   // be careful with the length of the buffer
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

    *string++ = '\0';
    return (len++);
}

template<typename T>
auto ConvertToRawString(T number, uchar base) -> char *
{
    char *string = new char[sizeof(T) * 8 + 1];
    IntegerToString<T>(number, string, base);
    return string;
}

template<typename T>
auto ConvertToHString(T number, uchar base) -> HString
{
    char c_string[sizeof(T) * 8 + 1];
    IntegerToString<T>(number, c_string, base);
    return HString(c_string);
}

