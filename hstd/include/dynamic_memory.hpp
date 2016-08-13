#ifndef __DYNAMIC_MEMORY__
#define __DYNAMIC_MEMORY__

#include <HPointer>
#include <HInteger>

class HDynamicMemory
{
public:
    inline HDynamicMemory() = default;
    inline HDynamicMemory(size_t size);
    inline HDynamicMemory(HDynamicMemory &other_memory);
    template<class T> inline HDynamicMemory(HPointer<T> &pointer);
    inline ~HDynamicMemory();

    template<class T> auto GetAddress() -> HPointer<T>;
    auto GetSize() const -> size_t;

    template<class T> auto GetData() const -> T &;
    template<class T> auto GetDataMember(const HInt position = HInteger()) const -> T &;
    template<class T> auto SetData(const HInt position = HInteger(), const HInt &value = HInteger());

    void Set(const HInt &value = HInteger());
    void Zero();

    template<class T> auto CopyFrom(const HPointer<T> &pointer) -> bool;
    auto CopyFrom(const HDynamicMemory &other_memory) -> bool;

    template<class T> auto MoveFrom(HPointer<T> &pointer) -> bool;
    auto MoveFrom(HDynamicMemory &other_memory) -> bool;

protected:
    class AbstractHelper
    {
        virtual ~AbstractHelper() {}
    };

    template<class T>
    struct Helper
    {
        HPointer<T> memory_address;
        size_t memory_size;
    };

    AbstractHelper *helper;
};

#endif
