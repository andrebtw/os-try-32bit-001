#ifndef STDLIB_H
#define STDLIB_H

#include "stdint.h"

#define NULL ((void *)0)

uint64  strlen(char *string);
/*
str - This is a pointer to the block of memory to fill.

c - This is a second parameter of type integer and converts 
it to an unsigned char before using it to fill a block of memory.

n - This is the number of bytes to be set to the value.
*/
void    *memset(void *buf, int c, size_t n);
void    *memmove(void *dest, const void *src, size_t n);

#endif