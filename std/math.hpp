#ifndef __MATHEMATICAL_FUNCTIONS__
#define __MATHEMATICAL_FUNCTIONS__

#include "data_types.hpp"
#include "helper.hpp"

namespace kernel
{
namespace std DLL_PUBLIC
{

enum NumberBase
{
    bin = 2,
    oct = 8,
    dec = 10,
    hex = 16
};

enum MathUnits
{
    BIT = 0,        b = 0,
    BYTE = 1,       B = 1,
    KILO_BYTE = 2, kB = 2,
    MEGA_BYTE = 3, MB = 3,
    GIGA_BYTE = 4, GB = 4,
    TERA_BYTE = 5, TB = 5
};

}
}

#endif
