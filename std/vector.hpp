#ifndef __VECTOR_CLASS__
#define __VECTOR_CLASS__

#include "data_types.hpp"
#include "memory.hpp"

namespace kernel
{
namespace std DLL_PUBLIC
{

template<typename T>
class Vector
{
public:
    Vector();
    Vector(const size_t size);
    Vector(const Vector<T> &vector);
    ~Vector();

    inline bool IsEmpty();
    inline size_t GetSize();
    inline size_t GetCapacity();
    inline void *GetBuffer();
    inline T &GetFirstElement();
    inline T &GetLastElement();
    inline T &GetElement(uint position);

    void Resize(const size_t size);

    void PushFirstElement(const T &t);
    void PopFirstElement();
    void PushLastElement(const T &t);
    void PopLastElement();

    inline T &operator [] (uint position);

protected:
    T *vector_buffer;
    size_t vector_capacity;
    size_t vector_size;
};

// ~ Vector

template<typename T>
Vector<T>::Vector() : vector_buffer(nullptr), vector_capacity(0), vector_size(0) {}

template<typename T>
Vector<T>::Vector(const size_t size) : vector_buffer(new T[size]), vector_capacity(size), vector_size(size) {}

template<typename T>
Vector<T>::Vector(const Vector<T> &vector)
{
    void *old_buffer = vector.GetBuffer();
    if(old_buffer != nullptr)
    {
        vector_capacity = vector.GetCapacity();
        vector_size = vector.GetSize();
        memcpy(vector_buffer, old_buffer, vector_size);
    }
}

template<typename T>
Vector<T>::~Vector()
{
    delete vector_buffer;
}

template<class T>
bool Vector<T>::IsEmpty()
{
    return (vector_capacity == 0) ? true : false;
}

template<class T>
size_t Vector<T>::GetSize()
{
    return vector_size;
}

template<class T>
size_t Vector<T>::GetCapacity()
{
    return vector_capacity;
}

template<class T>
void *Vector<T>::GetBuffer()
{
    return vector_buffer;
}

template<class T>
T &Vector<T>::GetFirstElement()
{
    return vector_buffer[0];
}

template<class T>
T &Vector<T>::GetLastElement()
{
    return vector_buffer[vector_size];
}

template<class T>
T &Vector<T>::GetElement(uint position)
{
    return vector_buffer[position];
}

template<typename T>
void Vector<T>::Resize(const size_t size)
{
    if(vector_capacity < size)
    {
        void *tmp_ptr = vector_buffer;
        vector_buffer = new T[size];
        delete tmp_ptr;

        vector_capacity = size;
    }
}

template<class T>
void Vector<T>::PushFirstElement(const T &t)
{
    if(vector_size + sizeof(T) < vector_capacity)
        Resize(vector_size + sizeof(T));
    
    void *old_pointer = vector_buffer + sizeof(T);
    memmove(old_pointer, vector_buffer, vector_size);

    vector_size += sizeof(T);
    memcpy(vector_buffer, &t, sizeof(T));
}

template<class T>
void Vector<T>::PopFirstElement()
{
    void *old_pointer = vector_buffer + sizeof(T);
    vector_size -= sizeof(T);
    memmove(vector_buffer, old_pointer, vector_size);
}

template<class T>
void Vector<T>::PushLastElement(const T &t)
{
    if(vector_size + sizeof(T) < vector_capacity)
        Resize(vector_size + sizeof(T));

    vector_size += sizeof(T);
    memcpy(vector_buffer + vector_size, &t, sizeof(T));
}

template<class T>
void Vector<T>::PopLastElement()
{
    vector_size -= sizeof(T);
    memzero(vector_buffer + vector_size, sizeof(T));
}

template<class T>
T &Vector<T>::operator[] (uint position)
{
    return vector_buffer[position];
}

}
}



#endif // __VECTOR_CLASS__
