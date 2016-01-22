#include "../include/bitfield.hpp"

HBitfield<uint8>::HBitfield(const uchar integer) : bit_field(integer)
{
}

HBitfield<uint8>::HBitfield(const HBitfield<uint8> &other_bitfield) : bit_field(other_bitfield.bit_field)
{
}

auto HBitfield<uint8>::IsBitSet(uint bit_number) const -> bool
{
	return ::IsBitSet(bit_field, bit_number % 64);
}

auto HBitfield<uint8>::GetBit(uint bit_number) const -> uint8
{
	return ::GetBit(bit_field, bit_number % 64);
}

void HBitfield<uint8>::SetBit(uint bit_number)
{
	::SetBit(bit_field, bit_number % 64);
}

void HBitfield<uint8>::ClearBit(uint bit_number)
{
	::ClearBit(bit_field, bit_number % 64);
}

auto HBitfield<uint8>::AreBitsSet(uint from_bit, uint to_bit) const -> bool
{
	return ::AreBitsSet(bit_field, from_bit, to_bit);
}

auto HBitfield<uint8>::GetBits(uint from_bit, uint to_bit) const -> uint8
{
	return ::GetBits(bit_field, from_bit, to_bit);
}

void HBitfield<uint8>::SetBits(uint from_bit, uint to_bit, uint8 value)
{
	::SetBits(bit_field, from_bit, to_bit);
}

void HBitfield<uint8>::ClearBits(uint from_bit, uint to_bit)
{
	::ClearBits(bit_field, from_bit, to_bit);
}

auto HBitfield<uint8>::operator =(uint8 integer) -> HBitfield<uint8> &
{
    bit_field = integer;
    return *this;
}

HBitfield<uint8>::operator uint8() const
{
    return bit_field;
}


HBitfield<uint16>::HBitfield(const uint16 integer) : bit_field(integer)
{
}

HBitfield<uint16>::HBitfield(const HBitfield<uint16> &other_bitfield) : bit_field(other_bitfield.bit_field)
{
}

auto HBitfield<uint16>::IsBitSet(uint bit_number) const -> bool
{
	return ::IsBitSet(bit_field, bit_number % 64);
}

auto HBitfield<uint16>::GetBit(uint bit_number) const -> uint8
{
	return ::GetBit(bit_field, bit_number % 64);
}

void HBitfield<uint16>::SetBit(uint bit_number)
{
	::SetBit(bit_field, bit_number % 64);
}

void HBitfield<uint16>::ClearBit(uint bit_number)
{
	::ClearBit(bit_field, bit_number % 64);
}

auto HBitfield<uint16>::AreBitsSet(uint from_bit, uint to_bit) const -> bool
{
	return ::AreBitsSet(bit_field, from_bit, to_bit);
}

auto HBitfield<uint16>::GetBits(uint from_bit, uint to_bit) const -> uint16
{
	return ::GetBits(bit_field, from_bit, to_bit);
}

void HBitfield<uint16>::SetBits(uint from_bit, uint to_bit, uint16 value)
{
	::SetBits(bit_field, from_bit, to_bit);
}

void HBitfield<uint16>::ClearBits(uint from_bit, uint to_bit)
{
	::ClearBits(bit_field, from_bit, to_bit);
}

auto HBitfield<uint16>::operator =(uint16 integer) -> HBitfield<uint16> &
{
    bit_field = integer;
    return *this;
}

HBitfield<uint16>::operator uint16() const
{
    return bit_field;
}


HBitfield<uint32>::HBitfield(const uint32 integer) : bit_field(integer)
{
}

HBitfield<uint32>::HBitfield(const HBitfield<uint32> &other_bitfield) : bit_field(other_bitfield.bit_field)
{
}

auto HBitfield<uint32>::IsBitSet(uint bit_number) const -> bool
{
	return ::IsBitSet(bit_field, bit_number % 64);
}

auto HBitfield<uint32>::GetBit(uint bit_number) const -> uint32
{
	return ::GetBit(bit_field, bit_number % 64);
}

void HBitfield<uint32>::SetBit(uint bit_number)
{
	::SetBit(bit_field, bit_number % 64);
}

void HBitfield<uint32>::ClearBit(uint bit_number)
{
	::ClearBit(bit_field, bit_number % 64);
}

auto HBitfield<uint32>::AreBitsSet(uint from_bit, uint to_bit) const -> bool
{
	return ::AreBitsSet(bit_field, from_bit, to_bit);
}

auto HBitfield<uint32>::GetBits(uint from_bit, uint to_bit) const -> uint32
{
	return ::GetBits(bit_field, from_bit, to_bit);
}

void HBitfield<uint32>::SetBits(uint from_bit, uint to_bit, uint32 value)
{
	::SetBits(bit_field, from_bit, to_bit);
}

void HBitfield<uint32>::ClearBits(uint from_bit, uint to_bit)
{
	::ClearBits(bit_field, from_bit, to_bit);
}

auto HBitfield<uint32>::operator =(uint32 integer) -> HBitfield<uint32> &
{
    bit_field = integer;
    return *this;
}

HBitfield<uint32>::operator uint32() const
{
    return bit_field;
}


HBitfield<uint64>::HBitfield(const uint64 integer) : bit_field(integer)
{
}

HBitfield<uint64>::HBitfield(const HBitfield<uint64> &other_bitfield) : bit_field(other_bitfield.bit_field)
{
}

auto HBitfield<uint64>::IsBitSet(uint bit_number) const -> bool
{
	return ::IsBitSet(bit_field, bit_number % 64);
}

auto HBitfield<uint64>::GetBit(uint bit_number) const -> uint64
{
	return ::GetBit(bit_field, bit_number % 64);
}

void HBitfield<uint64>::SetBit(uint bit_number)
{
	::SetBit(bit_field, bit_number % 64);
}

void HBitfield<uint64>::ClearBit(uint bit_number)
{
	::ClearBit(bit_field, bit_number % 64);
}

auto HBitfield<uint64>::AreBitsSet(uint from_bit, uint to_bit) const -> bool
{
	return ::AreBitsSet(bit_field, from_bit, to_bit);
}

auto HBitfield<uint64>::GetBits(uint from_bit, uint to_bit) const -> uint64
{
	return ::GetBits(bit_field, from_bit, to_bit);
}

void HBitfield<uint64>::SetBits(uint from_bit, uint to_bit, uint64 value)
{
	::SetBits(bit_field, from_bit, to_bit, value);
}

void HBitfield<uint64>::ClearBits(uint from_bit, uint to_bit)
{
	::ClearBits(bit_field, from_bit, to_bit);
}

auto HBitfield<uint64>::operator =(uint64 integer) -> HBitfield<uint64> &
{
    bit_field = integer;
    return *this;
}

HBitfield<uint64>::operator uint64() const
{
    return bit_field;
}
