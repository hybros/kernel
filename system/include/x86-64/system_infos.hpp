#ifndef __SYSTEM_INFO_AND_GENERAL_STRUCTURES_X86_64__
#define __SYSTEM_INFO_AND_GENERAL_STRUCTURES_X86_64__

#include <HStdTypes>

struct Registers
{
    ulong r15, r14, r13, r12, r11, r10, r9, r8, rsi, rdi, rbp, rdx, rcx, rbx, rax;
    ulong interrupt_number;
    ulong error_code;
    ulong rip, cs, rflags, userrsp, ss;
} __attribute__ ((aligned(16)));

#endif
