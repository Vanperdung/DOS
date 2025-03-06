#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include "paging.h"
#include "heap/heap.h"
#include "utils/mem_utils.h"

static struct page_directory page_directory;
static struct page_table page_table;

/*
*   Tell the processor where to find out page directory by putting
*   it's address into CR3 register
*/ 
void load_page_directory_table(uint32_t *ptr);

void enable_paging(void);

static int page_directory_init(void)
{
    // Create a blank Page Directory
    page_directory.entries = kmalloc(NUMS_OF_PDE * sizeof(struct page_directory_entry));
    if (!page_directory.entries)
        return -1;

    memset(page_directory.entries, 0, NUMS_OF_PDE * sizeof(struct page_directory_entry));

    /*
    *   Set each entry to not present so that if the MMU looks for that page table,
    *   it will see that it is not there yet.
    */ 
    for (int i = 0; i < NUMS_OF_PDE; i++)
    {
        // A page is "not present" when it's not used
        page_directory.entries[i].present = PDE_NOT_PRESENT;
        page_directory.entries[i].rw = PDE_RW;
        page_directory.entries[i].us = PDE_SUPERVISOR_ONLY;
    }

    return 0;
}

static int page_table_init(void)
{
    page_table.entries = kmalloc(NUMS_OF_PTE * sizeof(struct page_table_entry));
    if (!page_table.entries)
        return -1;

    memset(page_table.entries, 0, NUMS_OF_PTE * sizeof(struct page_directory_entry));

    for (int i = 0; i < NUMS_OF_PTE; i++)
    {
        // A page is "not present" when it's not used
        page_directory.entries[i].present = PDE_NOT_PRESENT;
        page_directory.entries[i].rw = PDE_RW;
        page_directory.entries[i].us = PDE_SUPERVISOR_ONLY;
    }

}

int paging_init(void)
{
    int ret; 

    ret = page_directory_init();
    if (ret)
        return ret;
    
    
}