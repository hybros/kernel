#include "ipi.hpp"
#include "local_apic.hpp"
using namespace kernel::processor;

InterProcessorInterrupt::InterProcessorInterrupt(LocalAPIC &local_apic) : LocalAPIC(local_apic) {}

InterProcessorInterrupt::InterProcessorInterrupt(LocalAPIC &local_apic, uint target, LAPICIntCmdReg &int_cmd_reg) : LocalAPIC(local_apic)
{
    SendCommand(target, int_cmd_reg);
}

bool InterProcessorInterrupt::SendCommand(uint target, LAPICIntCmdReg &int_cmd_reg)
{
    WriteRegister<ulong, &LAPICRegs::interrupt_command_register>(target << 24);
    WriteRegister<LAPICIntCmdReg, &LAPICRegs::interrupt_command_register_s>(int_cmd_reg);
}
