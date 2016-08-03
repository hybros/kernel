#include "../include/bitmap.hpp"

#include <cMemory>
#include <HBitOperations>

template<typename T>
HBitmap<T>::HBitmap() : bitmap_pointer(nullptr), bitmap_size(0) {}

template<typename T>
HBitmap<T>::HBitmap(size_t size, uchar value) : bitmap_pointer(new T[size / sizeof(T)]), bitmap_size(size)
{
    if(value == 0)
        Clear();
    else
        Reset(value);
}

template<typename T>
HBitmap<T>::HBitmap(size_t size, const T *bitmap_array) : bitmap_pointer(new T[size / sizeof(T)]), bitmap_size(size)
{
    if(bitmap_array)
        memcpy(bitmap_pointer, bitmap_array, bitmap_size);
}

template<typename T>
HBitmap<T>::~HBitmap()
{
    Clear();
    delete bitmap_pointer;
    bitmap_size = 0;
}

template<typename T>
void HBitmap<T>::Clear()
{
    memzero(bitmap_pointer, bitmap_size);
}

template<typename T>
void HBitmap<T>::Reset(uchar value)
{
    memset(bitmap_pointer, value, bitmap_size);
}

template<typename T>
void HBitmap<T>::Resize(size_t size)
{
    if(bitmap_size < size)
    {
        void *tmp_ptr = bitmap_pointer;
        bitmap_pointer = new T[size / sizeof(T)];
        delete tmp_ptr;
    }
}

template<typename T>
bool HBitmap<T>::IsBitSet(uint bit_number)
{
    return ::IsBitSet(bitmap_pointer[bit_number / (sizeof(T) * 8)], bit_number % (sizeof(T) * 8));
}

template<typename T>
T HBitmap<T>::GetBit(uint bit_number)
{
    return ::GetBit(bitmap_pointer[bit_number / (sizeof(T) * 8)], bit_number % (sizeof(T) * 8));
}

template<typename T>
void HBitmap<T>::SetBit(uint bit_number)
{
    ::SetBit(bitmap_pointer[bit_number / (sizeof(T) * 8)], bit_number % (sizeof(T) * 8));
}

template<typename T>
void HBitmap<T>::ClearBit(uint bit_number)
{
    ::ClearBit(bitmap_pointer[bit_number / (sizeof(T) * 8)], bit_number % (sizeof(T) * 8));
}

template<typename T>
T HBitmap<T>::FindFirstFreeBit()
{
    for(T i = 0; i < (bitmap_size / sizeof(T)); i++)    // Goes through each member of bitmap array from 0
    {
        for(T j = 0; j < (sizeof(T) * 8); j++)              // Goes through each bit; sizeof(T) * 8 -> Calculate bit number of type T
        {
            if(::IsBitSet(bitmap_pointer[i], j) == false)
                return (i * sizeof(T) * 8 + j);             // Calculation: i (-> Free array member) * sizeof(T) (-> Type size) * 8 (-> Bits per byte) + j (-> Free bit in array member)
        }
    }
    return -1;
}

template<typename T>
T HBitmap<T>::FindFirstFreeBits(size_t number_of_bits)
{
    T needed_bits = number_of_bits;
    for(T i = 0; i < (bitmap_size / sizeof(T)); i++)
    {
        for(T j = 0; j < (sizeof(T) * 8); j++)
        {
            if(needed_bits == 0)
                return i * sizeof(T) * 8 + (j - number_of_bits);

            if(::IsBitSet(bitmap_pointer[i], j) == false)
                needed_bits--;
        }
    }
    return -1;
}

template<typename T>
T HBitmap<T>::FindLastFreeBit()
{
    for(T i = bitmap_size / sizeof(T); i > 0; i--)          // Goes through each member of the bitmap array beginning with the last
    {
        for(T j = sizeof(T) * 8; j > 0; j--)                // Goes through each bit in reverse
        {
            if(::IsBitSet(bitmap_pointer[i], j) == false)
                return i * sizeof(T) * 8 + j;
        }
    }
}

template<typename T>
T HBitmap<T>::FindLastFreeBits(size_t number_of_bits)
{
    T needed_bits = number_of_bits;
    for(T i = bitmap_size / sizeof(T); i > 0; i--)
    {
        for(T j = sizeof(T) * 8; j > 0; j--)
        {
            if(::IsBitSet(bitmap_pointer[i], j) == false)
                needed_bits--;

            if(needed_bits == 0)
                return (i * sizeof(T) * 8 + j) - number_of_bits;
        }
    }
}

