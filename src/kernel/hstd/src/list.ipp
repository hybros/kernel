#include "../include/list.hpp"

#include <cMemory>

template<class T>
HList<T>::HList() : list_first(nullptr), list_last(nullptr), list_size(0), list_count(0) {}

template<class T>
HList<T>::HList(const T &first_data)
{
    PushFirstElement(first_data);
}

template<class T>
HList<T>::HList(const HList<T> &other_list)
{
    if(other_list.IsEmpty() == true)
        return;

    PushFirstElement(other_list.GetFirstElement());
    for(uint i = 1; i < other_list.GetCount(); i++)
    {
        PushLastElement(other_list.GetElement(i));
    }
}

template<class T>
HList<T>::HList(HList<T> &&other_list)
{
    if(other_list.IsEmpty() == true)
        return;

    list_count = other_list.list_count;
    list_size = other_list.list_size;
    list_first = other_list.list_first;
    list_last = other_list.list_last;

    other_list.list_count = 0;
    other_list.list_size = 0;
    other_list.list_first = nullptr;
    other_list.list_last = nullptr;
}

template<class T>
HList<T>::~HList()
{
    Clear();
}

template<class T>
void HList<T>::Clear()
{
    Node *current_node = list_first;
    while(current_node != list_last)
    {
        Node *next_node = current_node->node_next;
        delete current_node;
        current_node = next_node;
    }
}

template<class T>
bool HList<T>::IsEmpty() const
{
    return (list_count == 0) ? true : false;
}

template<class T>
bool HList<T>::IsPresent(const T &data) const
{
    return (GetNode(data, false) != nullptr) ? true : false;
}

template<class T>
size_t HList<T>::GetSize() const
{
    return list_size;
}

template<class T>
size_t HList<T>::GetCount() const
{
    return list_count;
}

//template<class T>
//auto HList<T>::GetFirstNode() const -> Node *
//{
//    return list_first;
//}

//template<class T>
//auto HList<T>::GetLastNode() const -> Node *
//{
//    return list_last;
//}

template<class T>
T &HList<T>::GetFirstElement()
{
    return list_first->node_data;
}

template<class T>
T &HList<T>::GetLastElement()
{
    return list_last->node_data;
}

template<class T>
T &HList<T>::GetElement(uint &position)
{
    return GetNode(position)->node_data;
}

template<class T>
uint HList<T>::GetPosition(const T &data)
{
    return GetNode(data)->node_position;
}

template<class T>
void HList<T>::PushFirstElement(const T &data)
{
    Node *new_first = new Node(data, 0, nullptr, list_first);
    list_first = new_first;
    list_size += sizeof(Node);
    UpdatePosition(list_first->node_next, false);
}

template<class T>
void HList<T>::PushLastElement(const T &data)
{
    Node *new_last = new Node(data, list_count, list_last, nullptr);
    list_last = new_last;
    list_size += sizeof(Node);
    list_count++;
}

template<class T>
void HList<T>::InsertElement(const T &data, uint position)
{
    Node *current_node = GetNode(position);
    Node *new_node = new Node(data, position, current_node->node_prev, current_node);
    current_node->node_prev = new_node;

    list_size += sizeof(Node);
    UpdatePosition(current_node, false);
}

template<class T>
void HList<T>::PopFirstElement()
{
    Node *new_first_node = list_first->node_next;
    new_first_node->node_prev = nullptr;

    UpdatePosition(new_first_node, true);
    delete list_last;
    list_size -= sizeof(Node);
}

template<class T>
void HList<T>::PopLastElement()
{
    Node *new_last_node = list_last->node_prev;
    new_last_node->node_next = nullptr;
    new_last_node->node_position--;
    list_count--;
    delete list_last;
    list_size -= sizeof(Node);
}

template<class T>
void HList<T>::EraseElement(uint position)
{
    Node *current_element = GetNode(position);
    Node *prev_element = current_element->node_prev;
    prev_element->node_next = current_element->node_next;

    UpdatePosition(prev_element, true);
    delete current_element;
    list_size -= sizeof(Node);
}

template<class T>
void HList<T>::RemoveElement(const T& data)
{
    Node *current_element = GetNode(data);
    Node *prev_element = current_element->node_prev;
    prev_element->node_next = current_element->node_next;

    UpdatePosition(prev_element, true);
    delete current_element;
    list_size -= sizeof(Node);
}

template<class T>
typename HList<T>::Iterator HList<T>::Begin() const
{
    return Iterator(list_first);
}

template<class T>
typename HList<T>::Iterator HList<T>::End() const
{
    return Iterator(list_last);
}

template<class T>
void HList<T>::operator =(const HList<T> &other_list)
{
    if(other_list.IsEmpty() == true)
        return;

    Clear();

    PushFirstElement(other_list.GetFirstElement());
    for(uint i = 1; i < other_list.GetCount(); i++)
    {
        PushLastElement(other_list.GetElement(i));
    }
}

template<class T>
void HList<T>::operator =(HList<T> &&other_list)
{
    if(other_list.IsEmpty() == true)
        return;

    Clear();

    list_count = other_list.list_count;
    list_size = other_list.list_size;
    list_first = other_list.list_first;
    list_last = other_list.list_last;

    other_list.list_count = 0;
    other_list.list_size = 0;
    other_list.list_first = nullptr;
    other_list.list_last = nullptr;
}

template<class T>
HList<T> &HList<T>::operator << (const T &data)
{
    PushLastElement(data);
    return THIS;
}

template<class T>
T &HList<T>::operator [] (uint position)
{
    return GetElement(position);
}

template<class T>
bool HList<T>::operator < (const HList<T> &other_list)
{
    return (list_count < other_list.GetCount()) ? true :  false;
}

template<class T>
bool HList<T>::operator <= (const HList<T> &other_list)
{
    return (list_count <= other_list.GetCount()) ? true :  false;
}
template<class T>
bool HList<T>::operator > (const HList<T> &other_list)
{
    return (list_count > other_list.GetCount()) ? true :  false;
}

template<class T>
bool HList<T>::operator >= (const HList<T> &other_list)
{
    return (list_count >= other_list.GetCount()) ? true :  false;
}

template<class T>
bool HList<T>::operator == (const HList<T> &other_list)
{
    return (list_count == other_list.GetCount()) ? true : false;
}

template<class T>
typename HList<T>::Node *HList<T>::GetNode(uint &position)
{
    Node *current_node = nullptr;
    if(position == 0)
        return list_first;
    else if(position >= list_count)
    {
        position = list_count;
        return list_last;
    }
    else if(position > (list_count / 2))
    {
        current_node = list_last;
        while(current_node->node_position != position)
            current_node = current_node->node_prev;
    }
    else
    {
        current_node = list_first;
        while(current_node->node_position != position)
            current_node = current_node->node_next;
    }

    position = current_node->node_position;
    return current_node;
}

template<class T>
typename HList<T>::Node *HList<T>::GetNode(const T &data, bool insert)
{
    Node *current_node = list_first;
    while(current_node->node_next != nullptr)
    {
        if(memcmp(&current_node->node_data, &data, sizeof(T)) == 0)
            return current_node;

        current_node = current_node->node_prev;
    }

    if(insert == true)
    {
        PushLastElement(data);
        return list_last;
    }
    else
        return nullptr;
}

template<class T>
void HList<T>::UpdatePosition(Node *start_node, bool negative)
{
    Node *current_node = start_node;
    if(negative == false)
    {
        while(current_node->node_next != nullptr)
        {
            current_node = current_node->node_next;
            current_node->node_position++;
        }
        list_count++;
    }
    else
    {
        while(current_node->node_next != nullptr)
        {
            current_node = current_node->node_next;
            current_node->node_position--;
        }
        list_count--;
    }
}

template<class T>
HList<T>::Iterator::Iterator(Node *node) : current_node(node) {}

template<class T>
HList<T>::Iterator::Iterator(const Iterator &iterator) : current_node(iterator.GetNode()) {}

template<class T>
T &HList<T>::Iterator::operator*()
{
    return current_node->node_data;
}

template<class T>
bool HList<T>::Iterator::operator ==(const Iterator &other_it)
{
    return (current_node == other_it.GetNode()) ? true : false;
}

template<class T>
bool HList<T>::Iterator::operator !=(const Iterator &other_it)
{
    return (current_node != other_it.GetNode()) ? true : false;
}

template<class T>
typename HList<T>::Iterator &HList<T>::Iterator::operator++(int)
{
    current_node = current_node->node_next;
    return THIS;
}

template<class T>
typename HList<T>::Iterator &HList<T>::Iterator::operator--(int)
{
    current_node = current_node->node_prev;
    return THIS;
}

template<class T>
HList<T>::Node::Node() : Node(0, 0, nullptr, nullptr) {}

template<class T>
HList<T>::Node::Node(T data, uint position) : Node(data, position, nullptr, nullptr) {}

template<class T>
HList<T>::Node::Node(T data, uint position, Node *next) : Node(data, position, nullptr, next) {}

template<class T>
HList<T>::Node::Node(T data, uint position, Node *prev, Node *next) : node_data(data), node_position(position), node_prev(prev), node_next(next) {}

template<class T>
HList<T>::Node::~Node()
{
    memzero(&node_data, sizeof(T));
}

