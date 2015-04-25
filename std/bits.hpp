#ifndef __BIT_OPERATIONS__
#define __BIT_OPERATIONS__

#include "data_types.hpp"
#include "helper.hpp"
#ifdef __x86_64
#include "x86-64/bits.hpp"
#endif

namespace kernel
{
namespace std DLL_PUBLIC
{

// number: number to get its bit; bit: which bit to check

template<typename T>
inline bool IsBitSet(T number, uint bit)
{
    return (number & (1 << bit)) != 0;
}

template<typename T>
inline void ClearBit(T &number, uint bit)
{
    number &= ~(1 << bit);
}

template<typename T>
inline void ToggleBit(T &number, uint bit)
{
    number ^= 1 << bit;
}

template<typename T>
inline uchar GetBit(T number, uint bit)
{
    return number & (1 << bit);
}

template<typename T>
inline void SetBit(T &number, uint bit)
{
    number |= 1 << bit;
}

template<typename T>
inline T GetBits(T number, ulong mask, uint from)
{
    return (number & mask) >> from;
}

template<typename T>
inline void SetBits(T &number, T value, ulong mask)
{
    number = (number & ~mask) | value;
}

}
}

#endif
