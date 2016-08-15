#ifndef __MEMORY_OPERATIONS__
#define __MEMORY_OPERATIONS__

#include <Hybros/StdHelper>
#include <Hybros/StdTypes>

void *operator new (size_t size);

void *operator new[] (size_t size);

void operator delete (void *address);

void operator delete[] (void *address);

//namespace kernel
//{

//template<typename T>
//class HMemory
//{
//public:
//    HMemory();
//    HMemory(T &data);
//    HMemory(HMemory<T> &other_memory);
//    ~HMemory();

//    template<typename R> inline R GetMember(uint position);
//    inline T GetData();
//    inline void SetData(uchar value);
//    inline void ZeroData();

//    template<typename R> static inline R Get(T &data, uint position);
//    static inline void Set(T &data, uchar value);
//    static void Set(T &data, uchar value, size_t size);
//    static inline void Zero(T &data);
//    static void Zero(T &data, size_t size);

//private:
//    T memory_data;
//};

//}

#endif
