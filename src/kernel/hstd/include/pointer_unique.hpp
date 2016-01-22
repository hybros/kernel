#ifndef __UNIQUE_POINTER__
#define __UNIQUE_POINTER__


template<class T>
class HUniquePointer
{
public:
    HUniquePointer() = default;
    HUniquePointer(T *new_pointer);
    HUniquePointer(const HUniquePointer<T> &other_pointer) = delete;
    HUniquePointer(HUniquePointer<T> &&other_pointer);
    ~HUniquePointer();

    auto IsValid() const -> bool;

    void Reset(T *other_pointer);

    auto operator =(T *other_pointer) -> HUniquePointer<T> &;
    auto operator =(const HUniquePointer<T> &other_pointer) -> HUniquePointer<T> & = delete;
    auto operator =(HUniquePointer<T> &&other_pointer) -> HUniquePointer<T> &;

private:
    T *pointer;
};


#endif
