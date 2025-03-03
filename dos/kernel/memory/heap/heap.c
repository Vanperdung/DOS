#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "heap.h"
#include "dos.h"
#include "utils/mem_utils.h"

static struct heap kheap;

// Heap memory layout

// |-------------------------------| KERNEL_HEAP_START_ADDR
// |                               |
// |                               |
// |  Heap memory for allocation   |
// |                               |
// |                               |
// |-------------------------------| KERNEL_HEAP_START_ADDR + KERNEL_HEAP_SIZE
// |                               |
// |                               |
// |      Heap block entries       |
// |                               |
// |                               |
// |-------------------------------| 


void heap_memory_init(void)
{
    kheap.start_addr = (void *)KERNEL_HEAP_START_ADDR;
    kheap.table.size = KERNEL_HEAP_SIZE / KERNEL_HEAP_BLOCK_SIZE;
    kheap.table.entries = (struct heap_block_entry *)(KERNEL_HEAP_START_ADDR + KERNEL_HEAP_SIZE); 

    for (uint32_t i = 0; i < kheap.table.size; i++)
    {
        kheap.table.entries[i].flag = HEAP_BLOCK_IS_FREE;
        kheap.table.entries[i].reserved = 0;
        kheap.table.entries[i].is_first = 0;
        kheap.table.entries[i].has_next = 0;
    }
}

void* kmalloc(size_t size)
{
    if (size == 0)
        return NULL;

    int i = 0;
    int blk_start_idx = -1;
    int blk_end_idx = -1;
    int blocks_needed = (size + KERNEL_HEAP_BLOCK_SIZE - 1) / KERNEL_HEAP_BLOCK_SIZE;
    bool can_allocated = false;

    while (i < kheap.table.size)
    {
        if (kheap.table.entries[i].flag == HEAP_BLOCK_IS_FREE)
        {
            if (blk_start_idx == -1)
            {
                blk_start_idx = i;
            }

            blk_end_idx = i;

            if (blk_end_idx - blk_start_idx + 1 == blocks_needed)
            {
                can_allocated = true;
                break;
            }
        }
        else 
        {
            blk_start_idx = 0;
            blk_end_idx = 0;
        }
        i++;
    }

    if (can_allocated)
    {
        for (int j = blk_start_idx; j <= blk_end_idx; j++)
        {
            kheap.table.entries[j].flag = HEAP_BLOCK_IS_TAKEN;
            kheap.table.entries[j].has_next = (j < blk_end_idx) ? HEAP_BLOCK_HAS_NEXT : 0;
            kheap.table.entries[j].is_first = (j == blk_start_idx) ? HEAP_BLOCK_IS_FIRST : 0;
        }

        return (void *)(kheap.start_addr + blk_start_idx * KERNEL_HEAP_BLOCK_SIZE);
    }

    return NULL;
}

void kfree(void *ptr)
{
    if (ptr == NULL && ptr < kheap.start_addr)
        return;

    int blk_start_idx = (ptr - kheap.start_addr) / KERNEL_HEAP_BLOCK_SIZE;

    if (kheap.table.entries[blk_start_idx].is_first != HEAP_BLOCK_IS_FIRST)
        return;

    for (int i = blk_start_idx; i < kheap.table.size; i++)
    {
        kheap.table.entries[i].flag = HEAP_BLOCK_IS_FREE;
        kheap.table.entries[i].is_first = 0;
        if (kheap.table.entries[i].has_next != HEAP_BLOCK_HAS_NEXT)
        {
            kheap.table.entries[i].has_next = 0;
            size_t size = (i - blk_start_idx + 1) * KERNEL_HEAP_BLOCK_SIZE;
            memset(ptr, 0, size);
            break;
        }
    }    
}