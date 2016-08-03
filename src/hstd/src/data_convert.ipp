#include "../include/data_convert.hpp"

template<typename T>
uchar DataConverter<T>::ToByte()
{
    return ToByte(data);
}

template<typename T>
uchar DataConverter<T>::ToByte(T value)
{
    return GetBits(value, 0xFF, 0);
}

template<typename T>
ushort DataConverter<T>::ToWord()
{
    return ToWord(data);
}

template<typename T>
ushort DataConverter<T>::ToWord(T value)
{
    return GetBits(value, 0xFFFF, 0);
}

template<typename T>
uint DataConverter<T>::ToDword()
{
    return ToDword(data);
}

template<typename T>
uint DataConverter<T>::ToDword(T value)
{
    return GetBits(value, 0xFFFFFFFF, 0);
}

template<typename T>
ulong DataConverter<T>::ToQword()
{
    return ToQword(data);
}

template<typename T>
ulong DataConverter<T>::ToQword(T value)
{
    return GetBits(value, 0xFFFFFFFFFFFFFFFF, 0);
}

template<typename T> template <typename R>
R DataConverter<T>::ToType()
{
    return ToType(data, sizeof(R));
}

template<typename T> template <typename R>
R DataConverter<T>::ToType(T value)
{
    return ToType(value, sizeof(R));
}

template<typename T> template <typename R>
R DataConverter<T>::ToType(T value, size_t size)
{
    R tmp;
    if(size <= sizeof(R))
        memcpy(&tmp, &value, size);
    else
        tmp = {0};
    return tmp;
}

// # ConvertToInteger

template<typename T, typename R>
R ConvertToInteger(T value)
{
    size_t size = sizeof(R);
#if size == 1
    return DataConverter<T>::ToByte(value);
#elif size == 2
    return DataConverter<T>::ToWord(value);
#elif size == 4
    return DataConverter<T>::ToDword(value);
#elif size == 8
    return DataConverter<T>::ToQword(value);
#endif
}

template<typename T, typename R>
R ConvertToInteger(T value, size_t size)
{
    switch(size)
    {
    case sizeof(uchar):
        return DataConverter<T>::ToByte(value);
    case sizeof(ushort):
        return DataConverter<T>::ToWord(value);
    case sizeof(uint):
        return DataConverter<T>::ToDword(value);
    case sizeof(ulong):
        return DataConverter<T>::ToQword(value);
    default:
        return DataConverter<T>::ToType(value, size);
    }
}
