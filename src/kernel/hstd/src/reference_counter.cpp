#include "../include/reference_counter.hpp"

auto HReferenceCounter::GetCount() const -> size_t
{
    return ref_count;
}

void HReferenceCounter::IncreaseCounter()
{
    ref_count++;
}

auto HReferenceCounter::DecreaseCounter() -> size_t
{
    return (ref_count--);
}

auto HReferenceCounter::operator new(size_t size) -> void *
{

}

void HReferenceCounter::operator delete(void *pointer)
{

}

