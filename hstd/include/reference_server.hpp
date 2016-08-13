#ifndef __REFERENCE_SERVER__
#define __REFERENCE_SERVER__

#include "reference.hpp"

// Manages the reference to a certain object
//  [*] Each reference is unique and accessable through its id
template<class T>
class HReferenceServer
{
public:
    HReferenceServer(const T &object);
    ~HReferenceServer();

    bool IsEmpty() const;

    auto AddReference(const HReference<T> &reference) -> uint;
    void RemoveReference(uint unique_id);

    operator T() const;

private:
    const T &reference;
    HList<uint> unique_ref_ids;
};

#endif
