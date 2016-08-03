#ifndef __TUPLE__
#define __TUPLE__

#include <HStdTypes>

// Implementation based on http://codereview.stackexchange.com/questions/44546/very-basic-tuple-implementation

template <typename T>
struct ID { using type = T; };

template <typename T>
using type_of = typename T::type;

template <size_t... N>
struct Sizes : ID <Sizes <N...> > { };

// choose N-th element in list <T...>
template <size_t N, typename... T>
struct Choose;

template <size_t N, typename H, typename... T>
struct Choose <N, H, T...> : Choose <N-1, T...> { };

template <typename H, typename... T>
struct Choose <0, H, T...> : ID <H> { };

template <size_t N, typename... T>
using choose = type_of <Choose <N, T...> >;

// given L>=0, generate sequence <0, ..., L-1>
template <size_t L, size_t I = 0, typename S = Sizes <> >
struct Range;

template <size_t L, size_t I, size_t... N>
struct Range <L, I, Sizes <N...> > : Range <L, I+1, Sizes <N..., I> > { };

template <size_t L, size_t... N>
struct Range <L, L, Sizes <N...> > : Sizes <N...> { };

template <size_t L>
using range = type_of <Range <L> >;

// single tuple element
template <size_t N, typename T>
class TupleElem
{
public:
    const T& Get() const { return data; }

private:
    T data;
};

// tuple implementation
template <typename N, typename... T>
class TupleImpl;

template <size_t... N, typename... T>
class TupleImpl <Sizes <N...>, T...> : TupleElem <N, T>...
{
    template <size_t M> using pick = Choose <M, T...>;
    template <size_t M> using elem = TupleElem <M, pick <M> >;

public:
    template <size_t M>
    const pick<M>& Get() const { return elem<M>::Get(); }
};

template <typename... T>
struct Tuple : TupleImpl <range<sizeof...(T)>, T...>
{
    static constexpr size_t GetSize() { return sizeof...(T); }
};

#endif // __TUPLE__

