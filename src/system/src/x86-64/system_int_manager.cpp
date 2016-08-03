#include "../../include/x86-64/system_int_manager.hpp"

#include "../../include/system_isr.hpp"
#include "../../include/system_asm.hpp"

#include <HInterruptDescriptorTable>
#include <HSystem>

char *exception_info[35];

HSystem::InterruptManager::InterruptManager() :
    idt(256)//	exception_info(new HString[31])
{
    exception_info[0] = "Divide-by-zero Error\0";
    exception_info[1] = "Debug";
    exception_info[2] = "Non-maskable Interrupt";
    exception_info[3] = "Breakpoint";
    exception_info[4] = "Overflow";
    exception_info[5] = "Bound Range Exceeded";
    exception_info[6] = "Invalid Opcode";
    exception_info[7] = "Device Not Available";
    exception_info[8] = "Double Fault";
    exception_info[9] = "Coprocessor Segment Overrun";
    exception_info[10] = "Invalid TSS";
    exception_info[11] = "Segment Not Present";
    exception_info[12] = "Stack-Segment Fault";
    exception_info[13] = "General Protection Fault";
    exception_info[14] = "Page Fault";
    exception_info[15] = "Reserved ";
    exception_info[16] = "x87 Floating-Point Exception";
    exception_info[17] = "Alignment Check";
    exception_info[18] = "Machine Check";
    exception_info[19] = "SIMD Floating-Point Exception";
    exception_info[20] = "Virtualization Exception";
    exception_info[21] = "Reserved";
    exception_info[22] = "Reserved";
    exception_info[23] = "Reserved";
    exception_info[24] = "Reserved";
    exception_info[25] = "Reserved";
    exception_info[26] = "Reserved";
    exception_info[27] = "Reserved";
    exception_info[28] = "Reserved";
    exception_info[29] = "Reserved";
    exception_info[30] = "Security Exception";
    exception_info[31] = "Reserved";
    exception_info[32] = "Local APIC timer tick";
    exception_info[33] = "Local APIC error";
    
    idt.OverwriteRoutine(0, isr0);
    idt.OverwriteRoutine(1, isr1);
    idt.OverwriteRoutine(2, isr2);
    idt.OverwriteRoutine(3, isr3);
    idt.OverwriteRoutine(4, isr4);
    idt.OverwriteRoutine(5, isr5);
    idt.OverwriteRoutine(6, isr6);
    idt.OverwriteRoutine(7, isr7);
    idt.OverwriteRoutine(8, isr8);
    idt.OverwriteRoutine(9, isr9);
    idt.OverwriteRoutine(10, isr10);
    idt.OverwriteRoutine(11, isr11);
    idt.OverwriteRoutine(12, isr12);
    idt.OverwriteRoutine(13, isr13);
    idt.OverwriteRoutine(14, isr14);
    idt.OverwriteRoutine(15, isr15);
    idt.OverwriteRoutine(16, isr16);
    idt.OverwriteRoutine(17, isr17);
    idt.OverwriteRoutine(18, isr18);
    idt.OverwriteRoutine(19, isr19);
    idt.OverwriteRoutine(20, isr20);
    idt.OverwriteRoutine(21, isr21);
    idt.OverwriteRoutine(22, isr22);
    idt.OverwriteRoutine(23, isr23);
    idt.OverwriteRoutine(24, isr24);
    idt.OverwriteRoutine(25, isr25);
    idt.OverwriteRoutine(26, isr26);
    idt.OverwriteRoutine(27, isr27);
    idt.OverwriteRoutine(28, isr28);
    idt.OverwriteRoutine(29, isr29);
    idt.OverwriteRoutine(30, isr30);
    idt.OverwriteRoutine(31, isr31);

    idt.OverwriteRoutine(32, isr32);
    idt.OverwriteRoutine(33, isr33);
    idt.OverwriteRoutine(34, isr34);
    idt.OverwriteRoutine(35, isr35);
    idt.OverwriteRoutine(36, isr36); 
    idt.OverwriteRoutine(37, isr37);
    idt.OverwriteRoutine(38, isr38);
    idt.OverwriteRoutine(39, isr39);
    idt.OverwriteRoutine(40, isr40);
    idt.OverwriteRoutine(41, isr41);
    idt.OverwriteRoutine(42, isr42);
    idt.OverwriteRoutine(43, isr43);
    idt.OverwriteRoutine(44, isr44);
    idt.OverwriteRoutine(45, isr45);
    idt.OverwriteRoutine(46, isr46);
    idt.OverwriteRoutine(47, isr47);
    idt.OverwriteRoutine(48, isr48);
    
    idt.OverwriteRoutine(100, isr100);

    idt.LoadTable();

    RemapPIC();

    WritePort<uchar>(0xA1, 0xFF);
    WritePort<uchar>(0x21, 0xFF);

    SYSTEM << "    " << INFO << "The PIC should be now disabled." << endl;

    EnableInterrupts();
}

auto HSystem::InterruptManager::GetFirstInterruptNumber() const -> uint
{
    return 0;
}

auto HSystem::InterruptManager::GetLastInterruptNumber() const -> uint
{
    return 31;
}

auto HSystem::InterruptManager::GetLastException() const -> HException
{
    return HException();
}

void HSystem::InterruptManager::HandleInterrupt(Registers *exception_regs)
{
//	HException new_exception(0, exception_regs.interrupt_number, exception_info[exception_regs.interrupt_number], exception_regs);
    if(exception_regs->interrupt_number < 32)
    {
        HSystem::GetInstance() << WARN << "Interrupt raised! Number: " << exception_regs->interrupt_number << " - Info: " << exception_info[exception_regs->interrupt_number] << endl
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
        HSystem::GetInstance() << INFO << "Interrupt " << exception_regs->interrupt_number << " raised! " 
               << exception_info[exception_regs->interrupt_number] << endl;
    }
    else
    {
    	HSystem::GetInstance() << WARN << "IRQ raised! Number: " << exception_regs->interrupt_number << endl;
    	if(exception_regs->interrupt_number >= 40)
    		WritePort<uchar>(0xA0, 0x20);
    
        WritePort<uchar>(0x20, 0x20);
	while(true) __asm__ __volatile__("nop");
    }
}

auto HSystem::InterruptManager::AddInterruptHandler(HInterruptHandler &new_handler) -> uint
{
    int_handlers.AddElement(&new_handler);
    return int_handlers.GetNumberOfElements();
}

auto HSystem::InterruptManager::RemoveInterruptHandler(uint interrupt_handler_id) -> bool
{
    return false;
}

void HSystem::InterruptManager::EnableInterrupts() const
{
    __asm__ __volatile__("sti");
}

void HSystem::InterruptManager::DisableInterrupts() const
{
    __asm__ __volatile__("cli");
}

void HSystem::InterruptManager::RemapPIC()
{
    // Set ICW1
    WritePort<uchar>(0x20, 0x11);
    WritePort<uchar>(0xA0, 0x11);
        
    // Set ICW2
    WritePort<uchar>(0x21, 0xe0);
    WritePort<uchar>(0xA1, 0xe8);
        
    // Set ICW3
    WritePort<uchar>(0x21, 0x04);
    WritePort<uchar>(0xA1, 0x02);
        
    // Set ICW4
    WritePort<uchar>(0x21, 0x01);
    WritePort<uchar>(0xA1, 0x01);
        
    // Set OCW1
    WritePort<uchar>(0x21, 0xff);
    WritePort<uchar>(0xA1, 0xff);
}


