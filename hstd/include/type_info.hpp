#ifndef __TYPE_INFORMATION__
#define __TYPE_INFORMATION__

#include "data_types.hpp"
#include "string.hpp"

template<typename T>
struct TypeName;

#define TYPE_NAME_TO_STRING(x) template<> struct TypeName<x> {static const char *name = #x;}

inline size_t ELFHash(const char *str)
{
    size_t hash = 0;
    uint x = 0;
   for(size_t i = 0; i < strlen(str); i++)
   {
      hash = (hash << 4) + str[i];
      if((x = hash & 0xF0000000L) != 0)
      {
         hash ^= (x >> 24);
      }
      hash &= ~x;
   }

   return hash;
}

template<class T>
struct HTypeInfo
{
    TYPE_NAME_TO_STRING(T);

    const size_t type_id = ELFHash(TypeName<T>::name);
};

#endif // __TYPE_INFORMATION__

