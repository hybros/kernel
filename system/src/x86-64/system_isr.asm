bits 64

section .text

extern _ZN7HSystem16InterruptManager15HandleInterruptEP9Registers

%macro ISR_NOERRCODE 1  ; define a macro, taking one parameter
  global isr%1        ; %1 accesses the first parameter.
  isr%1:
    cli
    push qword 0
    push qword %1
    jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
  global isr%1
  isr%1:
    cli
    push qword %1
    jmp isr_common_stub
%endmacro

%macro push_all 0
    push qword rax      ;save current rax
    push qword rbx      ;save current rbx
    push qword rcx      ;save current rcx
    push qword rdx      ;save current rdx
    push qword rbp      ;save current rbp
    push qword rdi       ;save current rdi
    push qword rsi       ;save current rsi
    push qword r8        ;save current r8
    push qword r9        ;save current r9
    push qword r10      ;save current r10
    push qword r11      ;save current r11
    push qword r12      ;save current r12
    push qword r13      ;save current r13
    push qword r14      ;save current r14
    push qword r15      ;save current r15
%endmacro

%macro pop_all 0
    pop qword r15
    pop qword r14
    pop qword r13
    pop qword r12
    pop qword r11
    pop qword r10
    pop qword r9
    pop qword r8
    pop qword rsi
    pop qword rdi
    pop qword rbp
    pop qword rdx
    pop qword rcx
    pop qword rbx
    pop qword rax
%endmacro

isr_common_stub:
    push_all

;    mov ax, 0x10
;    mov ds, ax
;    mov es, ax
;    mov fs, ax
;    mov gs, ax

    mov rdi, rsp
    call _ZN7HSystem16InterruptManager15HandleInterruptEP9Registers

    pop_all
    add rsp, 16

    xor eax, eax
.wait:
    inc eax
    cmp eax, 0xFFFFFFFF
    jb .wait
    

    iretq

; ISR defintions

ISR_NOERRCODE 0
ISR_NOERRCODE 1
ISR_NOERRCODE 2
ISR_NOERRCODE 3
ISR_NOERRCODE 4
ISR_NOERRCODE 5
ISR_NOERRCODE 6
ISR_NOERRCODE 7
ISR_ERRCODE 8
ISR_NOERRCODE 9
ISR_ERRCODE 10
ISR_ERRCODE 11
ISR_ERRCODE 12
ISR_ERRCODE 13
ISR_ERRCODE 14
ISR_NOERRCODE 15
ISR_NOERRCODE 16
ISR_NOERRCODE 17
ISR_NOERRCODE 18
ISR_NOERRCODE 19
ISR_NOERRCODE 20
ISR_NOERRCODE 21
ISR_NOERRCODE 22
ISR_NOERRCODE 23
ISR_NOERRCODE 24
ISR_NOERRCODE 25
ISR_NOERRCODE 26
ISR_NOERRCODE 27
ISR_NOERRCODE 28
ISR_NOERRCODE 29
ISR_NOERRCODE 30
ISR_NOERRCODE 31

; IRQ definitions

ISR_NOERRCODE 32
ISR_NOERRCODE 33
ISR_NOERRCODE 34
ISR_NOERRCODE 35
ISR_NOERRCODE 36
ISR_NOERRCODE 37
ISR_NOERRCODE 38
ISR_NOERRCODE 39
ISR_NOERRCODE 40
ISR_NOERRCODE 41
ISR_NOERRCODE 42
ISR_NOERRCODE 43
ISR_NOERRCODE 44
ISR_NOERRCODE 45
ISR_NOERRCODE 46
ISR_NOERRCODE 47

ISR_NOERRCODE 48

ISR_ERRCODE 100
