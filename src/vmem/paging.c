#include "../../include/paging.h"

uint32 page_directory_entry[1024] __attribute__((aligned(4096)));

uint32 page_table_entry0[1024] __attribute__((aligned(4096)));

uint8 physical_mem_bitmap[4096]; // 128MB total memory bitmap that 4096 bytes can store

static void reserve_first_mbyte();

static void fill_pte(void)
{
    // Page table entry 0
    for (size_t i = 0; i < 1024; i++)
    {
        page_table_entry0[i] = i * 4096 | P_FLAG | RW_FLAG;
    }
}

/* Filling each page directory with only zeros &
setting page table entry address + flags to each pde */
static void fill_pde(void)
{
    for (size_t i = 0; i < 1024; i++)
    {
        page_directory_entry[i] = 0x0000;
    }
    page_directory_entry[0] = (uint32)page_table_entry0 | P_FLAG | RW_FLAG;
}

void paging_init()
{
    fill_pte();
    fill_pde();
    reserve_first_mbyte();

    load_pde(page_directory_entry);
    enable_paging();
}

/////////////////////
//     FRAMES      //
/////////////////////
static void reserve_first_mbyte()
{
    // One frame is 4096 bytes, I need 4096 * 256 = 1MB so 256 frames
    // Each frame is 1 bit so I need 256 bits which is 256/8 = 32 bytes
    for (size_t i = 0; i < 32; i++)
    {
        physical_mem_bitmap[i] = 0b11111111; // 8 frames = 1 byte
    }
}

static void reserve_frame(uint32 address)
{
    address = address & 0xFFFFF000; // Ignore if address isnt 4096 bytes aligned
}

static void free_frame(uint32 address)
{
    address = address & 0xFFFFF000; // Ignore if address isnt 4096 bytes aligned
}

// 0 for free 1 for reserved
static uint8 check_frame(uint32 address)
{
    address = address & 0xFFFFF000; // Ignore if address isnt 4096 bytes aligned
    return 0;
}

uint32 alloc_frame(void)
{

    return 0;
}
