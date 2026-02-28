#include "../include/io.h"
#include "../include/stdint.h"

// Read a byte from a port 
uint8 inb(uint16 port)
{
    uint8 result;
    asm volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

// Read a word from a port 
uint16 inw(uint16 port)
{
    uint16 result;
    asm volatile ("inw %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

// Write a byte to a port
void outb(uint16 port, uint8 value)
{
    asm volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

// Write a word to a port
void outw(uint16 port, uint16 value)
{
    asm volatile ("outw %0, %1" : : "a"(value), "Nd"(port));
}
