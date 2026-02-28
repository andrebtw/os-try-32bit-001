#include "../include/vga_text.h"
#include "../include/stdint.h"
#include "../include/io.h"
#include "../include/keyboard.h"
#include "../include/stdlib.h"
#include "../include/ATA.h"
#include "../include/interrupts.h"
#include "../include/tests/drive_tests.h"
#include "../include/tests/paging_tests.h"
#include "../include/paging.h"

char last_err[50];

void kmain(void)
{
    IDT_Init();

    outb(0x64, 0xAE); // enables PS/2 port 
    VGA_fill_screen(VGA_BLACK_COLOR);

    drive_init_ATA();
    paging_init();
    
    VGA_print_str("OS Initialised.", 0, 10, VGA_BLACK_COLOR, VGA_GREEN_COLOR);

    drive_test();
    paging_tests();

    for (;;);
}
