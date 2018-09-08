global gdt_flush

gdt_flush:
   mov eax, [esp+4]      ; Get the pointer to the GDT, passed as a parameter.
   lgdt [eax]            ; Load the new GDT pointer
   jmp 0x08:.reload_cs   ; 0x08 is the offset to our code segment: Far jump!

.reload_cs:
    mov ax, 0x10         ; 0x10 points at the new data selector
    mov ds, ax           ; Load all data segment selectors
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    ret
