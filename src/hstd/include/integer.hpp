#ifndef __INTEGER__
#define __INTEGER__

#include <HStdTypes>

template<typename T>
class HBitmap;
class HString;

class HInteger
{
public:
    inline HInteger();
    inline HInteger(const ulong new_integer);
    inline HInteger(const HInteger &other_integer);
    inline ~HInteger();

    inline auto GetInteger() const -> uint64;
    inline auto GetReference() -> uint64 &;
    inline auto GetConstReference() const -> uint64 &;
    inline void SetInteger(const HInteger &other_int = HInteger());

    inline auto ToChar() const -> char;
    inline auto ToShort() const -> short;
    inline auto ToInt() const -> int;
    inline auto ToLong() const -> long;

    inline auto ToUChar() const -> uchar;
    inline auto ToUShort() const -> ushort;
    inline auto ToUInt() const -> uint;
    inline auto ToSizeT() const -> size_t;

    inline auto ToRawString() const -> char *;
    inline auto ToRawString(uchar integer_base) const -> char *;
    inline auto ToHString() const -> HString;
    inline auto ToHString(uchar integer_base) const -> HString;
    inline auto ToHBitmap() const -> HBitmap<uint64>;

//    inline void operator =(const char new_integer);
//    inline void operator =(const short new_integer);
//    inline void operator =(const int new_integer);
//    inline void operator =(const long new_integer);

//    inline void operator =(const uchar new_integer);
//    inline void operator =(const ushort new_integer);
//    inline void operator =(const uint new_integer);
    inline void operator =(const uint64 new_integer);

//    inline auto operator +(const HInteger &other_int) -> HInteger;
//    inline auto operator -(const HInteger &other_int) -> HInteger;
//    inline auto operator *(const HInteger &other_int) -> HInteger;
//    inline auto operator /(const HInteger &other_int) -> HInteger;
//    inline auto operator %(const HInteger &other_int) -> HInteger;
    inline auto operator ++(int) -> HInteger;
    inline auto operator --(int) -> HInteger;

//    inline void operator +=(const HInteger &other_int);
//    inline void operator -=(const HInteger &other_int);
//    inline void operator *=(const HInteger &other_int);
//    inline void operator /=(const HInteger &other_int);
//    inline void operator %=(const HInteger &other_int);

//    inline auto operator  <(const HInteger &other_int) -> bool;
//    inline auto operator  >(const HInteger &other_int) -> bool;
//    inline auto operator <=(const HInteger &other_int) -> bool;
//    inline auto operator >=(const HInteger &other_int) -> bool;
//    inline auto operator ==(const HInteger &other_int) -> bool;
//    inline auto operator !=(const HInteger &other_int) -> bool;

//    inline auto operator  &(const HInteger &other_integer) -> HInteger;
//    inline auto operator  |(const HInteger &other_integer) -> HInteger;
//    inline auto operator  ^(const HInteger &other_integer) -> HInteger;
//    inline auto operator <<(const HInteger &bit_number) -> HInteger;
//    inline auto operator >>(const HInteger &bit_number) -> HInteger;

    inline void operator   ~();
//    inline void operator  &=(const HInteger &other_integer);
//    inline void operator  |=(const HInteger &other_integer);
//    inline void operator  ^=(const HInteger &other_integer);
//    inline void operator <<=(const HInteger &bit_number);
//    inline void operator >>=(const HInteger &bit_number);

//    inline auto operator +(const ulong other_integer) -> HInteger;
//    inline auto operator -(const ulong other_integer) -> HInteger;
//    inline auto operator *(const ulong other_integer) -> HInteger;
//    inline auto operator /(const ulong other_integer) -> HInteger;

//    inline void operator +=(const ulong other_integer);
//    inline void operator -=(const ulong other_integer);
//    inline void operator *=(const ulong other_integert);
//    inline void operator /=(const ulong other_integer);

//    inline bool operator  <(const ulong other_integer);
//    inline bool operator  >(const ulong other_integer);
//    inline bool operator <=(const ulong other_integer);
//    inline bool operator >=(const ulong other_integer);
//    inline bool operator ==(const ulong other_integer);
//    inline bool operator !=(const ulong other_integer);

//    inline explicit operator char() const;
//    inline explicit operator short() const;
//    inline explicit operator int() const;
//    inline explicit operator long() const;

//    inline explicit operator uchar() const;
//    inline explicit operator ushort() const;
//    inline explicit operator uint() const;
    inline operator uint64 &();
//    inline explicit operator size_t() const;

protected:
    uint64 integer;
};

using HInt = HInteger;
using HSize  = HInteger;

#endif // __INTEGER__

