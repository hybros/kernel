#ifndef __BITFIELD__
#define __BITFIELD__

#include <HBitOperations>

template<typename T>
class HBitfield;

template<>
class HBitfield<uint8>
{
public:
    HBitfield() = default;
    HBitfield(const uchar integer);
    HBitfield(const HBitfield<uint8> &other_bitfield);
    ~HBitfield() = default;

	auto IsBitSet(uint bit_number) const -> bool;
	auto GetBit(uint bit_number) const -> uint8;
	void SetBit(uint bit_number);
	void ClearBit(uint bit_number);

	auto AreBitsSet(uint from_bit, uint to_bit) const -> bool;
	auto GetBits(uint from_bit, uint to_bit) const -> uint8;
	void SetBits(uint from_bit, uint to_bit, uint8 value);
	void ClearBits(uint from_bit, uint to_bit);

	auto ToUChar() const -> uint8;

    auto operator [](uint bit_position) const-> uint8;

    auto operator =(uint8 integer) -> HBitfield<uint8> &;
    operator uint8() const;

protected:
	uint8 bit_field;
};

template<>
class HBitfield<uint16>
{
public:
	HBitfield() = default;
	HBitfield(const uint16 integer);
	HBitfield(const HBitfield<uint16> &other_bitfield);
	~HBitfield() = default;

	auto IsBitSet(uint bit_number) const -> bool;
	auto GetBit(uint bit_number) const -> uchar;
	void SetBit(uint bit_number);
	void ClearBit(uint bit_number);

	auto AreBitsSet(uint from_bit, uint to_bit) const -> bool;
	auto GetBits(uint from_bit, uint to_bit) const -> uint16;
	void SetBits(uint from_bit, uint to_bit, uint16 value);
	void ClearBits(uint from_bit, uint to_bit);

	auto ToUChar() const -> uint16;

	auto operator [](uint bit_position) const-> uint16;

    auto operator =(uint16 integer) -> HBitfield<uint16> &;
    operator uint16() const;

protected:
	uint16 bit_field;
};

template<>
class HBitfield<uint32>
{
public:
	HBitfield() = default;
	HBitfield(const uint32 integer);
	HBitfield(const HBitfield<uint32> &other_bitfield);
	~HBitfield() = default;

	auto IsBitSet(uint bit_number) const -> bool;
	auto GetBit(uint bit_number) const-> uint32;
	void SetBit(uint bit_number);
	void ClearBit(uint bit_number);

	auto AreBitsSet(uint from_bit, uint to_bit) const -> bool;
	auto GetBits(uint from_bit, uint to_bit) const-> uint32;
	void SetBits(uint from_bit, uint to_bit, uint32 value);
	void ClearBits(uint from_bit, uint to_bit);

	auto ToUChar() const -> uint32;

	auto operator [](uint bit_position) const-> uint32;

    auto operator =(uint32 integer) -> HBitfield<uint32> &;
    operator uint32() const;

protected:
	uint32 bit_field;
};

template<>
class HBitfield<uint64>
{
public:
	HBitfield() = default;
	HBitfield(const uint64 integer);
	HBitfield(const HBitfield<uint64> &other_bitfield);
	~HBitfield() = default;

	auto IsBitSet(uint bit_number) const -> bool;
	auto GetBit(uint bit_number) const -> uint64;
	void SetBit(uint bit_number);
	void ClearBit(uint bit_number);

	auto AreBitsSet(uint from_bit, uint to_bit) const -> bool;
	auto GetBits(uint from_bit, uint to_bit) const -> uint64;
	void SetBits(uint from_bit, uint to_bit, uint64 value);
	void ClearBits(uint from_bit, uint to_bit);

	auto ToUChar() const -> uint64;

	auto operator [](uint bit_position) const-> uint64;

    auto operator =(uint64 integer) -> HBitfield<uint64> &;
    operator uint64() const;

protected:
	uint64 bit_field;
};

#define BITFIELD_CREATE_TESTER(name, from, to) \
bool Is##name##Set(){return ::AreBitsSet(bit_field, from, to);}

#define BITFIELD_CREATE_CLEARER(name, from, to) \
void Clear##name(){return ::ClearBits(bit_field, from, to);}

#define BITFIELD_CREATE_GETTER(type, name, from, to) \
type Get##name(){return static_cast<type>(::GetBits(bit_field, from, to));}

#define BITFIELD_CREATE_SETTER(type, name, from, to) \
void Set##name(type value){::SetBits(bit_field, from, to, value);}

#define BITFIELD_MEMBER(type, member, from, to) \
BITFIELD_CREATE_TESTER(member, from, to) \
BITFIELD_CREATE_CLEARER(member, from, to) \
BITFIELD_CREATE_GETTER(type, member, from, to) \
BITFIELD_CREATE_SETTER(type, member, from, to)

#define BITFIELD_CREATE_TESTER1(name, bit) \
bool Is##name##Set(){return ::IsBitSet(bit_field, bit);}

#define BITFIELD_CREATE_CLEARER1(name, bit) \
void Clear##name(){return ::ClearBit(bit_field, bit);}

#define BITFIELD_CREATE_GETTER1(type, name, bit) \
type Get##name(){return static_cast<type>(::GetBit(bit_field, bit));}

#define BITFIELD_CREATE_SETTER1(type, name, bit) \
void Set##name(type value){::SetBit(bit_field, bit);}

#define BITFIELD_MEMBER1(type, member, bit) \
BITFIELD_CREATE_TESTER1(member, bit) \
BITFIELD_CREATE_CLEARER1(member, bit) \
BITFIELD_CREATE_GETTER1(type, member, bit) \
BITFIELD_CREATE_SETTER1(type, member, bit)

#define BITFIELD_COMMON(name, type) \
inline name(type integer) \
{ \
    bit_field = integer; \
} \
inline auto operator =(type integer) -> name & \
{ \
    bit_field = integer; \
    return *this; \
}

#define BITFIELD_START(name, type) \
class name : public HBitfield<type>\
{ \
public:

#define BITFIELD_END }; 

#endif
