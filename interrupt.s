%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    cli                                 ; disable interrupts
    push    dword 0                     ; push 0 as error code
    push    dword %1                    ; push the interrupt number
    jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
    cli                                 ; disable interrupts
    push    dword %1                    ; push the interrupt number
    jmp     common_interrupt_handler    ; jump to the common handler
%endmacro

%macro no_error_code_interrupt_request_handler 2
global interrupt_request_handler_%1
interrupt_request_handler_%1:                   ; IRQ number
    cli                                         ; disable interrupts
    push    dword 0                             ; push 0 as error code
    push    dword %2                            ; push the remapped interrupt number
    jmp     common_interrupt_request_handler    ; jump to the common handler
%endmacro

extern interrupt_handler                ; define in interrupt_handler.c
extern interrupt_request_handler        ; define in interrupt_handler.c

common_interrupt_handler:               ; the common parts of the generic interrupt handler
    ; save the registers
    pusha

    mov ax, ds               ; Lower 16-bits of eax = ds.
    push eax                 ; save the data segment descriptor

    mov ax, 0x10  ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; call the C function
    call interrupt_handler

    pop eax        ; reload the original data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; restore the registers
    popa

    ; restore the esp
    add     esp, 8
    ; set interrupt enable bit
    sti
    ; return to the code that got interrupted
    iret

common_interrupt_request_handler:
    pusha                    ; Pushes edi,esi,ebp,esp,ebx,edx,ecx,eax

    mov ax, ds               ; Lower 16-bits of eax = ds.
    push eax                 ; save the data segment descriptor

    mov ax, 0x10  ; load the kernel data segment descriptor
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call interrupt_request_handler

    pop ebx        ; reload the original data segment descriptor
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa                     ; Pops edi,esi,ebp...
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    sti
    iret           ; pops 5 things at once: cs, eip, eflags, ss, and esp

no_error_code_interrupt_handler 0       ; create handler for interrupt 0
no_error_code_interrupt_handler 1
no_error_code_interrupt_handler 2
no_error_code_interrupt_handler 3
no_error_code_interrupt_handler 4
no_error_code_interrupt_handler 5
no_error_code_interrupt_handler 6
no_error_code_interrupt_handler 7
error_code_interrupt_handler    8
no_error_code_interrupt_handler 9
error_code_interrupt_handler    10
error_code_interrupt_handler    11
error_code_interrupt_handler    12
error_code_interrupt_handler    13
error_code_interrupt_handler    14
no_error_code_interrupt_handler 15
no_error_code_interrupt_handler 16
error_code_interrupt_handler    17
no_error_code_interrupt_handler 18
no_error_code_interrupt_handler 19
no_error_code_interrupt_handler 20
no_error_code_interrupt_handler 21
no_error_code_interrupt_handler 22
no_error_code_interrupt_handler 23
no_error_code_interrupt_handler 24
no_error_code_interrupt_handler 25
no_error_code_interrupt_handler 26
no_error_code_interrupt_handler 27
no_error_code_interrupt_handler 28
no_error_code_interrupt_handler 29
no_error_code_interrupt_handler 30
no_error_code_interrupt_handler 31

no_error_code_interrupt_request_handler 0, 32
no_error_code_interrupt_request_handler 1, 33
no_error_code_interrupt_request_handler 2, 34
no_error_code_interrupt_request_handler 3, 35
no_error_code_interrupt_request_handler 4, 36
no_error_code_interrupt_request_handler 5, 37
no_error_code_interrupt_request_handler 6, 38
no_error_code_interrupt_request_handler 7, 39
no_error_code_interrupt_request_handler 8, 40
no_error_code_interrupt_request_handler 9, 41
no_error_code_interrupt_request_handler 10, 42
no_error_code_interrupt_request_handler 11, 43
no_error_code_interrupt_request_handler 12, 44
no_error_code_interrupt_request_handler 13, 45
no_error_code_interrupt_request_handler 14, 46
no_error_code_interrupt_request_handler 15, 47
