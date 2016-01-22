#ifndef __INTERPROCESSOR_INTERRUP__
#define __INTERPROCESSOR_INTERRUP__

#include <HLocalAPIC>

class HInterProcessorInterrupt : public HLocalAPIC
{
public:
    HInterProcessorInterrupt(HLocalAPIC &local_apic);
    HInterProcessorInterrupt(HLocalAPIC &local_apic, uint target, HLocalAPIC::IntCmdReg &int_cmd_reg);
    ~HInterProcessorInterrupt() = default;

    void SendCommand(uint target, HLocalAPIC::IntCmdReg &int_cmd_reg);
};

using IPI = HInterProcessorInterrupt;

#endif //__INTERPROCESSOR_INTERRUP__
