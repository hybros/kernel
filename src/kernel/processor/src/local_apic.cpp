#include "../include/local_apic.hpp"

#include <HSystemManager>
#include <HSystem>
#include <HBitOperations>

HLocalAPIC::HLocalAPIC() : apic_enabled(false) {
}

HLocalAPIC::HLocalAPIC(uint base) : apic_enabled(false), has_apic(HasLocalAPIC()) {
    InitLocalAPIC(base);
}

HLocalAPIC::~HLocalAPIC() {
    DisableLocalAPIC();
}

auto HLocalAPIC::IsEnabled() -> bool {
    return apic_enabled;
}

void HLocalAPIC::EnableTimer() {
    // Set DIVIDE_CONFIG_REGISTER to divide by 16 (011)
    WriteRegister<uint>(DIVIDE_CONFIG_REGISTER, 3);

    // Set Initial Count Register to highest possible number
    WriteRegister<uint>(INITIAL_COUNT_REGISTER, 0xFFFFFFFF);
    
    // Disable APIC Timer now
    WriteRegister<uint>(LVT_TIMER_REGISTER, 0x10000);
    
    // Count ticks in 10ms
    uint ticks = 0xFFFFFFFF - ReadRegister<uint>(CURRENT_COUNT_REGISTER);
    HSystem::GetInstance() << "    " << INFO << "Ticks in 10ms: " << hex << ticks << endl;
    
    // Initialize the timer again to periodic mode (bit 17) with vector 32
    WriteRegister<uint>(LVT_TIMER_REGISTER, 0x20000 | 32);
    WriteRegister<uint>(DIVIDE_CONFIG_REGISTER, 3);

    // Set CURRENT_COUNT_REGISTER to ticks
    WriteRegister<uint>(CURRENT_COUNT_REGISTER, ticks);
}

auto HLocalAPIC::HasLocalAPIC() -> bool {
    uint eax = 0, edx = 0;
    cpuid(1, eax, edx);
    return IsBitSet(edx, 9);
}

auto HLocalAPIC::SendIPI(uint apic_target_id, HLocalAPIC::IntCmdReg &int_cmd_reg) -> bool {
    uint32 ipi_target = 0;
    SetBit(ipi_target, 24);
    HSystem::GetInstance() << INFO << "HYBROS -> Multi processor init: Target: " << bin << ipi_target << dec << '\n';
    WriteRegister<uint32>(INTERRUPT_COMMAND_REGISTER2, ipi_target);
    WriteRegister<IntCmdReg>(INTERRUPT_COMMAND_REGISTER1, int_cmd_reg);

    HSystem::GetInstance() << INFO << "HYBROS -> Multi processor init: Waiting for IPI to be received..." << endl;
    IntCmdReg current_reg = ReadRegister<IntCmdReg>(INTERRUPT_COMMAND_REGISTER2);
    while (current_reg.IsDeliveryStatusSet() == true);
    HSystem::GetInstance() << "    " << SUCC << "Received!" << endl;

}

auto HLocalAPIC::InitLocalAPIC() -> bool {
    InitLocalAPIC(0xFEE00000);
}

auto HLocalAPIC::InitLocalAPIC(uint base) -> bool {
    if (lapic_registers == nullptr)
        lapic_registers = reinterpret_cast<Registers*> (base);

    if (has_apic == true) {
        uint current_reg = ReadRegister<uint>(SPURIOS_INTERRUPT_VECTOR_REGISTER);
        WriteRegister(SPURIOS_INTERRUPT_VECTOR_REGISTER, current_reg | 0x100);

        HSystem::GetInstance() << "    " << INFO << "Local APIC version: " << hex << ReadRegister<uint>(LOCAL_APIC_VERSION) << dec << endl;

        current_reg = ReadRegister<uint>(LVT_ERROR_REGISTER);
        current_reg &= 0xFFFFFF00;
        current_reg |= 33;
        WriteRegister(LVT_ERROR_REGISTER, current_reg);

        HSystem::GetInstance() << "    " << INFO << "Local APIC error IRQ enabled!" << endl;

        EnableTimer();
        HSystem::GetInstance() << "    " << INFO << "Local APIC timer enabled!" << endl;

        apic_enabled = true;
    }
}

void HLocalAPIC::DisableLocalAPIC() {
    if (lapic_registers == nullptr)
        return;

    uint current_reg = ReadRegister<uint>(SPURIOS_INTERRUPT_VECTOR_REGISTER);
    WriteRegister<uint>(SPURIOS_INTERRUPT_VECTOR_REGISTER, current_reg & 0xFFFFFEFF);
}

