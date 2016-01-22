#ifndef __INTERPROCESSOR_INTERRUP__
#define __INTERPROCESSOR_INTERRUP__

#include "local_apic.hpp"

namespace kernel
{
namespace processor
{

class InterProcessorInterrupt : public LocalAPIC
{
public:
    InterProcessorInterrupt(LocalAPIC &local_apic);
    InterProcessorInterrupt(LocalAPIC &local_apic, uint target, LAPICIntCmdReg &int_cmd_reg);

    bool SendCommand(uint target, LAPICIntCmdReg &int_cmd_reg);
};
typedef class InterProcessorInterrupt IPI;

}
}

#endif //__INTERPROCESSOR_INTERRUP__
