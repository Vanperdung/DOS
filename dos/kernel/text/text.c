#include <stdint.h>
#include <stddef.h>

#include "text.h"

const char *BANNER = "WELCOME TO DOS :)";

struct position
{
    int x;
    int y;
};

static struct position current_pos = {0, 0};

static void char_to_screen_color(char c, int x, int y, uint8_t color)
{
    uint16_t *pos = (uint16_t *)VIDEO_MEM_COLOR_ADDR + COOR_TO_VAL(x, y);
    *pos = (c | color << 8); 
}

static void char_to_screen_no_color(char c, int x, int y)
{
    uint16_t *pos = (uint16_t *)VIDEO_MEM_NO_COLOR_ADDR + COOR_TO_VAL(x, y);
    *pos = c;
}

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
    str_to_screen_color(str, current_pos.x, current_pos.y, WHITE);
}

void str_to_screen_color(const char *str, int x, int y, uint8_t color)
{
    int index = 0;

    if (str == NULL)
        return;

    while (str[index] != '\0' && str[index] != '\n')
    {
        char_to_screen_color(str[index], x, y, color);
        index++;

        if (x == VGA_WIDTH - 1 && y == VGA_HEIGHT - 1)
        {
            x = 0;
            y = 0;
        }
        else if (x == VGA_WIDTH - 1)
        {
            x = 0;
            y++;
        }
        else
        {
            x++;
        }
    }

    if (str[index] == '\n')
    {
        x = 0;
        (y == VGA_HEIGHT - 1) ? (y = 0) : y++;
    }

    current_pos.x = x;
    current_pos.y = y;
}

void str_to_screen_no_color(const char *str, int x, int y)
{
    int index = 0;

    if (str == NULL)
        return;

    while (str[index] != '\0' && str[index] != '\n')
    {
        char_to_screen_no_color(str[index], x, y);
        index++;

        if (x == VGA_WIDTH - 1 && y == VGA_HEIGHT - 1)
        {
            x = 0;
            y = 0;
        }
        else if (x == VGA_WIDTH - 1)
        {
            x = 0;
            y++;
        }
        else
        {
            x++;
        }
    }

    if (str[index] == '\n')
    {
        x = 0;
        (y == VGA_HEIGHT - 1) ? 0 : y++;
    }

    current_pos.x = x;
    current_pos.y = y;
}