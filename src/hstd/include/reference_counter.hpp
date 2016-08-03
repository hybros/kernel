#ifndef __REFERENCE_COUNTER__
#define __REFERENCE_COUNTER__

#include <HStdTypes>

class HReferenceCounter
{
public:
    auto GetCount() const -> size_t;

    void IncreaseCounter();
    auto DecreaseCounter() -> size_t;

    auto operator new(size_t size) -> void *;
    void operator delete(void *pointer);

private:
    size_t ref_count;
};

#endif
