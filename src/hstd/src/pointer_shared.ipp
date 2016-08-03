#include "../include/pointer_shared.hpp"

#include <HStdHelper>

template<class T>
HSharedPointer<T>::HSharedPointer(T *other_pointer) :
    pointer(other_pointer),
    pointer_counter(new HReferenceCounter)
{
}

template<class T>
HSharedPointer<T>::~HSharedPointer()
{
    Release();
}

template<class T>
auto HSharedPointer<T>::IsShared() const -> bool
{
    return (pointer_counter->GetCount() > 1) ? true : false;
}

template<class T>
auto HSharedPointer<T>::GetCount() const -> size_t
{
    return pointer_counter->GetCount();
}

template<class T>
void HSharedPointer<T>::Release()
{
    if(pointer_counter->DecreaseCounter() == 0)
    {
        delete pointer;
        delete pointer_counter;
    }
}

template<class T>
auto HSharedPointer<T>::Reset(T *other_pointer) -> bool
{
    Release();
    pointer = other_pointer;
    pointer_counter = new HReferenceCounter;
}

template<class T>
auto HSharedPointer<T>::Reset(const HSharedPointer<T> &other_pointer) -> bool
{
    Release();
    pointer = other_pointer.pointer;
    pointer_counter = other_pointer.pointer_counter;
    pointer_counter->IncreaseCounter();
    return true;
}

template<class T>
auto HSharedPointer<T>::operator =(T *other_pointer) -> HSharedPointer &
{
    Reset(other_pointer);
    return THIS;
}

template<class T>
auto HSharedPointer<T>::operator =(const HSharedPointer<T> &other_pointer) -> HSharedPointer &
{
    Reset(other_pointer);
    return THIS;
}
