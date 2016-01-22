#ifndef __PRE_MEMORY_MANAGEMENT__
#define __PRE_MEMORY_MANAGEMENT__

#include <HStdTypes>

inline void *operator new (size_t size, void *address) throw()
{
    return address;
}

inline void *operator new[] (size_t size, void *address) throw()
{
    return address;
}

#endif // __PRE_MEMORY_MANAGEMENT__

