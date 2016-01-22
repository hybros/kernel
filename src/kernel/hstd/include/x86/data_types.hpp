#ifndef __KERNEL_DATA_TYPES__
#define __KERNEL_DATA_TYPES__

struct __64BitInteger
{
    int first;
    int second;
} __attribute__((packed));

struct __64BitUnsignedInteger
{
    unsigned int first;
    unsigned int second;
} __attribute__((packed));

using uchar     = unsigned char;
using ushort    = unsigned short;
using uint      = unsigned int;
using ulong     = unsigned long;
using size_t    = unsigned long int;

using int8      = char;
using int16     = short;
using int32     = int;
using int64     = __64BitInteger;

using uint8     = uchar;
using uint16    = ushort;
using uint32    = uint;
using uint64    = __64BitUnsignedInteger;

using byte      = uint8;
using word      = uint16;
using dword     = uint32;
using qword     = uint64;

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long int
#endif

namespace kernel
{

enum HDataSize
{
    SIZE_BYTE   = sizeof(byte),
    SIZE_WORD   = sizeof(word),
    SIZE_DWORD  = sizeof(dword),
    SIZE_QWORD  = sizeof(qword)
};

}

#endif
