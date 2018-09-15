#include "io.h"
#include "serial_driver.h"

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
void serial_configure_baud_rate(uint16_t com, uint16_t divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com),
            SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com),
            (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com),
            divisor & 0x00FF);
}

/** serial_configure_line:
 *  Configures the line of the given serial port. The port is set to have a
 *  data length of 8 bits, no parity bits, one stop bit and break control
 *  disabled.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_line(uint16_t com)
{
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

/** serial_configure_buffers:
 *  Configures the send buffer and receive buffer of the given serial port.
 *  The port is set to enable FIFO, clear both receiver and transmission FIFO
 *  queues, use 14 bytes as size of queue.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_buffers(uint16_t com)
{
    /* Bit:     | 7 6 | 5  | 4 | 3   | 2   | 1   | 0 |
     * Content: | lvl | bs | r | dma | clt | clr | e |
     * Value:   | 1 1 | 0  | 0 |  0  |  1  |  1  | 1 | = 0xC7
     */
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

/** serial_configure_modem:
 *  Configures the modem control register of the given serial port.
 *  The port is set to be ready to send data, interrupts disabled.
 *
 *  @param com  The serial port to configure
 */
void serial_configure_modem(uint16_t com)
{
    /* Bit:     | 7 | 6 | 5  | 4  | 3   | 2   | 1   | 0   |
     * Content: | r | r | af | lb | ao2 | ao1 | rts | dtr |
     * Value:   | 0 | 0 | 0  | 0  | 0   |  0  |  1  |   1 | = 0x03
     */
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

/** serial_is_transmit_fifo_empty:
 *  Checks whether the transmit FIFO queue is empty or not for the given COM
 *  port.
 *
 *  @param  com The COM port
 *  @return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int32_t serial_is_transmit_fifo_empty(uint32_t com)
{
    /* 0x20 = 0010 0000 */
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

/** serial_write:
 *  writes the contents of the buffer buf of length len to the serial port
 *
 *  @param buf The content to write
 *  @param len The length of the content
 */
void serial_write(char *buf, uint32_t len)
{
    uint32_t i;
    serial_configure_baud_rate(SERIAL_COM1_BASE, 2);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_configure_buffers(SERIAL_COM1_BASE);
    serial_configure_modem(SERIAL_COM1_BASE);

    for (i = 0; i < len; ++i)
    {
        /* spinning until transmit FIFO queue is empty */
        while (!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE));
        outb(SERIAL_DATA_PORT(SERIAL_COM1_BASE), buf[i]);
    }
}

/** serial_write_hex - write number in hex to serial port
 *
 *  @param c unsigned int to write
 */
void serial_write_hex(uint32_t n)
{
    char output[10] = "0x00000000";
    char hex[16] = "0123456789abcdef"; /* number to hex characters map */
    uint8_t i;
    
    for (i = 0; i < 8; ++i)
    {
        output[9 - i] = hex[n & 0x0000000f];
        n >>= 4;
    }

    serial_write(output, 10);
}
