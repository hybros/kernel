#include "../../std/data_types.hpp"
#include "../../system/system.hpp"
#include "../../system/terminal.hpp"
using namespace kernel;

extern "C" void minit()
{
    System &system = System::GetInstance();
    system << "WHatDaF4cK?!" << video::endl;
}
