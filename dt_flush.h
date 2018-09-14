#ifndef INCLUDE_DT_FLUSH_H
#define INCLUDE_DT_FLUSH_H

#include "common.h"

/** gdt_flush - Load gdt & flush segment registers.
 *
 *  @param gdt_ptr pointer point to gdt
 */
void gdt_flush(uint32_t gdt_ptr);

/** gdt_flush - Loads the interrupt descriptor table (IDT).
 *
 *  @param idt_ptr pointer point to idt
 */
void idt_flush(uint32_t idt_ptr);

#endif /* INCLUDE_DT_FLUSH_H */

