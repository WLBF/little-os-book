#ifndef INCLUDE_GDT_FLUSH_H
#define INCLUDE_GDT_FLUSH_H

#include "common.h"

/** gdt_flush:
 *  Load gdt & flush segment registers.
 *
 *  @param gdt_ptr pointer point to gdt
 */
void gdt_flush(uint32_t gdt_ptr);

#endif /* INCLUDE_GDT_FLUSH_H */
