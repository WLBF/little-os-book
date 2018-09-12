#include "descriptor_tables.h"
#include "gdt_flush.h"

extern void gdt_flush(unsigned int);

static void init_gdt();
static void gdt_set_entry(int, unsigned int, unsigned int, unsigned short, unsigned short);

struct gdt_entry gdt_entries[5];
struct gdt_ptr   gdt_ptr;

void init_descriptor_tables()
{
   init_gdt();
}

/* init_gdt() - Initialise the global descriptor table. */
static void init_gdt()
{
   gdt_ptr.limit = (sizeof(struct gdt_entry) * 3);
   gdt_ptr.base  = (unsigned int)&gdt_entries;

   gdt_set_entry(0, 0, 0, 0, 0);                /* null segment */
   gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); /* code segment */
   gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF); /* data segment */

   gdt_flush((unsigned int)&gdt_ptr);
}

/* gdt_set_entry() - Set the value of one GDT entry. */
static void gdt_set_entry(int num, unsigned int base, unsigned int limit, unsigned short access, unsigned short gran)
{
   gdt_entries[num].base_low    = (base & 0xFFFF);
   gdt_entries[num].base_middle = (base >> 16) & 0xFF;
   gdt_entries[num].base_high   = (base >> 24) & 0xFF;

   gdt_entries[num].limit_low   = (limit & 0xFFFF);
   gdt_entries[num].granularity = (limit >> 16) & 0x0F;

   gdt_entries[num].granularity |= gran & 0xF0;
   gdt_entries[num].access      = access;
}
