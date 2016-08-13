#ifndef __EXCEPTIONS__
#define __EXCEPTIONS__

#include <HBaseException>

class HException : public HBaseException
{
public:
    HException();
    ~HException() = default;
};

#endif
