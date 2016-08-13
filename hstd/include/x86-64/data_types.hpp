#ifndef __KERNEL_DATA_TYPES__
#define __KERNEL_DATA_TYPES__

using uchar     = unsigned char;
using ushort    = unsigned short;
using uint      = unsigned int;
using ulong     = unsigned long;
using size_t    = unsigned long int;

using int8      = char;
using int16     = short;
using int32     = int;
using int64     = long long;

using uint8     = uchar;
using uint16    = ushort;
using uint32    = uint;
using uint64    = unsigned long long;

using char16    = char16_t;
using char32    = char32_t;

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long int
#endif

enum class DataSize
{
    CHAR   = sizeof(char),
    SHORT  = sizeof(short),
    INT    = sizeof(int),
    LONG   = sizeof(long),

    CHAR_BITS   = sizeof(char) * 8,
    SHORT_BITS  = sizeof(short) * 8,
    INT_BITS    = sizeof(int) * 8,
    LONG_BITS   = sizeof(long) * 8,
};

enum class IntSize : int32
{
    MININUM = -2147483648,
    MAXIMUM = 2147483647
};

enum class UIntSize : uint32
{
    MININUM = 0,
    MAXIMUM = 4294967295
};

enum class LongValue64 : int64
{
    MININUM = -9223372036854775807,
    MAXIMUM = 9223372036854775807
};

enum class ULongValue64 : uint64
{
    MININUM = 0,
    MAXIMUM = 18446744073709551615
};

using LongValue = LongValue64;
using ULongValue = ULongValue64;

#define LONG_MIN LongValue::MININUM
#define LONG_MAX LongValue::MAXIMUM

#define ULONG_MIN ULongValue::MININUM
#define ULONG_MAX ULongValue::MAXIMUM

#endif
