#include "multiboot.hpp"
#include "multiboot2.hpp"
#include "system.hpp"
#include "pci.hpp"
#include "../std/data_types.hpp"
#include "../std/tuple.hpp"
using namespace kernel;
using namespace kernel::video;
using namespace kernel::std;

extern "C" void kmain()                                //Multiboot Magic, Multiboot Info
{
    System &system = System::InitSystem();
    system << info << "General -> Starting initialisation.. Oh yeah!" << endl << endl;

    uint boot_magic = system.GetMultibootMagic();
    if(boot_magic == multiboot::MULTIBOOT_BOOTLOADER_MAGIC)
    {
        system << info << "Multiboot -> Loaded by Multiboot compilant bootloader." << endl;

        system.CheckMultibootInfo();
    }
    else if(boot_magic == multiboot2::MULTIBOOT_BOOTLOADER_MAGIC)
    {
        system << info << "Multiboot -> Loaded by Multiboot2 compilant bootloader." << endl;
    }
    else
        system << warning << "Multiboot -> Not loaded by a Multiboot compilant bootloader!" << endl;
    system << success << "Multiboot -> Informations processed." << endl << endl;

//    if(system.CheckMultiProcessorSupport() == true)
//        system.InitProcessors();

//    system << memset(reinterpret_cast<void*>(0x7000), 0xFF, 0x1000) << endl;

//    ulong test = 0;
//    SetBit(test, 63);
//    system << hex << test << endl;

    Tuple<int, char> test;

    if(system.InitMemoryManagers() == true)
        system << success << "Memory Managers -> Working." << endl << endl;
    else
    {
        system << error << "Memory Managers -> Initialisation failed!!!" << endl << endl;
        return;
    }
//
    system << info << "Memory Managers -> Physical memory test: " << system.AllocateBlock() << endl
           << info << "Memory Managers -> Virtual memory test: " << system.AllocatePage() << endl;
//           << info << "Memory Managers -> Heap memory test: " << system.AllocateMemory(10) << endl;
}
