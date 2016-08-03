#ifndef __SYSTEM_ASSEMBLER_FUNCTIONS_FOR_CPP__
#define __SYSTEM_ASSEMBLER_FUNCTIONS_FOR_CPP__

#include <HStdTypes>

namespace kernel
{

template<typename T> inline void WritePort(ushort port, T data);

template<>
inline void WritePort(ushort port, uchar data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (port), "a" (data));
}

template<>
inline void WritePort(ushort port, ushort data)
{
    __asm__ __volatile__ ("outw %1, %0" : : "dN" (port), "a" (data));
}

template<>
inline void WritePort(ushort port, uint data)
{
   __asm__ __volatile__ ("outl %1, %0" : : "dN" (port), "a" (data));
}

template<typename T> inline T ReadPort(ushort port);

template<>
inline uchar ReadPort(ushort port)
{
   uchar data = 0;
   __asm__ __volatile__ ("inb %1, %0" : "=a" (data) : "dN" (port));
   return data;
}

template<>
inline ushort ReadPort(ushort port)
{
   ushort data = 0;
   __asm__ __volatile__ ("inw %1, %0" : "=a" (data) : "dN" (port));
   return data;
}

template<>
inline uint ReadPort(ushort port)
{
   uint data = 0;
   __asm__ __volatile__ ("inl %1, %0" : "=a" (data) : "dN" (port));
   return data;
}

inline void cpuid(uint code, uint *eax_value, uint *edx_value)
{
    __asm__ __volatile__("cpuid" : "=a"(*eax_value), "=d"(*edx_value) : "a"(code) : "ebx", "ecx");
}

inline void cpuid(uint code, uint *eax_value, uint *ecx_value, uint *edx_value)
{
    __asm__ __volatile__("cpuid" : "=a"(*eax_value), "=c"(*ecx_value), "=d"(*edx_value) : "a"(code) : "ebx");
}

inline void cpuid(uint code, uint *eax_value, uint *ebx_value, uint *ecx_value, uint *edx_value)
{
    __asm__ __volatile__("cpuid" : "=a"(*eax_value), "=b"(*ebx_value), "=c"(*ecx_value), "=d"(*edx_value) : "a"(code));
}

inline void rdmsr(uint msr, uint *low_dword, uint *high_dword)
{
    __asm__ __volatile__("rdmsr" : "=a"(*low_dword), "=d"(*high_dword) : "c"(msr));
}

inline void wrmsr(uint msr, uint low_dword, uint high_dword)
{
    __asm__ __volatile__("wrmsr" :: "a"(low_dword), "d"(high_dword), "c"(msr));
}

}


#endif
