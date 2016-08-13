#include "../include/dynamic_memory.hpp"


HDynamicMemory::HDynamicMemory(size_t size) :
{

}

HDynamicMemory::HDynamicMemory(HDynamicMemory &other_memory)
{

}

template<class T> HDynamicMemory::HDynamicMemory(HPointer<T> &pointer)
{

}

HDynamicMemory::~HDynamicMemory()
{

}

template<class T>
auto HDynamicMemory::GetAddress() -> HPointer<T>
{

}

auto HDynamicMemory::GetSize() const -> size_t
{

}

template<class T>
auto HDynamicMemory::GetData() const -> T &
{

}

template<class T>
auto HDynamicMemory::GetDataMember(const HInt position = HInteger()) const -> T &
{

}

template<class T>
auto HDynamicMemory::SetData(const HInt position = HInteger(), const HInt &value = HInteger())
{

}

void HDynamicMemory::Set(const HInt &value = HInteger())
{

}

void HDynamicMemory::Zero()
{

}

template<class T>
auto HDynamicMemory::CopyFrom(const HPointer<T> &pointer) -> bool
{

}

auto HDynamicMemory::CopyFrom(const HDynamicMemory &other_memory) -> bool
{

}

template<class T>
auto HDynamicMemory::MoveFrom(HPointer<T> &pointer) -> bool
{

}

auto HDynamicMemory::MoveFrom(HDynamicMemory &other_memory) -> bool
{

}
