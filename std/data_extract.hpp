#ifndef __DATA_EXTRACTOR__
#define __DATA_EXTRACTOR__

#include "bits.hpp"

namespace kernel
{
namespace std DLL_PUBLIC
{

template<class R, typename T, T R::* P>
inline T& ExtractData(R &object)
{
    return object.*P;
}

template<class R, typename T, T R::* P>
inline T& ExtractData(R *object)
{
    return object->*P;
}

template<typename T>
inline uchar ExtractByte(T value, uint byte_number)      // byte_number: Starting by 0
{
    GetBits<T>(value, 0xFF, byte_number * 8);
}

template<typename T>
inline ushort ExtractWord(T value, uint word_number)     // word_number: Starting by 0
{
    GetBits<T>(value, 0xFFFF, word_number * 16);
}

template<typename T>
inline uint ExtractDword(T value, uint dword_number)     // dword_number: Starting by 0
{
    GetBits<T>(value, 0xFFFFFFFF, dword_number * 32);
}

template<typename T, typename R>
inline constexpr T Extract(R value, uint position)
{
    switch(sizeof(T))
    {
    case sizeof(uchar):
        return ExtractByte<R>(value, position);
    case sizeof(ushort):
        return ExtractWord<R>(value, position);
    case sizeof(uint):
        return ExtractDword<R>(value, position);
    default:
        break;
    }
    return 0;
}

}
}

#endif
