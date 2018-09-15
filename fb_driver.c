#include "io.h"
#include "fb_driver.h"

/* framebuffer base address */
uint16_t *fb = (uint16_t *)0x000B8000;
/* cursor position */
uint16_t cur_pos = 0;

/** fb_write_cell:
 *  Writes a character with the given foreground and background to position i
 *  in the framebuffer.
 *
 *  @param i  The location in the framebuffer
 *  @param c  The character
 *  @param fg The foreground color
 *  @param bg The background color
 */
void fb_write_cell(uint16_t i, char c, uint8_t fg, uint8_t bg)
{
    uint8_t attr =  (bg << 4) | (fg & 0x0F);
    fb[i] = attr << 8 | c;
}

/** fb_scroll_lines:
 *  Scroll n lines of the framebuffer.
 *
 *  @param n The number of lines to scroll
 */
int32_t fb_scroll_lines(uint16_t n)
{
    if (n >= FB_ROW_NUM) return -1;
    uint16_t i;
    uint16_t *fb = (uint16_t *) 0x00b8000;
    uint16_t total_len = FB_ROW_NUM * FB_COLOMN_NUM;
    uint16_t shift_len = n * FB_COLOMN_NUM;
    uint16_t content_len = total_len - shift_len;

    for (i = 0; i < content_len; ++i)
    {
        fb[i] = fb[i + shift_len];
    }

    for (i = content_len; i < total_len; ++i)
    {
        fb_write_cell(i, '\0', FB_WHITE, FB_BLACK);
    }
    return 0;
}

/** fb_move_cursor:
 *  Moves the cursor of the framebuffer to the given position
 *
 *  @param pos The new position of the cursor
 */
void fb_move_cursor(uint16_t pos)
{
    outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    outb(FB_DATA_PORT,    pos & 0x00FF);
}

/** fb_clear - clear whole framebuffer */
void fb_clear()
{
    fb_scroll_lines(FB_ROW_NUM);
    fb_move_cursor(0);
}

/** fb_put - put one character to framebuffer
 *
 *  @param c character to put
 */
void fb_put(char c)
{
    if (cur_pos < (FB_ROW_NUM * FB_COLOMN_NUM - 1))
    {
        fb_write_cell(cur_pos, c, FB_WHITE, FB_BLACK);
        ++cur_pos;
        fb_move_cursor(cur_pos);
    }
    else
    {
        fb_scroll_lines(1);
        cur_pos -= FB_COLOMN_NUM;
        fb_move_cursor(cur_pos);
        fb_write_cell(cur_pos, c, FB_WHITE, FB_BLACK);
        ++cur_pos;
        fb_move_cursor(cur_pos);
    }
}

/** fb_write:
 *  writes the contents of the buffer buf of length len to the screen
 *  and automatically advance the cursor after a character has been 
 *  written and scroll the screen if necessary
 *
 *  @param buf The content to write
 *  @param len The length of the content
 */
void fb_write(char *buf, uint32_t len)
{
    uint16_t i;
    for (i = 0; i < len; ++i)
    {
        fb_put(buf[i]);
    }
}

/** fb_write_hex - write number in hex to framebuffer
 *
 *  @param c unsigned int to write
 */
void fb_write_hex(uint32_t n)
{
    char output[10] = "0x00000000";
    char hex[16] = "0123456789abcdef"; /* number to hex characters map */
    uint8_t i;
    
    for (i = 0; i < 8; ++i)
    {
        output[9 - i] = hex[n & 0x0000000f];
        n >>= 4;
    }

    fb_write(output, 10);
}
