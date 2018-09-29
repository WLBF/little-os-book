#include "io.h"
#include "dt_flush.h"
#include "descriptor_tables.h"

static void init_gdt();
static void gdt_set_gate(int32_t, uint32_t, uint32_t, uint16_t, uint16_t);

struct gdt_entry gdt_entries[3];
struct gdt_ptr   gdt_ptr;

static void init_idt();
static void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);

struct idt_entry idt_entries[256];
struct idt_ptr   idt_ptr;

void init_descriptor_tables()
{
    init_gdt();
    init_idt();
}

/* init_gdt() - Initialise the global descriptor table. */
static void init_gdt()
{
    gdt_ptr.limit = (sizeof(struct gdt_entry) * 3) - 1;
    gdt_ptr.base  = (uint32_t)&gdt_entries;

    gdt_set_gate(0, 0, 0, 0, 0);                /* null segment */
    gdt_set_gate(1, 0, 0xffffffff, 0x9a, 0xcf); /* code segment */
    gdt_set_gate(2, 0, 0xffffffff, 0x92, 0xcf); /* data segment */

    gdt_flush((uint32_t)&gdt_ptr);
}

/* gdt_set_gate() - Set the value of one GDT entry. */
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint16_t access, uint16_t gran)
{
    gdt_entries[num].base_low    = (base & 0xffff);
    gdt_entries[num].base_middle = (base >> 16) & 0xff;
    gdt_entries[num].base_high   = (base >> 24) & 0xff;

    gdt_entries[num].limit_low   = (limit & 0xffff);
    gdt_entries[num].granularity = (limit >> 16) & 0x0f;

    gdt_entries[num].granularity |= gran & 0xf0;
    gdt_entries[num].access      = access;
}

/* init_idt() - Initialise the interrupt descriptor table. */
static void init_idt()
{
    /* remap the irq table. */
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);

    idt_ptr.limit = sizeof(struct idt_entry) * 256 - 1;
    idt_ptr.base  = (uint32_t)&idt_entries;

    idt_set_gate(0, (uint32_t)interrupt_handler_0, 0x08, 0x8e);
    idt_set_gate(1, (uint32_t)interrupt_handler_1, 0x08, 0x8e);
    idt_set_gate(2, (uint32_t)interrupt_handler_2, 0x08, 0x8e);
    idt_set_gate(3, (uint32_t)interrupt_handler_3, 0x08, 0x8e);
    idt_set_gate(4, (uint32_t)interrupt_handler_4, 0x08, 0x8e);
    idt_set_gate(5, (uint32_t)interrupt_handler_5, 0x08, 0x8e);
    idt_set_gate(6, (uint32_t)interrupt_handler_6, 0x08, 0x8e);
    idt_set_gate(7, (uint32_t)interrupt_handler_7, 0x08, 0x8e);
    idt_set_gate(8, (uint32_t)interrupt_handler_8, 0x08, 0x8e);
    idt_set_gate(9, (uint32_t)interrupt_handler_9, 0x08, 0x8e);
    idt_set_gate(10, (uint32_t)interrupt_handler_10, 0x08, 0x8e);
    idt_set_gate(11, (uint32_t)interrupt_handler_11, 0x08, 0x8e);
    idt_set_gate(12, (uint32_t)interrupt_handler_12, 0x08, 0x8e);
    idt_set_gate(13, (uint32_t)interrupt_handler_13, 0x08, 0x8e);
    idt_set_gate(14, (uint32_t)interrupt_handler_14, 0x08, 0x8e);
    idt_set_gate(15, (uint32_t)interrupt_handler_15, 0x08, 0x8e);
    idt_set_gate(16, (uint32_t)interrupt_handler_16, 0x08, 0x8e);
    idt_set_gate(17, (uint32_t)interrupt_handler_17, 0x08, 0x8e);
    idt_set_gate(18, (uint32_t)interrupt_handler_18, 0x08, 0x8e);
    idt_set_gate(19, (uint32_t)interrupt_handler_19, 0x08, 0x8e);
    idt_set_gate(20, (uint32_t)interrupt_handler_20, 0x08, 0x8e);
    idt_set_gate(21, (uint32_t)interrupt_handler_21, 0x08, 0x8e);
    idt_set_gate(22, (uint32_t)interrupt_handler_22, 0x08, 0x8e);
    idt_set_gate(23, (uint32_t)interrupt_handler_23, 0x08, 0x8e);
    idt_set_gate(24, (uint32_t)interrupt_handler_24, 0x08, 0x8e);
    idt_set_gate(25, (uint32_t)interrupt_handler_25, 0x08, 0x8e);
    idt_set_gate(26, (uint32_t)interrupt_handler_26, 0x08, 0x8e);
    idt_set_gate(27, (uint32_t)interrupt_handler_27, 0x08, 0x8e);
    idt_set_gate(28, (uint32_t)interrupt_handler_28, 0x08, 0x8e);
    idt_set_gate(29, (uint32_t)interrupt_handler_29, 0x08, 0x8e);
    idt_set_gate(30, (uint32_t)interrupt_handler_30, 0x08, 0x8e);
    idt_set_gate(31, (uint32_t)interrupt_handler_31, 0x08, 0x8e);

    idt_set_gate(32, (uint32_t)interrupt_request_handler_0, 0x08, 0x8e);
    idt_set_gate(33, (uint32_t)interrupt_request_handler_1, 0x08, 0x8e);
    idt_set_gate(34, (uint32_t)interrupt_request_handler_2, 0x08, 0x8e);
    idt_set_gate(35, (uint32_t)interrupt_request_handler_3, 0x08, 0x8e);
    idt_set_gate(36, (uint32_t)interrupt_request_handler_4, 0x08, 0x8e);
    idt_set_gate(37, (uint32_t)interrupt_request_handler_5, 0x08, 0x8e);
    idt_set_gate(38, (uint32_t)interrupt_request_handler_6, 0x08, 0x8e);
    idt_set_gate(39, (uint32_t)interrupt_request_handler_7, 0x08, 0x8e);
    idt_set_gate(40, (uint32_t)interrupt_request_handler_8, 0x08, 0x8e);
    idt_set_gate(41, (uint32_t)interrupt_request_handler_9, 0x08, 0x8e);
    idt_set_gate(42, (uint32_t)interrupt_request_handler_10, 0x08, 0x8e);
    idt_set_gate(43, (uint32_t)interrupt_request_handler_11, 0x08, 0x8e);
    idt_set_gate(44, (uint32_t)interrupt_request_handler_12, 0x08, 0x8e);
    idt_set_gate(45, (uint32_t)interrupt_request_handler_13, 0x08, 0x8e);
    idt_set_gate(46, (uint32_t)interrupt_request_handler_14, 0x08, 0x8e);
    idt_set_gate(47, (uint32_t)interrupt_request_handler_15, 0x08, 0x8e);

    idt_flush((uint32_t)&idt_ptr);
}

/* idt_set_entry() - Set the value of one IDT entry. */
static void idt_set_gate(uint8_t num, uint32_t base, uint16_t sel, uint8_t flags)
{
    idt_entries[num].base_lo = base & 0xffff;
    idt_entries[num].base_hi = (base >> 16) & 0xffff;

    idt_entries[num].sel     = sel;
    idt_entries[num].always0 = 0;
    idt_entries[num].flags   = flags;
}
