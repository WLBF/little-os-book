#ifndef INCLUDE_DESCRIPTOR_TABLES_H
#define INCLUDE_DESCRIPTOR_TABLES_H

#include "common.h"

/**
 * struct gdt_entry - Contains the value of one GDT entry.
 * @limit_low:      lower 16 bits of the limit.
 * @base_low:       lower 16 bits of the base.
 * @base_middle:    next 8 bits of the base.
 * @access:         access flags, determine what ring this segment can be used in.
 * @granularity:    aranularity flag, determines the scaling of the segment limit field
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
 * @base:      base address of the GDT
 */
struct gdt_ptr
{
   uint16_t limit;
   uint32_t base;
} __attribute__((packed));

void init_descriptor_tables();

#endif /* INCLUDE_DESCRIPTOR_TABLES_H */
