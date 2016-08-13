#ifndef __BIT_OPERATIONS__
#define __BIT_OPERATIONS__

#include <HStdTypes>
#include <HInteger>

namespace kernel
{

class HInteger;

// number: number to get its bit; bit: which bit to check

template<typename T>
inline bool IsBitSet(T number, const HInteger bit);

template<typename T>
inline void ClearBit(T &number, const HInteger bit);

template<typename T>
inline void ToggleBit(T &number, const HInteger bit);

template<typename T>
inline uchar GetBit(T number, const HInteger bit);

template<typename T>
inline void SetBit(T &number, const HInteger bit);

template<typename T>
inline T GetBits(T number, ulong mask, uint from);

template<typename T>
inline void SetBits(T &number, T value, ulong mask);

}

#endif
