#ifndef __VARIANT__
#define __VARIANT__

namespace kernel
{
namespace std
{

class Variant
{
public:
    template<class T> Variant(const T &value);
    ~Variant();

protected:
    typedef unspecified Type;
    Type value;
};

}
}

#endif // __VARIANT__
