#include "interrupt_handler.h"
#include "fb_driver.h"
#include "serial_driver.h"

void interrupt_handler(struct registers stack)
{
    serial_write("interrupt\n", 10);
    serial_write_hex(stack.int_no);
    serial_write("\n", 1);
    serial_write_hex(stack.err_code);
    serial_write("\n", 1);
}
