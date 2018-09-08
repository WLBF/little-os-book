#ifndef INCLUDE_DESCRIPTOR_TABLES_H
#define INCLUDE_DESCRIPTOR_TABLES_H

// This structure contains the value of one GDT entry.
// We use the attribute 'packed' to tell GCC not to change
// any of the alignment in the structure.
struct gdt_entry_struct
{
   unsigned short limit_low;           // The lower 16 bits of the limit.
   unsigned short base_low;            // The lower 16 bits of the base.
   unsigned char  base_middle;         // The next 8 bits of the base.
   unsigned char  access;              // Access flags, determine what ring this segment can be used in.
   unsigned char  granularity;
   unsigned char  base_high;           // The last 8 bits of the base.
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
   unsigned short limit;               // The upper 16 bits of all selector limits.
   unsigned int base;                // The address of the first gdt_entry_t struct.
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

// Initialisation function is publicly accessible.
void init_descriptor_tables();

#endif /* INCLUDE_DESCRIPTOR_TABLES_H */