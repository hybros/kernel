#include "../include/bits.hpp"

// number: number to get its bit; bit: which bit to check

template<typename T>
auto IsBitSet(T number, ulong bit) -> bool
{
    return (number & (1 << bit)) != 0;
}

template<typename T>
void ClearBit(T &number, ulong bit)
{
    number &= ~(1 << bit);
}

template<typename T>
void ToggleBit(T &number, ulong bit)
{
    number ^= 1 << bit;
}

template<typename T>
auto GetBit(T number, ulong bit) -> T
{
    return number & (1 << bit);
}

template<typename T>
void SetBit(T &number, ulong bit)
{
    number |= 1 << bit;
}

template<typename T>
auto AreBitsSet(T number, ulong mask) -> bool
{
	return (number & mask) != 0;
}

template<typename T>
auto AreBitsSet(T number, uint from_bit, uint to_bit) -> bool
{
	return (number & MakeBitMap<T>(from_bit, to_bit)) != 0;
}

template<typename T>
void ClearBits(T &number, ulong mask)
{
	number &= ~mask;
}

template<typename T>
void ClearBits(T &number, uint from_bit, uint to_bit)
{
	number &= ~MakeBitMap<T>(from_bit, to_bit);
}

template<typename T>
auto GetBits(T number, ulong mask) -> T
{
    return (number & mask);
}

template<typename T>
auto GetBits(T number, uint from_bit, uint to_bit) -> T
{
	return (number & MakeBitMap<T>(from_bit, to_bit)) >> from_bit;
}

template<typename T>
void SetBits(T &number, ulong mask, ulong value)
{
    number = (number & ~mask) | value;
}

template<typename T>
void SetBits(T &number, uint from_bit, uint to_bit, ulong value)
{
	number = (number & ~MakeBitMap<T>(from_bit, to_bit)) | value;
}

template<typename T>
constexpr auto MakeBitMap(uint from_bit, uint to_bit) -> T
{
	return (((T)-1 >> ((sizeof(T) * 8 - 1) - (to_bit))) & ~((1ULL << (from_bit)) - 1));
}
