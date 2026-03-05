#ifndef PAGING_H
#define PAGING_H

#include "../include/stdlib.h"

void paging_init(void);
extern void load_pde(uint32 *);
extern void enable_paging();

// FLAGS //
// Present flag to know if page is in physical memory
#define P_FLAG 0b00000001
// Read write permission flag
#define RW_FLAG 0b00000010
// If page is used for user space or only the supervisor
#define US_FLAG 0b00000100
#define PWT_FLAG 0b00001000
#define PCD_FLAG 0b00010000
// Accessed bit
#define A_FLAG 0b00100000
// Page size
#define PS_FLAG 0b10000000

// is used to determine if a page has been written to
// #define D_FLAG 0b

uint32 alloc_frame(void);

#endif