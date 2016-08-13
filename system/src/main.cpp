#include <Hybros/System>
#include <Hybros/Terminal>
#include <Hybros/SystemHeapMemoryManager>

#include "../include/multiboot.hpp"
#include "../include/multiboot2.hpp"

extern "C" void kmain()                                //Multiboot Magic, Multiboot Info
{
    HSystem &system = HSystem::InitSystem();
    system << INFO << "HYBROS -> Starting initialisation.. Oh yeah!" << endl << endl;

    uint boot_magic = system.GetMultibootMagic();
    if(boot_magic == multiboot::MULTIBOOT_BOOTLOADER_MAGIC)
    {
        system << INFO << "HYBROS -> Loaded by Multiboot compilant bootloader." << endl;
        system.CheckMultibootInfo();
        system << SUCC << "HYBROS -> Multiboot: Informations processed." << endl << endl;
    }
    else if(boot_magic == multiboot2::MULTIBOOT_BOOTLOADER_MAGIC)
    {
        system << INFO << "HYBROS -> Loaded by Multiboot2 compilant bootloader." << endl;
    }
    else
        system << WARN << "HYBROS -> Not loaded by a Multiboot compilant bootloader!" << endl;

    if(system.InitMemoryManagers() == true)
        system << SUCC << "HYBROS -> Memory Managers: Working." << endl << endl;
    else
    {
        system << ERROR << "HYBROS -> Memory managers: Initialisation failed!!!" << endl << endl;
        return;
    }

//    system << INFO << "HYBROS -> Memory managers: Test: " << new ulong << endl;

    if(system.InitInterruptManager() == true)
    {
	system << SUCC << "HYBROS -> Interrupts should be intialized!" << endl
               << "    " << INFO << "Testing interrupts...." << endl;

        __asm__ __volatile__("mov $0xABABABABABABABAB, %rax;"
                             "push %rax;"
                             "int $31;");
    }

    if(system.CheckMultiProcessorSupport() == true)
    {
        if(system.InitProcessors() == true)
            system << SUCC << "HYBROS -> Processors initialized!" << endl << endl;
        else
            system << ERROR << "HYBROS -> Processors initialisation failed!!!" << endl << endl;
            return;
    }
    else
        system << WARN << "HYBROS -> This is not a multiprocessor system.." << endl;
    
    while(true)
        __asm__ __volatile__("nop");
}
