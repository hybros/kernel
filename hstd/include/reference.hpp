#ifndef __REFERENCE_WITH_ID__
#define __REFERENCE_WITH_ID__

#include <HStdTypes>
#include <HInteger>
#include <HList>

template<class T> class HReferenceServer;

// Specifies a unique reference
template<class T>
class HUniqueReference
{
public:
    HUniqueReference(const HReferenceServer<T> &server);
    ~HUniqueReference();

    inline T &GetReference() const;
    inline uint GetUniqueId() const;

    void operator =(const T &new_reference);

    operator T() const;

private:
    const uint reference_id;
    HReferenceServer<T> &reference_server;
};

template<class T> using HUniRef = HUniqueReference<T>;

template<class T>
HUniqueReference<T> MakeUniqueRef(const T &object);

#endif
