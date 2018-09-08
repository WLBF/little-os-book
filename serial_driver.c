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
void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
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
void serial_configure_line(unsigned short com)
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
void serial_configure_buffers(unsigned short com)
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
void serial_configure_modem(unsigned short com)
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
int serial_is_transmit_fifo_empty(unsigned int com)
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
int serial_write(char *buf, unsigned int len)
{
    unsigned int i, j;
    serial_configure_baud_rate(SERIAL_COM1_BASE, 2);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_configure_buffers(SERIAL_COM1_BASE);
    serial_configure_modem(SERIAL_COM1_BASE);

    /* spinning until transmit FIFO queue is empty */
    while (!serial_is_transmit_fifo_empty(SERIAL_COM1_BASE));

    for (i = 0, j = 0; i < len; ++i)
    {
        /* j is send char counter, if j reach the size of the transmit FIFO queue 
         * of given serial port, function spinning until transmit FIFO queue is empty.
         */
        while (j >= 14)
        {
            if (serial_is_transmit_fifo_empty(SERIAL_COM1_BASE))
            {
                j = 0;
                break;
            }
        }
        outb(SERIAL_DATA_PORT(SERIAL_COM1_BASE), buf[i]);
        ++j;
    }
    return 0;
}
