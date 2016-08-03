#ifndef __LOCAL_APIC__
#define __LOCAL_APIC__

#include <HSystemManager>
#include <HBitfield>
#include <HBitOperations>

class HLocalAPIC
{
public:
    struct InterruptCommandRegister : public HBitfield<uint32>
    {
    public:
        enum DeliveryMode
        {
            FIXED = 0,
            LOWEST_PRIORITY = 1,
            SMI = 2,
            NMI = 4,
            INIT = 5,
            STARTUP = 6
        };
        
        enum DestinationMode
        {
            PHYSICAL = 0,
            LOGICAL = 1
        };
        
        enum DeliveryStatus
        {
            IDLE = 0,
            SEND_PENDING = 1
        };
        
        enum AssertLevel
        {
            DE_ASSERT = 0,
            ASSERT = 1
        };
        
        enum TriggerMode
        {
            EDGE = 0,
            LEVEL = 1
        };
        
        enum DestinationShorthand
        {
            NO_SHORTHAND = 0,
            SELF = 1,
            ALL_INCLUD_SELF = 2,
            ALL_EXCLUD_SELF = 3
        };

        BITFIELD_COMMON(InterruptCommandRegister, uint32)

        BITFIELD_MEMBER(uint8, Vector, 0, 7)
        BITFIELD_MEMBER(DeliveryMode, DeliveryMode, 8, 10)
        BITFIELD_MEMBER1(DestinationMode, DestinationMode, 11)
        BITFIELD_MEMBER1(DeliveryStatus, DeliveryStatus, 12)
	//BITFIELD_MEMBER(uint64, reserved, 13, 13)
        BITFIELD_MEMBER1(AssertLevel, AssertLevel, 14)
        BITFIELD_MEMBER1(TriggerMode, TriggerMode, 15)
	//BITFIELD_MEMBER(uint64, reserved2, 16, 16)
        BITFIELD_MEMBER(DestinationShorthand, DestinationShorthand, 18, 19)
	//BITFIELD_MEMBER(uint64, reserved3 35)
	//BITFIELD_MEMBER(uint64, TargetId, 54, 57)
	//BITFIELD_MEMBER(uint64, destination_field  8
    };
    using IntCmdReg = InterruptCommandRegister;
    
    enum Registers
    {
        LOCAL_APIC_ID = 0x20,
        LOCAL_APIC_VERSION = 0x30,
        TASK_PRIORITY_REGISER = 0x80,
        ARBITRATION_PRIORITY_REGISTER = 0x90,
        PROCESSOR_PRIORITY_REGISTER = 0xA0,
        EOI_REGISTER = 0xB0,
        LOGICAL_DESTINATION_REGISTER = 0xD0,
        DESTINATION_FORMAT_REGISTER = 0xE0,
        SPURIOS_INTERRUPT_VECTOR_REGISTER = 0xF0,
        IN_SERVICE_REGISTER = 0x100,
        TRIGGER_MODE_REGISTER = 0x180,
        INTERRUPT_REQUEST_REGISTER = 0x200,
        ERROR_STATUS_REGISTER = 0x280,
        INTERRUPT_COMMAND_REGISTER = 0x300,
        INTERRUPT_COMMAND_REGISTER1 = 0x300,
        INTERRUPT_COMMAND_REGISTER2 = 0x310,
        LVT_TIMER_REGISTER = 0x320,
        LVT_THERMAL_SENSOR_REGISTER = 0x330,
        LVT_PERF_MON_COUNT_REGISTER = 0x340,
        LVT_LINT0_REGISTER = 0x350,
        LVT_LINT1_REGISTER = 0x360,
        LVT_ERROR_REGISTER = 0x370,
        INITIAL_COUNT_REGISTER = 0x380,
        CURRENT_COUNT_REGISTER = 0x390,
        DIVIDE_CONFIG_REGISTER = 0x3E0
    };

    HLocalAPIC();
    HLocalAPIC(uint base);
    ~HLocalAPIC();

    auto IsEnabled() -> bool;
    
    void EnableTimer();

    auto GetBase() -> uint;
    void SetBase(uint apic_base);

    template<typename T> auto ReadRegister(Registers reg) -> T;
    template<typename T> void WriteRegister(Registers reg, T data);

    auto SendIPI(uint apic_target_id, IntCmdReg &reg) -> bool;

protected:
    auto InitLocalAPIC() -> bool;
    auto InitLocalAPIC(uint base) -> bool;
    void DisableLocalAPIC();

    auto HasLocalAPIC() -> bool;

private:
    bool has_apic, apic_enabled;
    void *lapic_registers;

    //template<typename T> T &GetRegister(const LocalAPICRegisterType type);
};

// ~ LocalAPIC

template<typename T>
auto HLocalAPIC::ReadRegister(Registers reg) -> T
{
    void *tmp_address = reinterpret_cast<void*>(reinterpret_cast<uchar*>(lapic_registers) + reg);
    return *(reinterpret_cast<T*>(tmp_address));
}

template<typename T>
void HLocalAPIC::WriteRegister(Registers reg, T data)
{
    void *tmp_address = reinterpret_cast<void*>(reinterpret_cast<uchar*>(lapic_registers) + reg);
    *(reinterpret_cast<T*>(tmp_address)) = data;
}

//template<typename T, T HLocalAPIC::Registers::* P>
//T HLocalAPIC::ReadRegister()
//{
//    return lapic_registers->*P;
//}
//
//template<typename T, T HLocalAPIC::Registers::* P>
//void HLocalAPIC::WriteRegister(T data)
//{
//    lapic_registers->*P = data;
//}

#endif
