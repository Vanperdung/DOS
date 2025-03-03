#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdint.h>
#include <stddef.h>

#define HEAP_BLOCK_IS_FREE 0x00
#define HEAP_BLOCK_IS_TAKEN 0x01

#define HEAP_BLOCK_HAS_NEXT 0x80
#define HEAP_BLOCK_IS_FIRST 0x40


struct heap_block_entry
{
    uint8_t flag : 4;
    uint8_t reserved : 2;
    uint8_t is_first : 1;
    uint8_t has_next : 1;
};

struct heap_table
{
    struct heap_block_entry *entries;
    uint32_t size;
};

struct heap
{
    struct heap_table table;
    void *start_addr;
};

void heap_memory_init(void);
void* kmalloc(size_t size);
void kfree(void *ptr);

#endif // __HEAP_H__