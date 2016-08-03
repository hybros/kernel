#include "../include/ipi.hpp"

#include <HLocalAPIC>
#include <HSystem>

HInterProcessorInterrupt::HInterProcessorInterrupt(HLocalAPIC &local_apic) : HLocalAPIC(local_apic) {}

HInterProcessorInterrupt::HInterProcessorInterrupt(HLocalAPIC &local_apic, uint target, HLocalAPIC::IntCmdReg &int_cmd_reg) : HLocalAPIC(local_apic)
{
    SendCommand(target, int_cmd_reg);
}
