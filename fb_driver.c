#include "io.h"
#include "fb_driver.h"

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
    char *fb = (char *) 0x000B8000;
    fb[2 * i] = c;
    fb[2 * i + 1] = ((fg & 0x0F) << 4) | (bg & 0x0F);
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

/** fb_write:
 *  writes the contents of the buffer buf of length len to the screen
 *  and automatically advance the cursor after a character has been 
 *  written and scroll the screen if necessary
 *
 *  @param buf The content to write
 *  @param len The length of the content
 */
int32_t fb_write(char *buf, uint32_t len)
{
    uint16_t i, j;

    fb_move_cursor(0);
    for (i = 0, j = 0; i < len; ++i)
    {
        if (j < (FB_ROW_NUM * FB_COLOMN_NUM - 1))
        {
            fb_write_cell(j, buf[i], FB_WHITE, FB_BLACK);
            ++j;
            fb_move_cursor(j);
        }
        else
        {
            fb_scroll_lines(1);
            j -= FB_COLOMN_NUM;
            fb_move_cursor(j);
            fb_write_cell(j, buf[i], FB_WHITE, FB_BLACK);
            ++j;
            fb_move_cursor(j);
        }
    }
    return 0;
}