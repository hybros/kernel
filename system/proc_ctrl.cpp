#include "proc_ctrl.hpp"
#include "system.hpp"
#include "../processor/ipi.hpp"
#include "../std/data_convert.hpp"
#include "../std/bits.hpp"
#include "../std/helper.hpp"
using namespace kernel;
using namespace kernel::processor;
using namespace kernel::video;

extern "C" void *usable_space;

ProcessorController::ProcessorController() : system(System::GetInstance()), pc_info{"Processor Controller -> "}
{

}

ProcessorController::~ProcessorController()
{

}

bool ProcessorController::InitProcessorController(MPFloatPointStruct *mp_fps)
{
    if(mp_fps == nullptr)
        return false;

    if(mp_fps->feature_bytes[0] == 0)
    {
        MPConfigTab *mp_ct = reinterpret_cast<MPConfigTab*>(mp_fps->mp_config_table);
        if(system.IsStructureValid(reinterpret_cast<uchar*>(mp_ct), "PCMP", mp_ct->base_table_length) == true)          // Calculation is much simpler with 'base_table_length' than with other tests
        {
            system << info << pc_info << "MultiProcessor Configuration Table address: " << static_cast<void*>(mp_ct) << endl;
            return ProcessMPConfigTable(mp_ct);
        }
    }
    else if(mp_fps->feature_bytes[0] == 1)
        system << info << pc_info << "Running on dual core system (1)" << endl;
    else if(mp_fps->feature_bytes[0] == 2)
        system << info << pc_info << "Running on dual core system (2)" << endl;
    else if(mp_fps->feature_bytes[0] == 3)
        system << info << pc_info << "Running on dual core system (3)" << endl;
    else if(mp_fps->feature_bytes[0] == 4)
        system << info << pc_info << "Running on dual core system (4)" << endl;
    else if(mp_fps->feature_bytes[0] == 5)
        system << info << pc_info << "Running on dual core system (5)" << endl;
    else if(mp_fps->feature_bytes[0] == 6)
        system << info << pc_info << "Running on dual core system (6)" << endl;
    else if(mp_fps->feature_bytes[0] == 7)
        system << info << pc_info << "Running on dual core system (7)" << endl;
    return 10;
}

MPFloatPointStruct *ProcessorController::GetFloatingPointerStructure(uint address_to_start, uint length)
{
    for(uchar *address = reinterpret_cast<uchar*>(address_to_start); address < reinterpret_cast<uchar*>(address_to_start + length); address += 16)
    {
        if(system.IsStructureValid(address, "_MP_", 16) == true)
            return reinterpret_cast<MPFloatPointStruct*>(address);
    }
    return nullptr;
}

bool ProcessorController::BootProcessor(uint local_apic_id)
{
    LAPICIntCmdReg int_cmd_reg = pc_local_apics.GetFirstElement().ReadRegister<LAPICIntCmdReg, &LAPICRegs::interrupt_command_register_s>();
    int_cmd_reg.vector                  = 0x20;
    int_cmd_reg.delivery_mode           = LAPICIntCmdReg::STARTUP;
    int_cmd_reg.delivery_status         = LAPICIntCmdReg::IDLE;
    int_cmd_reg.destination_mode        = LAPICIntCmdReg::PHYSICAL;
    int_cmd_reg.destination_shorthand   = LAPICIntCmdReg::NO_SHORTHAND;
    int_cmd_reg.level                   = LAPICIntCmdReg::DE_ASSERT;
    int_cmd_reg.trigger_mode            = LAPICIntCmdReg::EDGE;
    processor::IPI ipi(pc_local_apics.GetFirstElement(), local_apic_id, int_cmd_reg);
}

bool ProcessorController::ProcessMPConfigTable(MPConfigTab *mp_ct)
{
    uchar *entry_type = reinterpret_cast<uchar*>(mp_ct);
    entry_type += sizeof(MPConfigTab);
//    system << info << pc_info << "Configuration table: " << entry_type << endl;
    for(int i = 0; i < mp_ct->entry_count; i++)
    {
//        system << info << "Multi processor setup -> Entry found!" << endl;
        if(*entry_type == MP_PROCESSOR)
        {
            MPEntry *mp_proc_entry = reinterpret_cast<MPEntry*>(entry_type);
//            system << " Type: Processor" << endl;
//                 << " Local APIC id: " << mp_proc_entry->local_apic_id << endl
//                 << " Local APIC version: " << mp_proc_entry->local_apic_version << endl
//                 << " CPU flags: " << std::bin << mp_proc_entry->cpu_flags << endl
//                 << " Feature flags: " << mp_proc_entry->feature_flags << std::dec << endl;
            if(std::IsBitSet(mp_proc_entry->cpu_flags, 0) == true)                      // Processor is usable
            {
                if(std::IsBitSet(mp_proc_entry->cpu_flags, 1) == true)                  // Our currently running boot processor
                {
                    system << info << pc_info << "Boot processor detected:" << endl;

                    pc_local_apics.PushFirstElement(LocalAPIC(mp_ct->local_apic_address));
                    if(pc_local_apics.GetFirstElement().IsEnabled() == true)
                        system << "    " << success << "APIC enabled." << endl;
                }
                else
                {
                    system << info << pc_info << "Application processor detected:" << endl;

                    if(BootProcessor(mp_proc_entry->local_apic_id) == true)
                        system << "    " << success << "Processor should be booted." << endl;

                    pc_local_apics.PushLastElement(LocalAPIC(mp_ct->local_apic_address));
                    if(pc_local_apics.GetLastElement().IsEnabled() == true)
                        system << "    " << success << "APIC enabled." << endl;
                }
            }

            entry_type += sizeof(MPEntry);
        }
        else if(*entry_type == MP_BUS)
        {
            MPBusEntry *mp_bus_entry = reinterpret_cast<MPBusEntry*>(entry_type);
//            system << " Type: Bus" << endl;
            entry_type += sizeof(MPBusEntry);
        }
        else if(*entry_type == MP_IO_APIC)
        {
            MPIOAPICEntry *mp_io_apic_entry = reinterpret_cast<MPIOAPICEntry*>(entry_type);
//            system << " Type: I/O APIC" << endl;
            entry_type += sizeof(MPIOAPICEntry);
        }
        else if(*entry_type == MP_IO_INTERRUPT_ASSIGN)
        {
            MPIOIntAssignEntry *mp_io_int_entry = reinterpret_cast<MPIOIntAssignEntry*>(entry_type);
//            system << " Type: I/O Interrupt Assignment" << endl;
            entry_type += sizeof(MPIOIntAssignEntry);
        }
        else if(*entry_type == MP_LOCAL_INTERRUPT_ASSIGN)
        {
            MPLocalIntAssignEntry *mp_local_int_entry = reinterpret_cast<MPLocalIntAssignEntry*>(entry_type);
//            system << " Type: Local Interrupt Assignment" << endl;
            entry_type += sizeof(MPLocalIntAssignEntry);
        }
        else
        {
//            system << warning << pc_info << "Type: Unkown" << endl;
        }
    }
    return 0;
}
