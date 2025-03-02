#ifndef __BANNER_H__
#define __BANNER_H__

#include <stdint.h>

#define VGA_WIDTH  80
#define VGA_HEIGHT 25

#define COOR_TO_VAL(x, y) (y) * VGA_WIDTH + (x)

#define VIDEO_MEM_COLOR_ADDR 0xB8000
#define VIDEO_MEM_NO_COLOR_ADDR 0xB0000

enum 
{
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHT_GRAY = 7,
    DARK_GRAY = 8,
    LIGHT_BLUE = 9,
    LIGHT_GREEN = 10,
    LIGHT_CYAN = 11,
    LIGHT_RED = 12,
    LIGHT_MAGENTA = 13,
    LIGHT_BROWN = 14,
    WHITE = 15
};

void banner_init(void);

void clear_screen(void);
void print_str(const char *str);

void str_to_screen_color(const char *str, int x, int y, uint8_t color);
void str_to_screen_no_color(const char *str, int x, int y);

#endif