#ifndef __LIST_CLASS__
#define __LIST_CLASS__

#include <Hybros/StdHelper>
#include <Hybros/StdTypes>
#include <Hybros/cMemory>

template<class T>
class HList
{
protected:
    class Node;

public:    
    class Iterator
    {
    public:
        Iterator(Node *node);
        Iterator(const Iterator &iterator);
        ~Iterator() = default;

        auto GetNode() const -> T &;

        auto operator *() -> T &;
        auto operator ==(const Iterator &other_it) -> bool;
        auto operator !=(const Iterator &other_it) -> bool;
        auto operator++(int) -> Iterator &;
        auto operator--(int) -> Iterator &;

    private:
        Node *current_node;
    };

    HList();
    HList(const T &first_data);
    HList(const HList<T> &other_list);
    HList(HList<T> &&other_list);
    ~HList();

    void Clear();
    auto IsEmpty() const -> bool;
    auto IsPresent(const T &data) const -> bool;
    auto GetSize() const -> size_t;
    auto GetCount() const -> size_t;

//    auto GetFirstNode() const -> Node *;
//    auto GetLastNode() const -> Node *;

    auto GetFirstElement() -> T&;
    auto GetLastElement() -> T&;
    auto GetElement(uint &position) -> T&;               // Returns also the position where the object were returned from
    auto GetPosition(const T &data) -> uint;             // Returns 0xFFFFFFFF if data is not part of the list

    virtual void PushFirstElement(const T &data);
    virtual void PushLastElement(const T &data);
    virtual void InsertElement(const T &data, uint position);

    virtual void PopFirstElement();
    virtual void PopLastElement();
    virtual void EraseElement(uint position);
    virtual void RemoveElement(const T &data);

    auto Begin() const -> Iterator;
    auto End() const -> Iterator;

    void operator = (const HList<T> &other_list);
    void operator = (HList<T> &&other_list);

    virtual auto operator <<(const T &data) -> HList<T> &;
    auto operator [](uint position) -> T &;
    auto operator  <(const HList<T> &other_list) -> bool;
    auto operator <=(const HList<T> &other_list) -> bool;
    auto operator  >(const HList<T> &other_list) -> bool;
    auto operator >=(const HList<T> &other_list) -> bool;
    auto operator ==(const HList<T> &other_list) -> bool;

protected:
    struct Node
    {
        Node *node_prev, *node_next;
        uint node_position;
        T node_data;

        Node();
        Node(T data, uint position = 0);
        Node(T data, uint position, Node *next = nullptr);
        Node(T data, uint position, Node *prev, Node *next = nullptr);
        ~Node();
    };

    Node *list_first, *list_last;
    size_t list_count;               // Number of nodes in list
    size_t list_size;                // Actual size

    auto GetNode(uint &position) -> Node *;
    auto GetNode(const T &data, bool insert = true) -> Node *;
    void UpdatePosition(HList<T>::Node *start_node, bool negative);
};

#endif
