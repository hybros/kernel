#ifndef __SMART_POINTER__
#define __SMART_POINTER__

#include "data_types.hpp"
#include "list.hpp"

namespace kernel
{
namespace std
{

template<class T>
class SmartPointer
{
public:
    SmartPointer();
    SmartPointer(const T *pointer);
    SmartPointer(const SmartPointer<T> &other_pointer);
    ~SmartPointer();

    void Reset(const T *pointer = nullptr);
    bool IsUnique();
    T *GetPointer();
    inline void *GetCounter();
    inline size_t GetReferenceCount();

    T *operator -> ();
    T &operator * ();
    T &operator ();

    void operator = (const T *new_pointer);
    void operator = (const SmartPointer<T> &other_pointer);

private:
    T *sp_pointer;
    ReferenceCounter *sp_count;
};

template<class T>
List<SmartPointer<T>>::~List()
{
    Clear();
}

// ~ SmartPointer

template<class T>
SmartPointer::SmartPointer() : sp_pointer(nullptr), sp_count(new ReferenceCounter) {}

template<class T>
SmartPointer::SmartPointer(const T *pointer) : sp_pointer(pointer), sp_count(new ReferenceCounter) {}

template<class T>
SmartPointer::SmartPointer(const SmartPointer<T> &other_pointer) : sp_pointer(other_pointer.GetPointer()), sp_count(other_pointer.GetCounter())
{
    sp_count->IncreaseCounter();
}

template<class T>
SmartPointer::~SmartPointer()
{
    if(sp_count && sp_count->DecreaseCounter() == 0)
        delete sp_pointer;
}

}
}

#endif // __SMART_POINTER__

