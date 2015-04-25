#ifndef __KERNEL_DATA_TYPES__
#define __KERNEL_DATA_TYPES__

typedef unsigned char       uchar;
typedef unsigned short      ushort;
typedef unsigned int        uint;
#ifdef __x86_64__
typedef unsigned long long  ulong;
#else
typedef unsigned long       ulong;
#endif
typedef unsigned long int   size_t;

#ifndef __SIZE_TYPE__
#define __SIZE_TYPE__ unsigned long int
#endif

enum DataSize
{
    SIZE_BYTE   = sizeof(uchar),
    SIZE_WORD   = sizeof(ushort),
    SIZE_DWORD  = sizeof(uint),
    SIZE_QWORD  = sizeof(ulong)
};

#endif
