#ifndef __C_MEMORY_OPERATIONS__
#define __C_MEMORY_OPERATIONS__

#include <HStdTypes>

extern "C"
{

void *memzero(void *destination, size_t size);

void *memset(void *destination, char value, size_t size);

void *memcpy(void *destination, const void *source, size_t size);

void *memmove(void *destination, const void *source, size_t size);

void *memchr(void *source, uchar value, size_t size);

int memcmp(const void *first, const void *second, size_t size);

}

#endif
