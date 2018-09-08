#ifndef INCLUDE_GDT_FLUSH_H
#define INCLUDE_GDT_FLUSH_H

/** gdt_flush:
 *  Load gdt & flush segment registers.
 *
 *  @param gdt_ptr pointer point to gdt
 */
void gdt_flush(unsigned int gdt_ptr);

#endif /* INCLUDE_GDT_FLUSH_H */
