#ifndef INCLUDE_SERIAL_DRIVER_H
#define INCLUDE_SERIAL_DRIVER_H

#include "common.h"

/* The I/O ports */

/* All the I/O ports are calculated relative to the data port. This is because
 *  all serial ports (COM1, COM2, COM3, COM4) have their ports in the same
 *  order, but they start at different values.
 */

#define SERIAL_COM1_BASE                0x3F8      /* COM1 base port */

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)

/* The I/O port commands */

/* SERIAL_LINE_ENABLE_DLAB:
 *  Tells the serial port to expect first the highest 8 bits on the data port,
 *  then the lowest 8 bits will follow
 */
#define SERIAL_LINE_ENABLE_DLAB         0x80

/* serial_configure_baud_rate:
 *  Sets the speed of the data being sent. The default speed of a serial
 *  port is 115200 bits/s. The argument is a divisor of that number, hence
 *  the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  @param com      The COM port to configure
 *  @param divisor  The divisor
 */
void serial_configure_baud_rate(uint16_t com, uint16_t divisor);

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_line(uint16_t com);

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int32_t serial_is_transmit_fifo_empty(uint32_t com);

/** serial_write:
 *  writes the contents of the buffer buf of length len to the serial port
 *
 *  @param buf The content to write
 *  @param len The length of the content
 */
void serial_write(char *buf, uint32_t len);

/** serial_write_hex - write number in hex to serial port
 *
 *  @param c unsigned int to write
 */
void serial_write_hex(uint32_t n);

#endif /* INCLUDE_FB_DRIVER_H */
