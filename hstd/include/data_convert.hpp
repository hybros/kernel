#ifndef __DATA_CONVERTER__
#define __DATA_CONVERTER__

#include <HStdTypes>
#include <HBitOperations>

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

template<class T, typename R>
auto ConvertToInteger(T value) -> R;

template<class T, typename R>
auto ConvertToInteger(T value, size_t size) -> R;

using ToInteger = ConvertToInteger;


#endif // __DATA_CONVERTER__
