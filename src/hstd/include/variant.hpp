#ifndef __VARIANT__
#define __VARIANT__

#include "data_types.hpp"
#include "type_info.hpp"
#include "pointer.hpp"

class HVariant
{
public:
    template<class T> HVariant(const T &value);
    ~HVariant();

protected:
    struct AbstractHelper
    {
        virtual ~AbstractHelper() {}
    };

    template<class T>
    struct HVariantHelper : public AbstractHelper
    {
        T type_data;
        TypeInfo<T> type_info;

        HVariantHelper(const T &data);
    };

    HPointer<AbstractHelper> helper;
};
typedef HVariant HVar;


#endif // __VARIANT__
