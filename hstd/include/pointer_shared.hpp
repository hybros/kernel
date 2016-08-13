#ifndef __SHARED_POINTER__
#define __SHARED_POINTER__

#include "reference_counter.hpp"

template<class T>
class HSharedPointer
{
public:
    HSharedPointer() = default;
    HSharedPointer(T *other_pointer);
    HSharedPointer(const HSharedPointer<T> &other_pointer);
    ~HSharedPointer();

    auto IsValid() const -> bool;
    auto IsShared() const -> bool;

    auto GetCount() const -> size_t;

    void Release();
    auto Reset(T *other_pointer) -> bool;
    auto Reset(const HSharedPointer<T> &other_pointer) -> bool;

    auto operator =(T *other_pointer) -> HSharedPointer &;
    auto operator =(const HSharedPointer<T> &other_pointer) -> HSharedPointer &;

protected:
    T *pointer;
    HReferenceCounter *pointer_counter;
};

#endif
