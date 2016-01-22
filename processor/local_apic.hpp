#ifndef __LOCAL_APIC__
#define __LOCAL_APIC__

#include "../std/data_types.hpp"
#include "../std/data_extract.hpp"

namespace kernel
{

class System;

namespace processor
{


struct LocalAPICInterruptCommandRegister
{
    ulong vector : 8;
    enum : ulong
    {
        FIXED           = 0,
        LOWEST_PRIORITY = 1,
        SMI             = 2,
        NMI             = 4,
        INIT            = 5,
        STARTUP         = 6
    } delivery_mode : 3;
    enum : ulong
    {
        PHYSICAL        = 0,
        LOGICAL         = 1
    } destination_mode : 1;
    enum : ulong
    {
        IDLE            = 0,
        SEND_PENDIG     = 1
    } delivery_status : 1;
    ulong reserved : 1;
    enum : ulong
    {
        DE_ASSERT       = 0,
        ASSERT          = 1
    } level : 1;
    enum : ulong
    {
        EDGE            = 0,
        LEVEL           = 1
    } trigger_mode : 1;
    ulong reserved2 : 2;
    enum : ulong
    {
        NO_SHORTHAND    = 0,
        SELF            = 1,
        ALL_INCLUD_SELF = 2,
        ALL_EXCLUD_SELF = 3
    } destination_shorthand : 2;
    ulong reserved3 : 35;
    ulong destination_field : 8;
};
typedef struct LocalAPICInterruptCommandRegister LAPICIntCmdReg;

struct LocalAPICRegisters
{
    uchar reserved[20];
    uint local_apic_id;
    uint local_apic_version;
    uint task_priority_register;
    uint arbitration_priority_register;
    uint processor_priority_register;
    uint end_of_interrupt_register;
    uint logical_destination_register;
    uint destination_format_register;
    uint spurious_interrput_vector_register;
    uchar in_service_register[256];
    uchar trigger_mode_register[256];
    uchar interrupt_request_register[256];
    uint error_status_register;
    union
    {
        ulong interrupt_command_register;
        LAPICIntCmdReg interrupt_command_register_s;
    };
    uint lvt_timer_register;
    uint lvt_thermal_sensor_register;
    uint lvt_perform_mon_count_register;
    uint lvt_lint0_register;
    uint lvt_lint1_register;
    uint lvt_error_register;
    uint initial_count_register;
    uint current_count_register;
    uint divide_config_register;
};
typedef LocalAPICRegisters LAPICRegs;

//enum LocalAPICRegisterType
//{
//    LAPIC_ID,
//    LAPIC_VERSION,
//    TPR,                        // Task Priority Register
//    APR,                        // Arbitration Priority Register
//    PPR,                        // Processor Priority Register
//    EOI,                        // End of Interrupt Register
//    LDR,                        // Logical Destination Register
//    DFR,                        // Destination Format Register
//    SIVR,                       // Spurious Interrupt Vector Register
//    ISR,                        // In-Service Register
//    TMR,                        // Trigger Mode Register
//    IRR,                        // Interrupt Request Register
//    ESR,                        // Error Status Register
//    ICR,                        // Interrupt Command Register
//    LVT_TR,                     // LVT Timer Register
//    LVT_TSR,                    // LVT Thermal Sensor Register
//    LVT_PMCR,                   // LVT Performance Monitoring Counters Register
//    LVT_LI0R,                   // LVT LINT0 Register
//    LVT_LI1R,                   // LVT LINT1 Register
//    LVT_ER,                     // LVT Error Register
//    IICR,                       // Initial Count Register
//    CCR,                        // Current Count Register
//    DCR                         // Divide Configuration Register
//};

class LocalAPIC
{
public:
    LocalAPIC();
    LocalAPIC(uint base);
    ~LocalAPIC();

    inline bool IsEnabled();

    uint GetBase();
    void SetBase(uint apic_base);

    template<typename T, T LocalAPICRegisters::* P> inline T ReadRegister();
    template<typename T, T LocalAPICRegisters::* P> inline void WriteRegister(T data);

protected:
    bool InitLocalAPIC();
    bool InitLocalAPIC(uint base);
    void DisableLocalAPIC();

    bool HasLocalAPIC();

private:
    System &system;
    bool has_apic, apic_enabled;
    LocalAPICRegisters *lapic_registers;

    //template<typename T> T &GetRegister(const LocalAPICRegisterType type);
};

// ~ LocalAPIC

bool LocalAPIC::IsEnabled()
{
    return apic_enabled;
}

template<typename T, T LocalAPICRegisters::* P>
T LocalAPIC::ReadRegister()
{
    return lapic_registers->*P;
}

template<typename T, T LocalAPICRegisters::* P>
void LocalAPIC::WriteRegister(T data)
{
    lapic_registers->*P = data;
}

}
}
#endif
