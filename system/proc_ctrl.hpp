#ifndef __PROCESSOR_CONTROLLER__
#define __PROCESSOR_CONTROLLER__

#include "system_infos.hpp"
#include "../processor/local_apic.hpp"
#include "../processor/mp_infos.hpp"
#include "../std/vector.hpp"

namespace kernel
{

class System;

class ProcessorController
{
public:
    ProcessorController();
    ~ProcessorController();

    bool InitProcessorController(processor::MPFloatPointStruct *mp_fps);

    bool BootProcessor(uint local_apic_id);

    processor::MPFloatPointStruct *GetFloatingPointerStructure(uint address_to_start, uint length);

protected:
    bool ProcessMPConfigTable(processor::MPConfigTab *mp_ct);

private:
    System &system;
    std::Vector<processor::LocalAPIC> pc_local_apics;
    const char pc_info[25];
};

}

#endif // __PROCESSOR_CONTROLLER__
