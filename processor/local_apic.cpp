#include "local_apic.hpp"
#include "../system/system.hpp"
#include "../system/system_asm.hpp"
#include "../std/bits.hpp"
using namespace kernel::processor;
using namespace kernel::std;

LocalAPIC::LocalAPIC() : apic_enabled(false), system(System::GetInstance()) {}

LocalAPIC::LocalAPIC(uint base) : apic_enabled(false), has_apic(HasLocalAPIC()), system(System::GetInstance())
{
    InitLocalAPIC(base);
}

LocalAPIC::~LocalAPIC()
{
    DisableLocalAPIC();
}

bool LocalAPIC::InitLocalAPIC()
{
    if(lapic_registers == nullptr)
        lapic_registers = reinterpret_cast<LocalAPICRegisters*>(0xFEE00000);

    if(has_apic == true)
    {
        uint current_reg = ReadRegister<uint, &LocalAPICRegisters::spurious_interrput_vector_register>();
        WriteRegister<uint, &LocalAPICRegisters::spurious_interrput_vector_register>(current_reg | 0x100);
        apic_enabled = true;
    }
}

bool LocalAPIC::InitLocalAPIC(uint base)
{
    if(lapic_registers == nullptr)
        lapic_registers = reinterpret_cast<LocalAPICRegisters*>(base);

    if(has_apic == true)
    {
        uint current_reg = ReadRegister<uint, &LocalAPICRegisters::spurious_interrput_vector_register>();
        WriteRegister<uint, &LocalAPICRegisters::spurious_interrput_vector_register>(current_reg | 0x100);
        apic_enabled = true;
    }
}

void LocalAPIC::DisableLocalAPIC()
{
    if(lapic_registers == nullptr)
        return;

   uint current_reg = ReadRegister<uint, &LocalAPICRegisters::spurious_interrput_vector_register>();
   WriteRegister<uint, &LocalAPICRegisters::spurious_interrput_vector_register>(current_reg & 0xFFFFFEFF);
}

bool LocalAPIC::HasLocalAPIC()
{
    uint eax = 0, edx = 0;
    cpuid(1, &eax, &edx);
    return IsBitSet(edx, 9);
}

void LocalAPIC::SetBase(uint apic_base)
{
    //uint edx = 0, eax =
}

