#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#include "common.h"

/** outb:
 *  Sends the given data to the given I/O port. Defined in io.s
 *
 *  @param port The I/O port to send the data to
 *  @param data The data to send to the I/O port
 */
void outb(uint16_t port, uint8_t data);

/** inb:
 *  Read a byte from an I/O port.
 *
 *  @param  port The address of the I/O port
 *  @return      The read byte
 */
uint8_t inb(uint16_t port);

/** inw:
 *  Read 2 bytes from an I/O port.
 *
 *  @param  port The address of the I/O port
 *  @return      The read bytes
 */
uint16_t inw(uint16_t port);

#endif /* INCLUDE_IO_H */