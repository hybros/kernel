#include "../include/memory.hpp"
#include "../include/memory.h"


//namespace kernel
//{

//template<typename T>
//Memory<T>::Memory() : memory_data(0) {}

//template<typename T>
//Memory<T>::Memory(T &data)
//{
//    memory_data = data;
//}

//template<typename T>
//Memory<T>::Memory(Memory<T> &other_memory)
//{
//    memory_data = other_memory.GetData();
//}

//template<typename T>
//Memory<T>::~Memory()
//{
//    SetData(0);
//}

//template<typename T> template<typename R>
//R Memory<T>::GetMember(uint position)
//{
//    return Get(memory_data, position);
//}

//template<typename T>
//void Memory<T>::SetData(uchar value)
//{
//    Set(memory_data, value);
//}

//template<typename T>
//void Memory<T>::ZeroData()
//{
//    Zero(memory_data);
//}

//template<typename T> template<typename R>
//R Memory<T>::Get(T &data, uint position)
//{
//    return Extract<T, R>(data, position);
//}

//template<typename T>
//void Memory<T>::Set(T &data, uchar value)
//{
//    Set(data, value, sizeof(T));
//}

//template<typename T>
//void Memory<T>::Set(T &data, uchar value, size_t size)
//{
//    switch(size)
//    {
//    case sizeof(uchar):
//        data = value;
//        break;
//    case sizeof(ushort):
//        data = (value << 8) | value;
//        break;
//    case sizeof(uint):
//        data = (value << 24) | (value << 16) | (value << 8) | value;
//        break;
//    case sizeof(ulong):
//        data = (value << 56) | (value << 48) | (value << 40) | (value << 32) | (value << 24) | (value << 16) | (value << 8) | value;
//        break;
//    default:
//        memsetd(&data, (value << 24) | (value << 16) | (value << 8) | value, size);
//        break;
//    }
//}

//template<typename T>
//void Memory<T>::Zero(T &data)
//{
//    Zero(data, sizeof(T));
//}

//template<typename T>
//void Memory<T>::Zero(T &data, size_t size)
//{
//    if(size > sizeof(ulong))
//        memset(&data, 0, size);
//    else
//        data = 0;
//}

//}
