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
void fb_write_cell(unsigned short i, char c, unsigned char fg, unsigned char bg)
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
int fb_scroll_lines(unsigned short n)
{
    if (n >= 25) return -1;
    unsigned short i;
    unsigned short *fb = (unsigned short *) 0x00b8000;
    unsigned short total_len = 25 * 80;
    unsigned short shift_len = n * 80;
    unsigned short content_len = total_len - shift_len;

    for (i = 0; i < content_len; ++i)
    {
        fb[i] = fb[i + shift_len];
    }

    for (i = content_len; i < total_len; ++i)
    {
        fb_write_cell(i, '\0', FB_GREEN, FB_DARK_GREY);
    }
    return 0;
}

/** fb_move_cursor:
*  Moves the cursor of the framebuffer to the given position
*
*  @param pos The new position of the cursor
*/
void fb_move_cursor(unsigned short pos)
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
int fb_write(char *buf, unsigned int len)
{
    unsigned short i, j;

    fb_move_cursor(0);
    for (i = 0, j = 0; i < len; ++i)
    {
        if (j < (25 * 80 - 1))
        {
            fb_write_cell(j, buf[i], FB_GREEN, FB_DARK_GREY);
            ++j;
            fb_move_cursor(j);
        }
        else
        {
            fb_scroll_lines(1);
            j -= 80;
            fb_move_cursor(j);
            fb_write_cell(j, buf[i], FB_GREEN, FB_DARK_GREY);
            ++j;
            fb_move_cursor(j);
        }
    }
    return 0;
}