#ifndef __GENERAL_FUNCTIONS__
#define __GENERAL_FUNCTIONS__

#include <HStdTypes>

#define THIS (*this)

#define VAR_TO_PTR(x) reinterpret_cast<void*>(x)
#define VAR_TO_UCHAR_PTR(x) reinterpret_cast<uchar*>(x)
#define VAR_TO_UINT_PTR(x) reinterpret_cast<uint*>(x)
#define VAR_TO_PTR_VALUE(x) *(reinterpret_cast<uint*>(x))
#define VAR_TO_PTR_VALUE_W(x) *(reinterpret_cast<ushort*>(x))

#define PTR_TO_VAR(x) reinterpret_cast<ulong>(x)

#define OFFSETOF(type, member) ((size_t) & (((type*)0)->*member))

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_PUBLIC
    #define DLL_LOCAL
  #endif
#endif

template<class T>
inline void Swap(T &start, T &end);

template<class T>
inline void Swap(T *start, T *end);

// ~ Swap

template<class T>
void Swap(T &start, T &end)
{
    if(start != end)
    {
        T tmp = end;
        end = start;
        start = tmp;
    }
}

template<class T>
void Swap(T *start, T* end)
{
    if(*start != *end)
    {
        T tmp = *end;
        *end = *start;
        *start = tmp;
    }
}



#endif
