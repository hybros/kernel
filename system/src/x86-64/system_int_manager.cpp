#include "../../include/x86-64/system_int_manager.hpp"

#include "../../include/system_isr.hpp"
#include "../../include/system_asm.hpp"

#include <HInterruptDescriptorTable>
#include <System>

namespace Hybros
{

char *exception_info[35] = {
    "Divide-by-zero Error\0",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved ",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Security Exception",
    "Reserved",
    "Local APIC timer tick",
    "Local APIC error"
}

System::InterruptManager::InterruptManager() :
    idt(256)//	exception_info(new HString[31])
{    
    idt.owerwriteRoutine(0, isr0);
    idt.owerwriteRoutine(1, isr1);
    idt.owerwriteRoutine(2, isr2);
    idt.owerwriteRoutine(3, isr3);
    idt.owerwriteRoutine(4, isr4);
    idt.owerwriteRoutine(5, isr5);
    idt.owerwriteRoutine(6, isr6);
    idt.owerwriteRoutine(7, isr7);
    idt.owerwriteRoutine(8, isr8);
    idt.owerwriteRoutine(9, isr9);
    idt.owerwriteRoutine(10, isr10);
    idt.owerwriteRoutine(11, isr11);
    idt.owerwriteRoutine(12, isr12);
    idt.owerwriteRoutine(13, isr13);
    idt.owerwriteRoutine(14, isr14);
    idt.owerwriteRoutine(15, isr15);
    idt.owerwriteRoutine(16, isr16);
    idt.owerwriteRoutine(17, isr17);
    idt.owerwriteRoutine(18, isr18);
    idt.owerwriteRoutine(19, isr19);
    idt.owerwriteRoutine(20, isr20);
    idt.owerwriteRoutine(21, isr21);
    idt.owerwriteRoutine(22, isr22);
    idt.owerwriteRoutine(23, isr23);
    idt.owerwriteRoutine(24, isr24);
    idt.owerwriteRoutine(25, isr25);
    idt.owerwriteRoutine(26, isr26);
    idt.owerwriteRoutine(27, isr27);
    idt.owerwriteRoutine(28, isr28);
    idt.owerwriteRoutine(29, isr29);
    idt.owerwriteRoutine(30, isr30);
    idt.owerwriteRoutine(31, isr31);

    idt.owerwriteRoutine(32, isr32);
    idt.owerwriteRoutine(33, isr33);
    idt.owerwriteRoutine(34, isr34);
    idt.owerwriteRoutine(35, isr35);
    idt.owerwriteRoutine(36, isr36); 
    idt.owerwriteRoutine(37, isr37);
    idt.owerwriteRoutine(38, isr38);
    idt.owerwriteRoutine(39, isr39);
    idt.owerwriteRoutine(40, isr40);
    idt.owerwriteRoutine(41, isr41);
    idt.owerwriteRoutine(42, isr42);
    idt.owerwriteRoutine(43, isr43);
    idt.owerwriteRoutine(44, isr44);
    idt.owerwriteRoutine(45, isr45);
    idt.owerwriteRoutine(46, isr46);
    idt.owerwriteRoutine(47, isr47);
    idt.owerwriteRoutine(48, isr48);
    
    idt.owerwriteRoutine(100, isr100);

    idt.loadTable();

    remapPIC();

    writePort<uchar>(0xA1, 0xFF);
    writePort<uchar>(0x21, 0xFF);

    SYSTEM << "    " << INFO << "The PIC should be now disabled." << endl;

    enableInterrupts();
}

auto System::InterruptManager::getFirstInterruptNumber() const -> uint
{
    return 0;
}

auto System::InterruptManager::getLastInterruptNumber() const -> uint
{
    return 31;
}

auto System::InterruptManager::getLastException() const -> HException
{
    return HException();
}

void System::InterruptManager::handleInterrupt(Registers *exception_regs)
{
//	HException new_exception(0, exception_regs.interrupt_number, exception_info[exception_regs.interrupt_number], exception_regs);
    if(exception_regs->interrupt_number < 32)
    {
        System::getInstance() << WARN << "Interrupt raised! Number: " << exception_regs->interrupt_number << " - Info: " << exception_info[exception_regs->interrupt_number] << endl
            << "    " << INFO << "rax: " << hex << exception_regs->rax << half << "rbx: " << exception_regs->rbx << endl
            << "    " << INFO << "rcx: " << exception_regs->rcx << half << "rdx: " << exception_regs->rdx << endl
            << "    " << INFO << "rdi: " << exception_regs->rdi << half << "rbp: " << exception_regs->rbp << endl
            << "    " << INFO << "rsp: " <<  exception_regs->userrsp << half << "rip: " << exception_regs->rip << endl << endl
            << "    " << INFO << "error code:" << exception_regs->error_code << half << "rflags: " << exception_regs->rflags << dec << endl;

//		for(uint i = 0; i < int_handlers.GetNumberOfElements(); i++)
//		{
//			HInterruptHandler *handler = int_handlers.GetElement(i);
//			if(handler->GetId() == new_exception.GetCode())
//				handler->Handle(new_exception);
//		}
//		new_exception.Handled(true);
    }
    else if(exception_regs->interrupt_number >= 32 && exception_regs->interrupt_number < 40)
    {
        System::getInstance() << INFO << "Interrupt " << exception_regs->interrupt_number << " raised! " 
               << exception_info[exception_regs->interrupt_number] << endl;
    }
    else
    {
    	System::getInstance() << WARN << "IRQ raised! Number: " << exception_regs->interrupt_number << endl;
    	if(exception_regs->interrupt_number >= 40)
    		writePort<uchar>(0xA0, 0x20);
    
        writePort<uchar>(0x20, 0x20);
	    while(true) 
            __asm__ __volatile__("nop");
    }
}

auto System::InterruptManager::addInterruptHandler(HInterruptHandler &new_handler) -> uint
{
    int_handlers.AddElement(&new_handler);
    return int_handlers.GetNumberOfElements();
}

auto System::InterruptManager::removeInterruptHandler(uint interrupt_handler_id) -> bool
{
    return false;
}

void System::InterruptManager::enableInterrupts() const
{
    __asm__ __volatile__("sti");
}

void System::InterruptManager::disableInterrupts() const
{
    __asm__ __volatile__("cli");
}

void System::InterruptManager::remapPIC()
{
    // Set ICW1
    writePort<uchar>(0x20, 0x11);
    writePort<uchar>(0xA0, 0x11);
        
    // Set ICW2
    writePort<uchar>(0x21, 0xe0);
    writePort<uchar>(0xA1, 0xe8);
        
    // Set ICW3
    writePort<uchar>(0x21, 0x04);
    writePort<uchar>(0xA1, 0x02);
        
    // Set ICW4
    writePort<uchar>(0x21, 0x01);
    writePort<uchar>(0xA1, 0x01);
        
    // Set OCW1
    writePort<uchar>(0x21, 0xff);
    writePort<uchar>(0xA1, 0xff);
}

}

