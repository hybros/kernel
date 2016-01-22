#include "../../include/bits.hpp"

template<>
auto IsBitSet<uint64>(uint64 number, ulong bit) -> bool
{
    return (number & (1ULL << bit)) != 0;
}

template<>
void ClearBit<uint64>(uint64 &number, ulong bit)
{
    number &= ~(1ULL << bit);
}

template<>
void ToggleBit<uint64>(uint64 &number, ulong bit)
{
    number ^= 1ULL << bit;
}

template<>
auto GetBit<uint64>(uint64 number, ulong bit) -> uint64
{
    return number & (1ULL << bit);
}

template<>
void SetBit<uint64>(uint64 &number, ulong bit)
{
    number |= 1ULL << bit;
}

/*
template<>
auto AreBitsSet<uint64>(uint64 number, ulong mask) -> bool
{
	return (number & mask) != 0;
}

template<>
auto AreBitsSet<uint64>(uint64 number, uint from_bit, uint to_bit) -> bool
{
	return (number & MakeBitMap<uint64>(from_bit, to_bit)) != 0;
}

template<>
void ClearBits<uint64>(uint64 &number, ulong mask)
{
	number &= ~mask;
}

template<>
void ClearBits<uint64>(uint64 &number, uint from_bit, uint to_bit)
{
	number &= ~MakeBitMap<uint64>(from_bit, to_bit);
}

template<>
auto GetBits<uint64>(uint64 number, ulong mask) -> uint64
{
	return (number & mask);
}

template<>
auto GetBits<uint64>(uint64 number, uint from_bit, uint to_bit) -> uint64
{
	return (number & MakeBitMap<uint64>(from_bit, to_bit)) >> from_bit;
}

template<>
void SetBits<uint64>(uint64 &number, ulong mask, ulong value)
{
	number = (number & ~mask) | value;
}

template<>
void SetBits<uint64>(uint64 &number, uint from_bit, uint to_bit, ulong value)
{
	number = (number & ~MakeBitMap<uint64>(from_bit, to_bit)) | value;
}
*/

template<>
constexpr auto MakeBitMap<uint64>(uint from_bit, uint to_bit) -> uint64
{
	return ((static_cast<uint64>(-1) >> (63 - (to_bit))) & ~((1ULL << (from_bit)) - 1));
}