#ifndef INCLUDE_INTERRUPT_HANDLER_H
#define INCLUDE_INTERRUPT_HANDLER_H

#include "common.h"

struct cpu_state {
    uint32_t ebp;
    uint32_t esp;
    uint32_t edi;
    uint32_t esi;
    uint32_t edx;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t eax;
} __attribute__((packed));

struct stack_state {
    uint32_t error_code;
    uint32_t eip;
    uint32_t cs;
    uint32_t eflags;
} __attribute__((packed));

#endif /* INCLUDE_INTERRUPT_HANDLER_H */
