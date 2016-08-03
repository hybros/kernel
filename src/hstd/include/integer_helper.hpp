#include "integer.hpp"

namespace kernel
{

inline auto operator +(const ulong integer, const HInteger &other_integer) -> ulong;

inline auto operator -(const ulong integer, const HInteger &other_integer) -> ulong;

inline auto operator *(const ulong integer, const HInteger &other_integer) -> ulong;

inline auto operator /(const ulong integer, const HInteger &other_integer) -> ulong;

inline void operator +=(const ulong integer, const HInteger &other_integer);

inline void operator -=(const ulong integer, const HInteger &other_integer);

inline void operator *=(const ulong integer, const HInteger &other_integer);

inline void operator /=(const ulong integer, const HInteger &other_integer);

inline auto operator  <(const ulong integer, const HInteger &other_integer) -> bool;

inline auto operator  >(const ulong integer, const HInteger &other_integer) -> bool;

inline auto operator <=(const ulong integer, const HInteger &other_integer) -> bool;

inline auto operator >=(const ulong integer, const HInteger &other_integer) -> bool;

inline auto operator ==(const ulong integer, const HInteger &other_integer) -> bool;

inline auto operator !=(const ulong integer, const HInteger &other_integer) -> bool;

inline auto operator  &(const ulong integer, const HInteger &other_integer) -> ulong;

inline auto operator  |(const ulong integer, const HInteger &other_integer) -> ulong;

inline auto operator  ^(const ulong integer, const HInteger &other_integer) -> ulong;

inline auto operator <<(const ulong integer, const HInteger &bit_number) -> ulong;

auto operator >>(const ulong integer, const HInteger &bit_number) -> ulong;

void operator  &=(const ulong integer, const HInteger &other_integer);

void operator  |=(const ulong integer, const HInteger &other_integer);

void operator  ^=(const ulong integer, const HInteger &other_integer);

void operator <<=(const ulong integer, const HInteger &bit_number);

void operator >>=(const ulong integer, const HInteger &bit_number);

//auto operator [](const ulong *integer_pointer, const HInteger &integer) -> ulong;

}
