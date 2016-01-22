#ifndef __BIT_OPERATIONS__
#define __BIT_OPERATIONS__

#include <HStdTypes>

// number: number to get its bit; bit: which bit to check

template<typename T>
auto IsBitSet(T number, ulong bit) -> bool;

template<typename T>
void ClearBit(T &number, ulong bit);

template<typename T>
void ToggleBit(T &number, ulong bit);

template<typename T>
auto GetBit(T number, ulong bit) -> T;

template<typename T>
void SetBit(T &number, ulong bit);

template<typename T>
auto AreBitsSet(T number, ulong mask) -> bool;

template<typename T>
auto AreBitsSet(T number, uint from_bit, uint to_bit) -> bool;

template<typename T>
void ClearBits(T &number, ulong mask);

template<typename T>
void ClearBits(T &number, uint from_bit, uint to_bit);

template<typename T>
auto GetBits(T number, ulong mask) -> T;

template<typename T>
auto GetBits(T number, uint from_bit, uint to_bit) -> T;

template<typename T>
void SetBits(T &number, ulong mask, ulong value);

template<typename T>
void SetBits(T &number, uint from_bit, uint to_bit, ulong value);

template<typename T>
constexpr auto MakeBitMap(uint from_bit, uint to_bit) -> T;

#endif
