#ifndef __LIST_CLASS__
#define __LIST_CLASS__

#include "data_types.hpp"
#include "helper.hpp"
#include "memory.hpp"

namespace kernel
{
namespace std DLL_PUBLIC
{

template<class T>
class List
{
    class Node;

public:
    List();
    List(void *first_element_memory);                   // NOTE: Probably unsafe
    List(const List<T> &list);
    ~List();

    inline void Clear();
    inline bool IsEmpty();
    inline bool IsPresent(const T &data);
    inline size_t GetSize();
    inline size_t GetCount();
    inline size_t GetNodeSize() const;
    inline T& GetFirstElement();
    inline T& GetLastElement();
    inline T& GetElement(uint &position);               // Returns also the position where the object were returned from
    inline uint GetPosition(const T &data);             // Returns 0xFFFFFFFF if data is not part of the list

    void PushFirstElement(const T &data);
    void PushLastElement(const T &data);
    void InsertElement(const T &data, uint position);

    void PopFirstElement();
    void PopLastElement();
    void EraseElement(uint position);
    void RemoveElement(const T &data);

    inline List<T> &operator << (const T &data);
    inline T &operator [] (uint position);
    inline bool operator < (const List<T> &other_list);
    inline bool operator <= (const List<T> &other_list);
    inline bool operator > (const List<T> &other_list);
    inline bool operator >= (const List<T> &other_list);
    inline bool operator == (const List<T> &other_list);

protected:
    Node *GetNode(uint &position);
    Node *GetNode(const T &data, bool insert = true);
    void UpdatePosition(List<T>::Node *start_node, bool negative);

private:
    class Node
    {
    public:
        Node();
        Node(T data, uint position = 0);
        Node(T data, uint position, Node *next = nullptr);
        Node(T data, uint position, Node *prev, Node *next = nullptr);
        ~Node();

        T node_data;
        uint node_position;
        Node *node_prev, *node_next;
    };

    Node *list_first, *list_last;
    size_t list_count;               // Number of nodes in list
    size_t list_size;                // Actual size
};

// ~ List

template<class T>
List<T>::List() : list_first(nullptr), list_last(nullptr), list_size(0), list_count(0) {}

template<class T>
List<T>::List(void *first_element_memory) : list_first(new (first_element_memory) Node), list_last(nullptr), list_size(sizeof(Node)), list_count(1) {}

template<class T>
List<T>::List(const List<T> &list) : list_first(list.GetFirst()), list_last(list.GetLast()), list_size(list.GetSize()) {}

template<class T>
List<T>::~List()
{
    Clear();
}

template<class T>
void List<T>::Clear()
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
bool List<T>::IsEmpty()
{
    return (list_count == 0) ? true : false;
}

template<class T>
bool List<T>::IsPresent(const T &data)
{
    return (GetNode(data, false) != nullptr) ? true : false;
}

template<class T>
size_t List<T>::GetSize()
{
    return list_size;
}

template<class T>
size_t List<T>::GetCount()
{
    return list_count;
}

template<class T>
size_t List<T>::GetNodeSize() const
{
    return sizeof(Node);
}

template<class T>
T &List<T>::GetFirstElement()
{
    return list_first->node_data;
}

template<class T>
T &List<T>::GetLastElement()
{
    return list_last->node_data;
}

template<class T>
T &List<T>::GetElement(uint &position)
{
    return GetNode(position)->node_data;
}

template<class T>
uint List<T>::GetPosition(const T &data)
{
    return GetNode(data)->node_position;
}

template<class T>
void List<T>::PushFirstElement(const T &data)
{
    Node *new_first = new Node(data, 0, nullptr, list_first);
    list_first = new_first;
    list_size += sizeof(Node);
    UpdatePosition(list_first->node_next, false);
}

template<class T>
void List<T>::PushLastElement(const T &data)
{
    Node *new_last = new Node(data, list_count, list_last, nullptr);
    list_last = new_last;
    list_size += sizeof(Node);
    list_count++;
}

template<class T>
void List<T>::InsertElement(const T &data, uint position)
{
    Node *current_node = GetNode(position);
    Node *new_node = new Node(data, position, current_node->node_prev, current_node);
    current_node->node_prev = new_node;

    list_size += sizeof(Node);
    UpdatePosition(current_node, false);
}

template<class T>
void List<T>::PopFirstElement()
{
    Node *new_first_node = list_first->node_next;
    new_first_node->node_prev = nullptr;

    UpdatePosition(new_first_node, true);
    delete list_last;
    list_size -= sizeof(Node);
}

template<class T>
void List<T>::PopLastElement()
{
    Node *new_last_node = list_last->node_prev;
    new_last_node->node_next = nullptr;
    new_last_node->node_position--;
    list_count--;
    delete list_last;
    list_size -= sizeof(Node);
}

template<class T>
void List<T>::EraseElement(uint position)
{
    Node *current_element = GetNode(position);
    Node *prev_element = current_element->node_prev;
    prev_element->node_next = current_element->node_next;

    UpdatePosition(prev_element, true);
    delete current_element;
    list_size -= sizeof(Node);
}

template<class T>
void List<T>::RemoveElement(const T& data)
{
    Node *current_element = GetNode(data);
    Node *prev_element = current_element->node_prev;
    prev_element->node_next = current_element->node_next;

    UpdatePosition(prev_element, true);
    delete current_element;
    list_size -= sizeof(Node);
}

template<class T>
List<T> &List<T>::operator << (const T &data)
{
    PushLastElement(data);
    return THIS;
}

template<class T>
T &List<T>::operator [] (uint position)
{
    return GetElement(position);
}

template<class T>
bool List<T>::operator < (const List<T> &other_list)
{
    return (list_count < other_list.GetCount()) ? true :  false;
}

template<class T>
bool List<T>::operator <= (const List<T> &other_list)
{
    return (list_count <= other_list.GetCount()) ? true :  false;
}
template<class T>
bool List<T>::operator > (const List<T> &other_list)
{
    return (list_count > other_list.GetCount()) ? true :  false;
}

template<class T>
bool List<T>::operator >= (const List<T> &other_list)
{
    return (list_count >= other_list.GetCount()) ? true :  false;
}

template<class T>
bool List<T>::operator == (const List<T> &other_list)
{
    return (list_count == other_list.GetCount()) ? true : false;
}

template<class T>
typename List<T>::Node *List<T>::GetNode(uint &position)
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
typename List<T>::Node *List<T>::GetNode(const T &data, bool insert)
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
void List<T>::UpdatePosition(Node *start_node, bool negative)
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
List<T>::Node::Node() : Node(0, 0, nullptr, nullptr) {}

template<class T>
List<T>::Node::Node(T data, uint position) : Node(data, position, nullptr, nullptr) {}

template<class T>
List<T>::Node::Node(T data, uint position, Node *next) : Node(data, position, nullptr, next) {}

template<class T>
List<T>::Node::Node(T data, uint position, Node *prev, Node *next) : node_data(data), node_position(position), node_prev(prev), node_next(next) {}

template<class T>
List<T>::Node::~Node()
{
    memzero(&node_data, sizeof(T));
}

}
}
#endif
