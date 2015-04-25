#ifndef __DATA_CONVERTER__
#define __DATA_CONVERTER__

#include "data_types.hpp"
#include "bits.hpp"
#include "memory.hpp"

namespace kernel
{
namespace std DLL_PUBLIC
{

template<typename T>
class DataConverter
{
public:
    inline uchar  ToByte();             // Converts to uchar
    static uchar  ToByte(T value);
    inline ushort ToWord();             // Converts to ushort
    static ushort ToWord(T value);
    inline uint   ToDword();            // Converts to uint
    static uint   ToDword(T value);
    inline ulong  ToQword();            // Converts to ulong
    static ulong  ToQword(T value);

    template<typename R> inline R ToType();
    template<typename R> static R ToType(T value);
    template<typename R> static R ToType(T value, size_t size);

private:
    T data;
};

template<typename T, typename R>
R ConvertTypes(T value);

template<typename T, typename R>
R ConvertTypes(T value, size_t size);

// ~ DataConverter

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

// ° ConvertTypes

template<typename T, typename R>
R ConvertTypes(T value)
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
R ConvertTypes(T value, size_t size)
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

}
}
#endif // DATA_CONVERT_HPP
