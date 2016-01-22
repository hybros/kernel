#ifndef __BITMAP__
#define __BITMAP__

#include "data_types.hpp"
#include "helper.hpp"
#include "bits.hpp"
#include "memory.hpp"

namespace kernel
{
namespace std DLL_PUBLIC
{

template<typename T>
class Bitmap
{
public:
    Bitmap();
    Bitmap(size_t size, uchar value = 0);
    ~Bitmap();

    void Clear();
    void Reset(uchar value);
    void Resize(size_t size);

    inline bool IsBitSet(uint bit_number);
    inline T GetBit(uint bit_number);
    inline void SetBit(uint bit_number);
    inline void ClearBit(uint bit_number);

    T FindFirstFreeBit();
    T FindFirstFreeBits(uint number_of_bits);
    T FindLastFreeBit();
    T FindLastFreeBits(uint number_of_bits);

    Bitmap &operator << (uint number_of_bits);
    Bitmap &operator >> (uint number_of_bits);

protected:
    DLL_LOCAL T *bitmap_pointer;
    DLL_LOCAL size_t bitmap_size;
};

// ~ Bitmap

template<typename T>
Bitmap<T>::Bitmap() : bitmap_pointer(nullptr), bitmap_size(0) {}

template<typename T>
Bitmap<T>::Bitmap(size_t size, uchar value) : bitmap_pointer(new T[size / sizeof(T)]), bitmap_size(size)
{
    if(value == 0)
        Clear();
    else
        Reset(value);
}

template<typename T>
Bitmap<T>::~Bitmap()
{
    Clear();
    delete bitmap_pointer;
    bitmap_size = 0;
}

template<typename T>
void Bitmap<T>::Clear()
{
    Memory<T>::Zero(*bitmap_pointer, bitmap_size);
}

template<typename T>
void Bitmap<T>::Reset(uchar value)
{
    Memory<T>::Set(*bitmap_pointer, value, bitmap_size);
}

template<typename T>
void Bitmap<T>::Resize(size_t size)
{
    if(bitmap_size < size)
    {
        void *tmp_ptr = bitmap_pointer;
        bitmap_pointer = new T[size / sizeof(T)];
        delete tmp_ptr;
    }
}

template<typename T>
bool Bitmap<T>::IsBitSet(uint bit_number)
{
    return std::IsBitSet(bitmap_pointer[bit_number / (sizeof(T) * 8)], bit_number % (sizeof(T) * 8));
}

template<typename T>
T Bitmap<T>::GetBit(uint bit_number)
{
    return std::GetBit(bitmap_pointer[bit_number / (sizeof(T) * 8)], bit_number % (sizeof(T) * 8));
}

template<typename T>
void Bitmap<T>::SetBit(uint bit_number)
{
    std::SetBit(bitmap_pointer[bit_number / (sizeof(T) * 8)], bit_number % (sizeof(T) * 8));
}

template<typename T>
void Bitmap<T>::ClearBit(uint bit_number)
{
    std::ClearBit(bitmap_pointer[bit_number / (sizeof(T) * 8)], bit_number % (sizeof(T) * 8));
}

template<typename T>
T Bitmap<T>::FindFirstFreeBit()
{
    for(T i = 0; i < (bitmap_size / sizeof(T)); i++)    // Goes through each member of bitmap array from 0
    {
        for(T j = 0; j < (sizeof(T) * 8); j++)              // Goes through each bit; sizeof(T) * 8 -> Calculate bit number of type T
        {
            if(std::IsBitSet(bitmap_pointer[i], j) == false)
                return (i * sizeof(T) * 8 + j);             // Calculation: i (-> Free array member) * sizeof(T) (-> Type size) * 8 (-> Bits per byte) + j (-> Free bit in array member)
        }
    }
    return -1;
}

template<typename T>
T Bitmap<T>::FindFirstFreeBits(uint number_of_bits)
{
    uint needed_bits = number_of_bits;
    for(T i = 0; i < (bitmap_size / sizeof(T)); i++)
    {
        for(T j = 0; j < (sizeof(T) * 8); j++)
        {
            if(needed_bits == 0)
                return i * sizeof(T) * 8 + (j - number_of_bits);

            if(std::IsBitSet(bitmap_pointer[i], j) == false)
                needed_bits--;
        }
    }
    return -1;
}

template<typename T>
T Bitmap<T>::FindLastFreeBit()
{
    for(T i = bitmap_size / sizeof(T); i > 0; i--)          // Goes through each member of the bitmap array beginning with the last
    {
        for(T j = sizeof(T) * 8; j > 0; j--)                // Goes through each bit in reverse
        {
            if(std::IsBitSet(bitmap_pointer[i], j) == false)
                return i * sizeof(T) * 8 + j;
        }
    }
}

template<typename T>
T Bitmap<T>::FindLastFreeBits(uint number_of_bits)
{
    T needed_bits = number_of_bits;
    for(T i = bitmap_size / sizeof(T); i > 0; i--)
    {
        for(T j = sizeof(T) * 8; j > 0; j--)
        {
            if(std::IsBitSet(bitmap_pointer[i], j) == false)
                needed_bits--;

            if(needed_bits == 0)
                return (i * sizeof(T) * 8 + j) - number_of_bits;
        }
    }
}

}
}

#endif // __BITMAP__
