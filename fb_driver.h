#ifndef INCLUDE_FB_DRIVER_H
#define INCLUDE_FB_DRIVER_H

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
void fb_write_cell(unsigned short i, char c, unsigned char fg, unsigned char bg);

/** fb_scroll_lines:
 *  Scroll n lines of the framebuffer.
 *
 *  @param n The number of lines to scroll
 */
int fb_scroll_lines(unsigned short n);

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(unsigned short pos);

/** fb_write:
 *  writes the contents of the buffer buf of length len to the screen
 *  and automatically advance the cursor after a character has been 
 *  written and scroll the screen if necessary
 *
 *  @param buf The content to write
 *  @param len The length of the content
 */
int fb_write(char *buf, unsigned int len);

#endif /* INCLUDE_FB_DRIVER_H */