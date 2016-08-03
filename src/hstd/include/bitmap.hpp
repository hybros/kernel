#ifndef __BITMAP__
#define __BITMAP__

#include <HStdTypes>

template<typename T>
class HBitmap
{
public:
    HBitmap();
    HBitmap(size_t size, uchar value = 0);
    HBitmap(size_t size, const T *bitmap_array);
    ~HBitmap();

    void Clear();
    void Reset(uchar value);
    void Resize(size_t size);

    inline bool IsBitSet(uint bit_number);
    inline T GetBit(uint bit_number);
    inline void SetBit(uint bit_number);
    inline void ClearBit(uint bit_number);

    T FindFirstFreeBit();
    T FindFirstFreeBits(size_t number_of_bits);
    T FindLastFreeBit();
    T FindLastFreeBits(size_t number_of_bits);

    HBitmap &operator <<(uint number_of_bits);
    HBitmap &operator >>(uint number_of_bits);

protected:
    T *bitmap_pointer;
    size_t bitmap_size;
};


#endif // __BITMAP__
