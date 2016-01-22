#include "../include/vector.hpp"

template<typename T>
HVector<T>::HVector() :
    vector_buffer(nullptr),
    vector_capacity(0),
    vector_size(0)
{}

template<typename T>
HVector<T>::HVector(const size_t size) :
    vector_buffer(new T[size]),
    vector_capacity(size),
    vector_size(0)
{}

template<typename T>
HVector<T>::HVector(const HVector<T> &vector)
{
    if(vector.IsEmpty() == true)
        return;

    vector_capacity = vector.vector_capacity;
    vector_size = vector.vector_size;
    memcpy(vector_buffer, vector.vector_buffer, vector_size);
}

template<typename T>
HVector<T>::HVector(HVector<T> &&other_vector)
{
    if(other_vector.IsEmpty() == true)
        return;

    vector_capacity = other_vector.vector_capacity;
    vector_size = other_vector.vector_size;
    vector_buffer = other_vector.vector_buffer;

    other_vector.vector_capacity = 0;
    other_vector.vector_size = 0;
    other_vector.vector_buffer = nullptr;
}

template<typename T>
HVector<T>::~HVector()
{
    delete vector_buffer;
    vector_capacity = 0;
    vector_size = 0;
}

template<class T>
auto HVector<T>::IsEmpty() const -> bool
{
    // Checks if the vector is empty or the pointer is invalid (so it must be empty, too)
    return ((vector_size == 0) || (vector_buffer == nullptr)) ? true : false;
}

template<class T>
auto HVector<T>::HasMaximumReached() const -> bool
{
    return (vector_capacity > vector_size) ? false : true;
}

template<class T>
auto HVector<T>::GetSize() const -> size_t
{
    return vector_size;
}

template<class T>
auto HVector<T>::GetCapacity() const -> size_t
{
    return vector_capacity;
}

template<class T>
auto HVector<T>::GetNumberOfElements() const -> size_t
{
	return (vector_size / sizeof(T));
}

template<class T>
auto HVector<T>::GetFirstElement() -> T &
{
    return vector_buffer[0];
}

template<class T>
T &HVector<T>::GetLastElement()
{
    return vector_buffer[LastPosition()];
}

template<class T>
T &HVector<T>::GetElement(uint position)
{
    if(position && (position <= vector_size))
        return vector_buffer[position];
    else
        return vector_buffer[LastPosition()];
}

template<class T>
auto HVector<T>::GetPosition(const T &data) -> uint
{
    for(uint i = 0; i <= LastPosition(); i++)
    {
        if(memcmp(&vector_buffer[i], &data, sizeof(T)) == 0)
            return i;
    }
    return 0xFFFFFFFF;
}

template<typename T>
auto HVector<T>::Resize(const size_t size) -> bool
{
    if(vector_capacity < size)
    {
        T *old_buffer = vector_buffer;
        vector_buffer = new T[size];
        if(vector_buffer == nullptr)
        {
            vector_buffer = old_buffer;
            return false;
        }

        delete old_buffer;

        vector_capacity = size;
    }
    return true;
}

template<class T>
auto HVector<T>::AddElement(const T &data) -> bool
{
	return PushFirstElement(data);
}

template<class T>
auto HVector<T>::PushFirstElement(const T &data) -> bool
{
    if((vector_size + sizeof(T)) > vector_capacity)
    {
        if(Resize(vector_size + sizeof(T)) == false)
            return false;
    }
    
    T *new_buffer = vector_buffer + sizeof(T);
    memmove(new_buffer, vector_buffer, vector_size);

    vector_size += sizeof(T);
    memcpy(vector_buffer, &data, sizeof(T));
    return true;
}

template<class T>
auto HVector<T>::PushLastElement(const T &data) -> bool
{
    if((vector_size + sizeof(T)) > vector_capacity)
    {
        if(Resize(vector_size + sizeof(T)) == false)
            return false;
    }

    vector_size += sizeof(T);
    memcpy(&vector_buffer[LastPosition()], &data, sizeof(T));
    return true;
}

template<class T>
auto HVector<T>::InsertElement(const T &data, uint position) -> bool
{
    if((vector_size + sizeof(T)) > vector_capacity)
    {
        if(Resize(vector_size + sizeof(T)) == false)
            return false;
    }

    if(position == 0)
        return PushFirstElement(data);
    else if(position >= LastPosition())
        return PushLastElement(data);

    memmove(&vector_buffer[position + 1], &vector_buffer[position], vector_size - (sizeof(T) * position));

    vector_size += sizeof(T);
    memcpy(&vector_buffer[position], &data, sizeof(T));
    return true;
}

template<class T>
void HVector<T>::PopFirstElement()
{
    vector_size -= sizeof(T);
    memmove(vector_buffer, &vector_buffer[1], vector_size);             // Moves the second to the first element
}

template<class T>
void HVector<T>::PopLastElement()
{
    vector_size -= sizeof(T);
    memzero(vector_buffer + vector_size, sizeof(T));
}

template<class T>
auto HVector<T>::EraseElement(uint position) -> bool
{
    if(position == 0)
        PopFirstElement();
    else if(position == LastPosition())
        PopLastElement();
    else if(position > LastPosition())
        return false;

    memmove(&vector_buffer[position], &vector_buffer[position + 1], vector_size - (sizeof(T) * (position - 1)));
    vector_size -= sizeof(T);
    return true;
}

template<class T>
auto HVector<T>::RemoveElement(const T &data) -> bool
{
    return EraseElement(GetPosition(data));
}

template<class T>
auto HVector<T>::TakeElement(uint position) -> T
{
	T element = GetElement(position);
	EraseElement(position);
	return element;
}

template<class T>
auto HVector<T>::operator[](uint position) -> T &
{
    return GetElement(position);
}

template<class T>
auto HVector<T>::LastPosition() const -> uint
{
    return (vector_size / sizeof(T));
}

template<class T>
typename HVector<T>::Iterator HVector<T>::Begin() const
{
    return Iterator(vector_buffer, 0);
}

template<class T>
typename HVector<T>::Iterator HVector<T>::End() const
{
    return Iterator(vector_buffer, LastPosition());
}

template<class T>
HVector<T>::Iterator::Iterator(T *vector_address, uint current_position) :
    vector(vector_address),
    position(current_position)
{}

template<class T>
HVector<T>::Iterator::Iterator(const Iterator &iterator) :
    vector(iterator.vector),
    position(iterator.position)
{}

template<class T>
auto HVector<T>::Iterator::operator *() -> T &
{
    return vector[position];
}

template<class T>
bool HVector<T>::Iterator::operator ==(const Iterator &other_it)
{
    return (position == other_it.position) ? true : false;
}

template<class T>
bool HVector<T>::Iterator::operator !=(const Iterator &other_it)
{
    return (position != other_it.position) ? true : false;
}

template<class T>
typename HVector<T>::Iterator &HVector<T>::Iterator::operator++(int)
{
    position++;
    return THIS;
}

template<class T>
typename HVector<T>::Iterator &HVector<T>::Iterator::operator--(int)
{
    position--;
    return THIS;
}
