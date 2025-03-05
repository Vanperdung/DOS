#ifndef __PAGING_H__
#define __PAGING_H__

#include <stdint.h>

#define NUMS_OF_PDE 1024
#define NUMS_OF_PTE 1024

#define PDE_PRESENT 1
#define PDE_NOT_PRESENT 0

#define PDE_RW 1
#define PDE_RO 0

#define PDE_ALL 1
#define PDE_SUPERVISOR_ONLY 0


// Currently, DOS only supports 4-KiB aligned
struct page_directory_entry
{
    // If present is set, page is actually in physical memory
    uint32_t present : 1; 

    // Read/Write, if rw is set, page is read/write
    // Otherwise, page is read only
    uint32_t rw : 1;

    // User/Supervisor, constrols access to page based on priviledge level
    // If us is set, page may be accessed by all
    // Otherwise, only supervisor has access to page 
    uint32_t us : 1;

    // Write-Through, controls "Write-Through" abilities of the page
    // If pwt is set, write-through caching is enabled
    // If not, then write-back is enabled instead
    uint32_t pwt : 1;

    // Cache Disable, if pcd is set, page will not be cached
    // Otherwise, it will be
    uint32_t pcd : 1;

    // Accessed is used to discover whether PDE or PTE was reading during address translation 
    uint32_t accessed : 1;
    uint32_t reserved2 : 1;

    // Page size determines the size of page frame
    // If page_size is set, PDE maps to a page frame, that is 4MB in size
    // Otherwise, PDE maps to a 4KiB page table
    uint32_t page_size : 1;
    uint32_t reserved1 : 4;

    // A 4-KiB aligned PTE address
    uint32_t page_table_addr : 20;
};

struct page_directory
{
    struct page_directory_entry *entries;
};

struct page_table_entry
{
    // If present is set, page is actually in physical memory
    uint32_t present : 1;

    // Read/Write, if rw is set, page is read/write
    // Otherwise, page is read only
    uint32_t rw : 1;

    // User/Supervisor, constrols access to page based on priviledge level
    // If us is set, page may be access by all
    // Otherwise, only supervisor has access to page    
    uint32_t us : 1;

    // Write-Through, controls "Write-Through" abilities of the page
    // If pwt is set, write-through caching is enabled
    // If not, then write-back is enabled instead
    uint32_t pwt : 1;

    // Cache Disable, if pcd is set, page will not be cached
    // Otherwise, it will be   
    uint32_t pcd : 1;

    // Accessed is used to discover whether PDE or PTE was reading during address translation 
    uint32_t accessed2 : 1;

    // Dirty is used to determine a page has been written to
    uint32_t dirty : 1;

    // If PAT is supported, then PAT along with PCD and PWT shall indicate the memory caching type
    // Otherwise, it is reserved and must be set to 0.
    uint32_t pat : 1;

    // Global tells the processor not to invalidate the TLB entry corresponding to the page upon a MOV to CR3 instruction
    // Bit 7 (PGE) in CR4 must be set to enable global pages.
    uint32_t global : 1;
    uint32_t reserved1 : 3;

    // A 4-KiB aligned physical address
    uint32_t physical_addr : 20;
};

struct page_table
{
    struct page_table_entry *entries;
};


#endif