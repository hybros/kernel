#include "../include/reference_server.hpp"

namespace kernel
{
namespace hstd
{

template<class T>
HReferenceServer<T>::HReferenceServer(const T &object) : reference(object) {}

template<class T>
HReferenceServer<T>::~HReferenceServer()
{
    for(HList<HInt>::Iterator it = unique_ref_ids.Begin(); it != unique_ref_ids.End(); it++)
        delete unique_ref_ids.EraseElement(*it);
}

template<class T>
bool HReferenceServer<T>::IsEmpty() const
{
    return unique_ref_ids.IsEmpty();
}

template<class T>
HInt HReferenceServer<T>::AddReference(const HReference<T> &reference)
{
    HInt new_id = unique_ref_ids.GetLastElement();
    new_id++;
    unique_ref_ids.PushLastElement(new_id);
    reference.
}

template<class T>
void HReferenceServer<T>::RemoveReference(uint unique_id)
{

}

template<class T>
HReferenceServer<T>::operator T() const
{

}

}
}
