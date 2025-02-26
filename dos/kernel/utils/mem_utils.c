#include <stddef.h>
#include <stdint.h>

#include "mem_utils.h"

void *memset(void *str, int c, size_t n)
{
    char *ptr = (char *)str;

    for (int i = 0; i < n; i++)
    {
        ptr[i] = (char)c;
    }
    return str;
}