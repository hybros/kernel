#include "../include/integer.hpp"

#include <HBitmap>
#include <HString>

#include "../include/data_extract.hpp"

namespace kernel
{

HInteger::HInteger() : integer(0) {}

HInteger::HInteger(const ulong new_integer) : integer(new_integer) {}

HInteger::HInteger(const HInteger &other_integer) : integer(other_integer.GetConstReference()) {}

HInteger::~HInteger()
{
    integer = 0;
}

auto HInteger::GetInteger() const -> uint64
{
    return integer;
}

auto HInteger::GetReference() -> uint64 &
{
    return integer;
}

void HInteger::SetInteger(const HInteger &other_int)
{
    integer = other_int.GetInteger();
}

auto HInteger::ToChar() const -> char
{
    return static_cast<char>(ExtractByte(integer, 0));
}

auto HInteger::ToShort() const -> short
{
    return static_cast<short>(ExtractWord(integer, 0));
}

auto HInteger::ToInt() const -> int
{
    return static_cast<int>(ExtractDword(integer, 0));
}

auto HInteger::ToLong() const -> long
{
    return static_cast<long>(integer);
}

auto HInteger::ToUChar() const -> uchar
{
    return ExtractByte(integer, 0);
}

auto HInteger::ToUShort() const -> ushort
{
    return ExtractWord(integer, 0);
}

auto HInteger::ToUInt() const -> uint
{
    return ExtractDword(integer, 0);
}

auto HInteger::ToSizeT() const -> size_t
{
    return static_cast<size_t>(integer);
}

auto HInteger::ToRawString() const -> char *
{
    return ConvertToRawString(integer, 10);
}

auto HInteger::ToRawString(uchar integer_base) const -> char *
{
    return ConvertToRawString(integer, integer_base);
}

auto HInteger::ToHString() const -> HString
{
    return ConvertToHString(integer, 10);
}

auto HInteger::ToHString(uchar integer_base) const -> HString
{
    return ConvertToHString(integer, integer_base);
}

auto HInteger::ToHBitmap() const -> HBitmap<uint64>
{

}

//void HInteger::operator =(short new_integer)
//{
//    integer = new_integer;
//}

//void HInteger::operator =(int new_integer)
//{
//    integer = new_integer;
//}

//void HInteger::operator =(long new_integer)
//{
//    integer = new_integer;
//}

//void HInteger::operator =(uchar new_integer)
//{
//    integer = new_integer;
//}

//void HInteger::operator =(ushort new_integer)
//{
//    integer = new_integer;
//}

//void HInteger::operator =(uint new_integer)
//{
//    integer = new_integer;
//}

void HInteger::operator =(const uint64 new_integer)
{
    integer = new_integer;
}

//auto HInteger::operator +(const HInteger &other_int) -> HInteger
//{
//    return HInteger(this->integer + other_int.GetConstReference());
//}

//auto HInteger::operator -(const HInteger &other_int) -> HInteger
//{
//    return HInteger(integer - other_int.GetConstReference());
//}

//auto HInteger::operator *(const HInteger &other_int) -> HInteger
//{
//    return HInteger(integer * other_int.GetConstReference());
//}

//auto HInteger::operator /(const HInteger &other_int) -> HInteger
//{
//    return HInteger(integer / other_int.GetConstReference());
//}

//auto HInteger::operator %(const HInteger &other_int) -> HInteger
//{
//    return HInteger(integer % other_int.GetConstReference());
//}

auto HInteger::operator ++(int) -> HInteger
{
    return HInteger(integer++);
}

auto HInteger::operator --(int) -> HInteger
{
    return HInteger(integer--);
}

//void HInteger::operator +=(const HInteger &other_int)
//{
//    integer += other_int.GetConstReference();
//}

//void HInteger::operator -=(const HInteger &other_int)
//{
//    integer -= other_int.GetConstReference();
//}

//void HInteger::operator *=(const HInteger &other_int)
//{
//    integer *= other_int.GetConstReference();
//}

//void HInteger::operator /=(const HInteger &other_int)
//{
//    integer /= other_int.GetConstReference();
//}

//auto HInteger::operator <(const HInteger &other_int) -> bool
//{
//    return (integer < other_int.GetConstReference()) ? true : false;
//}

//auto HInteger::operator >(const HInteger &other_int) -> bool
//{
//    return (integer > other_int.GetConstReference()) ? true : false;
//}

//auto HInteger::operator <=(const HInteger &other_int) -> bool
//{
//    return (integer <= other_int.GetConstReference()) ? true : false;
//}

//auto HInteger::operator >=(const HInteger &other_int) -> bool
//{
//    return (integer >= other_int.GetConstReference()) ? true : false;
//}

//auto HInteger::operator ==(const HInteger &other_int) -> bool
//{
//    return (integer == other_int.GetConstReference()) ? true : false;
//}

//auto HInteger::operator !=(const HInteger &other_int) -> bool
//{
//    return (integer != other_int.GetConstReference()) ? true : false;
//}

//auto HInteger::operator &(const HInteger &other_int) -> HInteger
//{
//    return HInteger(integer & other_int.GetConstReference());
//}

//auto HInteger::operator |(const HInteger &other_int) -> HInteger
//{
//    return HInteger(integer | other_int.GetConstReference());
//}

//auto HInteger::operator ^(const HInteger &other_int) -> HInteger
//{
//    return HInteger(integer ^ other_int.GetConstReference());
//}

//auto HInteger::operator <<(const HInteger &bit_number) -> HInteger
//{
//    return HInteger(integer << bit_number.GetConstReference());
//}

//auto HInteger::operator >>(const HInteger &bit_number) -> HInteger
//{
//    return HInteger(integer >> bit_number.GetConstReference());
//}

void HInteger::operator ~()
{
    integer = ~integer;
}

//void HInteger::operator &=(const HInteger &other_int)
//{
//    integer &= other_int.GetConstReference();
//}

//void HInteger::operator |=(const HInteger &other_int)
//{
//    integer |= other_int.GetConstReference();
//}

//void HInteger::operator ^=(const HInteger &other_int)
//{
//    integer ^= other_int.GetConstReference();
//}

//void HInteger::operator <<=(const HInteger &bit_number)
//{
//    integer <<= bit_number.GetConstReference();
//}

//void HInteger::operator >>=(const HInteger &bit_number)
//{
//    integer >>= bit_number.GetConstReference();
//}

//HInteger HInteger::operator +(const ulong other_integer)
//{
//    return HInteger(integer + other_integer);
//}

//HInteger HInteger::operator -(const ulong other_integer)
//{
//    return HInteger(integer - other_integer);
//}

//HInteger HInteger::operator *(const ulong other_integer)
//{
//    return HInteger(integer * other_integer);
//}

//HInteger HInteger::operator /(const ulong other_integer)
//{
//    return HInteger(integer / other_integer);
//}

//void HInteger::operator +=(const ulong other_integer)
//{
//    integer += other_integer;
//}

//void HInteger::operator -=(const ulong other_integer)
//{
//    integer -= other_integer;
//}

//void HInteger::operator *=(const ulong other_integer)
//{
//    integer *= other_integer;
//}

//void HInteger::operator /=(const ulong other_integer)
//{
//    integer /= other_integer;
//}

//bool HInteger::operator <(const ulong other_integer)
//{
//    return (integer < other_integer) ? true : false;
//}

//bool HInteger::operator >(const ulong other_integer)
//{
//    return (integer > other_integer) ? true : false;
//}

//bool HInteger::operator <=(const ulong other_integer)
//{
//    return (integer <= other_integer) ? true : false;
//}

//bool HInteger::operator >=(const ulong other_integer)
//{
//    return (integer >= other_integer) ? true : false;
//}

//bool HInteger::operator ==(const ulong other_integer)
//{
//    return (integer == other_integer) ? true : false;
//}

//bool HInteger::operator !=(const ulong other_integer)
//{
//    return (integer != other_integer) ? true : false;
//}

//HInteger::operator char() const
//{
//    return static_cast<char>(ExtractByte(integer, 0));
//}

//HInteger::operator short() const
//{
//    return static_cast<short>(ExtractWord(integer, 0));
//}

//HInteger::operator int() const
//{
//    return static_cast<int>(ExtractDword(integer, 0));
//}

//HInteger::operator long() const
//{
//    return static_cast<long>(integer);
//}

//HInteger::operator uchar() const
//{
//    return ExtractByte(integer, 0);
//}

//HInteger::operator ushort() const
//{
//    return ExtractWord(integer, 0);
//}

//HInteger::operator uint() const
//{
//    return ExtractDword(integer, 0);
//}

HInteger::operator uint64 &()
{
    return integer;
}

//HInteger::operator HBitmap<uint64>() const
//{
//    return HBitmap<uint64>(sizeof(uint64), &integer);
//}

//HInteger::operator char*() const
//{
//    return ConvertToRawString(integer, 10);
//}

//HInteger::operator HString() const
//{
//    return ConvertToHString(integer, 10);
//}

}
