#include "io.h"
#include "timer.h"
#include "fb_driver.h"
#include "interrupt_handler.h"

uint32_t tick = 0;

static void timer_callback(struct registers regs)
{
   tick++;
   fb_write("tick: ", 6);
   fb_write_hex(regs.int_no);
   fb_put('\n');
   fb_write_hex(tick);
   fb_put('\n');
}

void init_timer(uint32_t frequency)
{
   register_interrupt_handler(IRQ0, &timer_callback);

   uint32_t divisor = 1193180 / frequency;

   outb(0x43, 0x36);

   uint8_t l = (uint8_t)(divisor & 0xff);
   uint8_t h = (uint8_t)( (divisor>>8) & 0xff );

   outb(0x40, l);
   outb(0x40, h);
}