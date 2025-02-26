#include <stdint.h>
#include <stddef.h>

#include "text.h"

const char *BANNER = "WELCOME TO DOS :)";

void banner_init(void)
{
    str_to_screen_color(BANNER, 0, 0, RED);
}

void clear_screen(void)
{
    for (int i = 0; i < VGA_HEIGHT; i++)
    {
        for (int j = 0; j < VGA_WIDTH; j++)
        {
            char_to_screen_color(' ', j, i, BLACK);
        }
    }
}

void print_str(const char *str)
{
    str_to_screen_color(str, 0, 0, WHITE);
}

void char_to_screen_color(char c, int x, int y, uint8_t color)
{
    uint16_t *pos = (uint16_t *)VIDEO_MEM_COLOR_ADDR + COOR_TO_VAL(x, y);
    *pos = (c | color << 8); 
}

void char_to_screen_no_color(char c, int x, int y)
{
    uint16_t *pos = (uint16_t *)VIDEO_MEM_NO_COLOR_ADDR + COOR_TO_VAL(x, y);
    *pos = c;
}

void str_to_screen_color(const char *str, int x, int y, uint8_t color)
{
    int index = 0;

    if (str == NULL)
        return;

    for (int i = 0; i < VGA_HEIGHT && str[index] != '\0'; i++)
    {
        for (int j = 0; i < VGA_WIDTH && str[index] != '\0'; j++)
        {
            char_to_screen_color(str[index], x + j, y + i, color);
            index++;
        }
    }
}

void str_to_screen_no_color(const char *str, int x, int y)
{
    int index = 0;

    if (str == NULL)
        return;

    for (int i = 0; i < VGA_HEIGHT && str[index] != '\0'; i++)
    {
        for (int j = 0; i < VGA_WIDTH && str[index] != '\0'; j++)
        {
            char_to_screen_no_color(str[index], x + j, y + i);
            index++;
        }
    }
}