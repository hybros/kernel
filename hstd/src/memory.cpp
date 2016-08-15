#include "../include/memory.h"
#include "../include/memory.hpp"

#include <Hybros/System>

//void *memset(void *destination, char value, size_t size)
//{
//    char *tmp = reinterpret_cast<char*>(destination);
//    while(size--)
//        *tmp++ = value;
//
//    return destination;
//}

//void *memcpy(void *destination, const void *source, size_t size)
//{
//    char *tmp_dest = reinterpret_cast<char*>(destination);
//    const char *tmp_src = reinterpret_cast<const char*>(source);
//    while(size--)
//        *tmp_dest++ = *tmp_src++;
    
//    return destination;
//}

void *memzero(void *destination, size_t size)
{
    return memset(destination, 0, size);
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
    return HSystem::GetInstance().AllocateMemory(size);
}

void *operator new[](size_t size)
{
    return HSystem::GetInstance().AllocateMemory(size);
}

void operator delete(void *address)
{
    HSystem::GetInstance().FreeMemory(address);
}

void operator delete[](void *address)
{
    HSystem::GetInstance().FreeMemory(address);
}

