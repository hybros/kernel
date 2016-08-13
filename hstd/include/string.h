#ifndef __C_STRING_OPERATIONS__
#define __C_STRING_OPERATIONS__

#include <HStdTypes>

extern "C"
{

size_t strlen(const char *str);
char *strcpy(char *destination, const char *source);
char *strcpy_s(char *destination, const char *source, size_t length);
char *strcat(char *destination, const char *source);
char *itoa(int number, char *string, int base);

}

#endif
