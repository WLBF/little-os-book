#include "io.h"
#include "fb_driver.h"
#include "serial_driver.h"

#define PIC1_PORT_A 0x20
#define PIC2_PORT_A 0xA0

/* The PIC interrupts have been remapped */
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT   PIC2_START_INTERRUPT + 7

#define PIC_ACK     0x20

struct registers
{
   uint32_t ds;
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
   uint32_t int_no, err_code;
   uint32_t eip, cs, eflags, useresp, ss;
};

/** pic_acknowledge:
 *  Acknowledges an interrupt from either PIC 1 or PIC 2.
 *
 *  @param num The number of the interrupt
 */
void pic_acknowledge(uint32_t int_no)
{
    if (int_no < PIC1_START_INTERRUPT || int_no > PIC2_END_INTERRUPT) {
        return;
    }

    if (int_no >= PIC2_START_INTERRUPT) {
        outb(PIC2_PORT_A, PIC_ACK);
    }

    outb(PIC1_PORT_A, PIC_ACK);
}

void interrupt_handler(struct registers regs)
{
    fb_write("interrupt\n", 10);
    fb_write_hex(regs.int_no);
    fb_write("\n", 1);
    fb_write_hex(regs.err_code);
    fb_write("\n", 1);
}

void interrupt_request_handler(struct registers regs)
{
    fb_write("interrupt\n", 10);
    pic_acknowledge(regs.int_no);
    interrupt_handler(regs);
}
