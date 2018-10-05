#include "io.h"
#include "fb_driver.h"
#include "serial_driver.h"
#include "interrupt_handler.h"


isr_t interrupt_handlers[256];

void register_interrupt_handler(uint8_t n, isr_t handler)
{
  interrupt_handlers[n] = handler;
}

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

void isr_common_handler(struct registers regs)
{
    if (interrupt_handlers[regs.int_no] != 0)
    {
        isr_t handler = interrupt_handlers[regs.int_no];
        handler(regs);
    }
}

void irq_common_handler(struct registers regs)
{
    pic_acknowledge(regs.int_no);
    isr_common_handler(regs);
}
