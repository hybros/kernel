#include "../include/pointer_unique.hpp"

#include <HStdHelper>

template<class T>
HUniquePointer<T>::HUniquePointer(T *new_pointer) :
    pointer(new_pointer)
{
}

template<class T>
HUniquePointer<T>::HUniquePointer(HUniquePointer<T> &&other_pointer)
{
    pointer = other_pointer.pointer;
    other_pointer.pointer = nullptr;
}

template<class T>
HUniquePointer<T>::~HUniquePointer()
{
    delete pointer;
}

template<class T>
auto HUniquePointer<T>::IsValid() const -> bool
{
    if(pointer != nullptr)
        return true;
    else
        return false;
}

template<class T>
void HUniquePointer<T>::Reset(T *other_pointer)
{
    if(pointer != nullptr)
        delete pointer;

    pointer = other_pointer;
}

template<class T>
auto HUniquePointer<T>::operator =(T *other_pointer) -> HUniquePointer<T> &
{
    Reset(other_pointer);
    return THIS;
}

template<class T>
auto HUniquePointer<T>::operator =(HUniquePointer<T> &&other_pointer) -> HUniquePointer<T> &
{
    pointer = other_pointer.pointer;
    other_pointer.pointer = nullptr;
}
