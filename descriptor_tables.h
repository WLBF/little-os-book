#ifndef INCLUDE_DESCRIPTOR_TABLES_H
#define INCLUDE_DESCRIPTOR_TABLES_H

#include "common.h"

/**
 * struct gdt_entry - Contains the value of one GDT entry.
 * @limit_low:      lower 16 bits of the limit.
 * @base_low:       lower 16 bits of the base.
 * @base_middle:    next 8 bits of the base.
 * @access:         access flags, determine what ring this segment can be used in.
 * @granularity:    aranularity flag, determines the scaling of the segment limit field.
 * @base_high:      last 8 bits of the base.
 */
struct gdt_entry
{
   uint16_t limit_low;
   uint16_t base_low;
   uint8_t  base_middle;
   uint8_t  access;
   uint8_t  granularity;
   uint8_t  base_high;
} __attribute__((packed));

/**
 * struct gdt_ptr - Contains the value of the GDTR.
 * @limit:     16 bits table limit for the GDT.
 * @base:      base address of the gdt_entry array.
 */
struct gdt_ptr
{
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));


/**
 * struct idt_entry - Contains the value of one IDT entry.
 * @base_lo:    lower 16 bits of the address to jump to when this interrupt fires
 * @sel:        kernel segment selector.
 * @always0:    always be zero.
 * @flags:      more flags. See documentation.
 * @base_hi:    upper 16 bits of the address to jump to.
 */
struct idt_entry
{
   uint16_t base_lo;
   uint16_t sel;
   uint8_t  always0;
   uint8_t  flags;
   uint16_t base_hi;
} __attribute__((packed));

/**
 * struct idt_ptr - Contains the value of the IDTR.
 * @limit:     16 bits table limit for the iDT.
 * @base:      base address of the idt_entry array.
 */
struct idt_ptr
{
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));


void init_descriptor_tables();

extern void interrupt_handler_0();
extern void interrupt_handler_1();
extern void interrupt_handler_2();
extern void interrupt_handler_3();
extern void interrupt_handler_4();
extern void interrupt_handler_5();
extern void interrupt_handler_6();
extern void interrupt_handler_7();
extern void interrupt_handler_8();
extern void interrupt_handler_9();
extern void interrupt_handler_10();
extern void interrupt_handler_11();
extern void interrupt_handler_12();
extern void interrupt_handler_13();
extern void interrupt_handler_14();
extern void interrupt_handler_15();
extern void interrupt_handler_16();
extern void interrupt_handler_17();
extern void interrupt_handler_18();
extern void interrupt_handler_19();
extern void interrupt_handler_20();
extern void interrupt_handler_21();
extern void interrupt_handler_22();
extern void interrupt_handler_23();
extern void interrupt_handler_24();
extern void interrupt_handler_25();
extern void interrupt_handler_26();
extern void interrupt_handler_27();
extern void interrupt_handler_28();
extern void interrupt_handler_29();
extern void interrupt_handler_30();
extern void interrupt_handler_31();

extern void interrupt_request_handler_0();
extern void interrupt_request_handler_1();
extern void interrupt_request_handler_2();
extern void interrupt_request_handler_3();
extern void interrupt_request_handler_4();
extern void interrupt_request_handler_5();
extern void interrupt_request_handler_6();
extern void interrupt_request_handler_7();
extern void interrupt_request_handler_8();
extern void interrupt_request_handler_9();
extern void interrupt_request_handler_10();
extern void interrupt_request_handler_11();
extern void interrupt_request_handler_12();
extern void interrupt_request_handler_13();
extern void interrupt_request_handler_14();
extern void interrupt_request_handler_15();

#endif /* INCLUDE_DESCRIPTOR_TABLES_H */
