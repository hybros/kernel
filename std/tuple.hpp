#ifndef __TUPLE__
#define __TUPLE__

#include "data_types.hpp"

namespace kernel
{
namespace std
{
namespace internal
{

template<size_t Index, class T>
struct TupleElement
{
    TupleElement(T &data);

protected:
    T element;
};

}

template<class ...Rest>
class Tuple : private internal::TupleElement<sizeof ...(Rest), Rest...>
{
public:
    Tuple();
    Tuple(Tuple<Rest...> &other_tuple);
};

// Tuple

template<class ... Rest>
Tuple<Rest...>::Tuple()
{

}

}
}

#endif // __TUPLE__

