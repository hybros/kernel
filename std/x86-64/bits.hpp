#ifndef __X86_64__BIT_FUNCTIONS__
#define __X86_64__BIT_FUNCTIONS__

#include "../data_types.hpp"

namespace kernel
{
namespace std
{

inline bool IsBitSet(ulong number, uint bit)
{
    return (number & (1ULL << bit)) != 0;
}

inline void ClearBit(ulong &number, uint bit)
{
    number &= ~(1ULL << bit);
}

inline void ToggleBit(ulong &number, uint bit)
{
    number ^= 1ULL << bit;
}

inline uchar GetBit(ulong number, uint bit)
{
    return number & (1ULL << bit);
}

inline void SetBit(ulong &number, uint bit)
{
    number |= 1ULL << bit;
}

}
}

#endif
