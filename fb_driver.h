#ifndef INCLUDE_FB_DRIVER_H
#define INCLUDE_FB_DRIVER_H

#include "common.h"

/* The foreground and background colors */
#define FB_BLACK          0
#define FB_BLUE           1
#define FB_GREEN          2
#define FB_CYAN           3
#define FB_RED            4
#define FB_MAGENTA        5
#define FB_BROWN          6
#define FB_LIGHT_GREY     7
#define FB_DARK_GREY      8
#define FB_LIGHT_BLUE     9
#define FB_LIGHT_GREEN    10
#define FB_LIGHT_CYAN     11
#define FB_LIGHT_RED      12
#define FB_LIGHT_MAGENTA  13
#define FB_LIGHT_BROWN    14
#define FB_WHITE          15

/* The I/O ports */
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5

/* The I/O port commands */
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

/* The row and colomn numbers of framebuffer */
#define FB_ROW_NUM       25
#define FB_COLOMN_NUM    80

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(uint16_t i, char c, uint8_t fg, uint8_t bg);

/** fb_scroll_lines:
 *  Scroll n lines of the framebuffer.
 *
 *  @param n The number of lines to scroll
 */
int32_t fb_scroll_lines(uint16_t n);

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(uint16_t pos);

/** fb_clear - clear whole framebuffer */
void fb_clear();

/** fb_put - put one character to framebuffer
 *
 *  @param c character to put
 */
void fb_put(char c);

/** fb_write:
 *  writes the contents of the buffer buf of length len to the screen
 *  and automatically advance the cursor after a character has been 
 *  written and scroll the screen if necessary
 *
 *  @param buf The content to write
 *  @param len The length of the content
 */
void fb_write(char *buf, uint32_t len);

/** fb_write_hex - write number in hex to framebuffer
 *
 *  @param c unsigned int to write
 */
void fb_write_hex(uint32_t n);

#endif /* INCLUDE_FB_DRIVER_H */
