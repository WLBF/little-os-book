#ifndef INCLUDE_INTERRUPT_HANDLER_H
#define INCLUDE_INTERRUPT_HANDLER_H

#include "common.h"

struct registers
{
   uint32_t ds;
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
   uint32_t int_no, err_code;
   uint32_t eip, cs, eflags, useresp, ss;
};

#endif /* INCLUDE_INTERRUPT_HANDLER_H */
