#ifndef __VECTOR_CLASS__
#define __VECTOR_CLASS__

#include <Hybros/StdTypes>
#include <Hybros/cMemory>

///<summary>
///This is a continuous cohesive container for any type of data
///</summary>
template<typename T>
class HVector
{
public:
    class Iterator
    {
    public:
        Iterator(T *vector_pointer, uint current_position);
        Iterator(const Iterator &iterator);
        ~Iterator() = default;

        auto operator *() -> T &;
        auto operator ==(const Iterator &other_it) -> bool;
        auto operator !=(const Iterator &other_it) -> bool;
        auto operator ++(int) -> Iterator &;
        auto operator --(int) -> Iterator &;

    private:
        T *vector;
        uint position;
    };

    HVector();
    HVector(const size_t size);
    HVector(const HVector<T> &vector);
    HVector(HVector<T> &&vector);
    ~HVector();

    auto IsEmpty() const -> bool;
    auto HasMaximumReached() const -> bool;

    auto GetSize() const -> size_t;
    auto GetCapacity() const -> size_t;
	auto GetNumberOfElements() const -> size_t;

    virtual auto Resize(const size_t size) -> bool;

	///<summary>Gets the first element</summary>
	///<returns>The first element</returns>
    auto GetFirstElement() -> T &;
    auto GetLastElement() -> T &;
    auto GetElement(uint position) -> T &;
    auto GetPosition(const T &data) -> uint;

	auto AddElement(const T &data) -> bool;
    auto PushFirstElement(const T &data) -> bool;
    auto PushLastElement(const T &data) -> bool;
    auto InsertElement(const T &data, uint position) -> bool;

    void PopFirstElement();
    void PopLastElement();
    auto EraseElement(uint position) -> bool;
    auto RemoveElement(const T &data) -> bool;
	auto TakeElement(uint position) -> T;

    auto GetSubVector(uint from, uint to) const -> HVector<T> &;
    auto CreateSubVector(uint from, uint to) const -> HVector<T>;

    auto operator =(const HVector<T> &other_vector) -> HVector<T> &;
    auto operator =(HVector<T> &&other_vector) -> HVector<T> &;

    auto operator [](uint position) -> T &;
	auto operator [](uint position) const -> const T &;

	///<summary>Adds an element to the vector's end</summary>
	///<param name='data'>A reference to data to add</param>
	///<returns>A reference to itself</returns>
	auto operator <<(const T &data) -> HVector<T> &;

	///<summary>Adds another vector to this vector's end</summary>
	auto operator <<(const HVector<T> &other_vector) -> HVector<T> &;

	///<summary>Extracts the currently last element</summary>
	///<remarks>This operation will delete the element in the vector itself</remarks>
	auto operator >>(T &data) -> HVector<T> &;

    auto Begin() const -> Iterator;
    auto End() const -> Iterator;

protected:
    T *vector_buffer;
    size_t vector_capacity;
    size_t vector_size;

    auto LastPosition() const -> uint;
};

#endif // __VECTOR_CLASS__
