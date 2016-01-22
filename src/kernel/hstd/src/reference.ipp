#include "../include/reference.hpp"
#include "../include/reference_server.hpp"

template<class T>
HReference<T>::HReference(const HReferenceServer<T> &server) : reference_server(server), reference_id(server.AddReference(THIS)) {}

template<class T>
HReference<T>::~HReference()
{
    if(reference_server.IsEmpty())
       delete &reference_server;
}

template<class T>
auto HReference<T>::GetReference() const -> T &
{
    return reference_server;
}

template<class T>
auto HReference<T>::GetUniqueId() const -> uint
{
    return reference_id;
}

