#ifndef __MEMORY_OPERATIONS__
#define __MEMORY_OPERATIONS__

#include "data_types.hpp"
#include "helper.hpp"
#include "data_extract.hpp"

extern "C"
{

DLL_PUBLIC void *memset(void *destination, char value, size_t size);
//DLL_PUBLIC void *memsetw(void *destination, ushort value, size_t size);
//DLL_PUBLIC void *memsetd(void *destination, uint value, size_t size);
//DLL_PUBLIC void *memsetq(void *destination, ulong value, size_t size);

DLL_PUBLIC inline void *memzero(void *destination, size_t size);

DLL_PUBLIC void *memcpy(void *destination, const void *source, size_t size);

DLL_PUBLIC void *memmove(void *destination, const void *source, size_t size);

DLL_PUBLIC void *memchr(void *source, uchar value, size_t size);

DLL_PUBLIC int memcmp(const void *first, const void *second, size_t size);

}

DLL_PUBLIC void *operator new (size_t size);
DLL_PUBLIC void *operator new[] (size_t size);
DLL_PUBLIC void operator delete (void *address);
DLL_PUBLIC void operator delete[] (void *address);

namespace kernel
{
namespace std DLL_PUBLIC
{

template<typename T>
class Memory
{
public:
    Memory();
    Memory(T &data);
    Memory(Memory<T> &other_memory);
    ~Memory();

    template<typename R> inline R GetMember(uint position);
    inline T GetData();
    inline void SetData(uchar value);
    inline void ZeroData();

    template<typename R> static inline R Get(T &data, uint position);
    static inline void Set(T &data, uchar value);
    static void Set(T &data, uchar value, size_t size);
    static inline void Zero(T &data);
    static void Zero(T &data, size_t size);

private:
    T memory_data;
};

// ~ Memory

template<typename T>
Memory<T>::Memory() : memory_data(0) {}

template<typename T>
Memory<T>::Memory(T &data)
{
    memory_data = data;
}

template<typename T>
Memory<T>::Memory(Memory<T> &other_memory)
{
    memory_data = other_memory.GetData();
}

template<typename T>
Memory<T>::~Memory()
{
    SetData(0);
}

template<typename T> template<typename R>
R Memory<T>::GetMember(uint position)
{
    return Get(memory_data, position);
}

template<typename T>
void Memory<T>::SetData(uchar value)
{
    Set(memory_data, value);
}

template<typename T>
void Memory<T>::ZeroData()
{
    Zero(memory_data);
}

template<typename T> template<typename R>
R Memory<T>::Get(T &data, uint position)
{
    return Extract<T, R>(data, position);
}

template<typename T>
void Memory<T>::Set(T &data, uchar value)
{
    Set(data, value, sizeof(T));
}

template<typename T>
void Memory<T>::Set(T &data, uchar value, size_t size)
{
    switch(size)
    {
    case sizeof(uchar):
        data = value;
        break;
    case sizeof(ushort):
        data = (value << 8) | value;
        break;
    case sizeof(uint):
        data = (value << 24) | (value << 16) | (value << 8) | value;
        break;
    case sizeof(ulong):
        data = (value << 56) | (value << 48) | (value << 40) | (value << 32) | (value << 24) | (value << 16) | (value << 8) | value;
        break;
    default:
        memsetd(&data, (value << 24) | (value << 16) | (value << 8) | value, size);
        break;
    }
}

template<typename T>
void Memory<T>::Zero(T &data)
{
    Zero(data, sizeof(T));
}

template<typename T>
void Memory<T>::Zero(T &data, size_t size)
{
    if(size > sizeof(ulong))
        memset(&data, 0, size);
    else
        data = 0;
}

}
}

void *memzero(void *destination, size_t size)
{
    memset(destination, 0, size);
}

#endif
