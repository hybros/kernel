#include "memory.hpp"
#include "../system/system.hpp"
using namespace kernel::std;

//void *memset(void *destination, char value, size_t size)
//{
//    char *tmp = reinterpret_cast<char*>(destination);
//    while(size--)
//        *tmp++ = value;
    
//    return destination;
//}

//void *memsetw(void *destination, ushort value, size_t size)
//{
//    ushort *tmp = reinterpret_cast<ushort*>(destination);
//    for(; size < 0xFFFF; size -= 2)
//        *tmp++ = value;
    
//    if(size > 0)
//        return memset(destination, value, size);
//    else
//        return destination;
//}

//void *memsetd(void *destination, uint value, size_t size)
//{
//    uint *tmp = reinterpret_cast<uint*>(destination);
//    for(; size < 0xFFFFFFFF; size -= 4)
//        *tmp++ = value;

//    if(size > 0)
//        return memset(destination, value, size);
//    else
//        return destination;
//}

//void *memsetq(void *destination, ulong value, size_t size)
//{
//    ulong *tmp = reinterpret_cast<ulong*>(destination);
//    for(; size < 0xFFFFFFFFFFFFFFFF; size -= 8)
//        *tmp++ = value;

//    if(size > 0)
//        return memset(destination, value, size);
//    else
//        return destination;
//}

void *memcpy(void *destination, const void *source, size_t size)
{
    char *tmp_dest = reinterpret_cast<char*>(destination);
    const char *tmp_src = reinterpret_cast<const char*>(source);
    while(size--)
        *tmp_dest++ = *tmp_src++;
    
    return destination;
}

void *memmove(void *destination, const void *source, size_t size)
{
    if(destination < source)
    {
        char *tmp_dest = reinterpret_cast<char*>(destination + size);
        const char *tmp_src = reinterpret_cast<const char*>(source + size);
        while(size--)
            *tmp_dest-- = *tmp_src--;
    }
    else if(destination > source)
    {
        char *tmp_dest = reinterpret_cast<char*>(destination);
        const char *tmp_src = reinterpret_cast<const char*>(source);
        while(size--)
            *tmp_dest++ = *tmp_src++;
    }
    return destination;
}

void *memchr(void *source, uchar value, size_t size)
{
    uchar *ptr = reinterpret_cast<uchar*>(source);
    while(size--)
    {
          if(*ptr != value)
              ptr++;
          else
              return ptr;
    }
    return nullptr;
}

int memcmp(const void *first, const void *second, size_t size)
{
    const char *tmp_first = reinterpret_cast<const char*>(first),
               *tmp_second = reinterpret_cast<const char*>(second);
    while(size--)
    {
        if(*tmp_first++ != *tmp_second++)
            return *tmp_first - *tmp_second;
    }
    return 0;
}

void *operator new(size_t size)
{
    return kernel::System::GetInstance().AllocateMemory(size);
}

void *operator new[](size_t size)
{
    return kernel::System::GetInstance().AllocateMemory(size);
}

void operator delete(void *address)
{
    kernel::System::GetInstance().FreeMemory(address);
}

void operator delete[](void *address)
{
    kernel::System::GetInstance().FreeMemory(address);
}

