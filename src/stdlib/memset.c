/*
NAME
       memset - fill memory with a constant byte

LIBRARY
       Standard C library (libc, -lc)

SYNOPSIS
       #include "stdlib.h"

       void *memset(size_t n;
                    void s[n], int c, size_t n);

DESCRIPTION
       The memset() function fills the first n bytes of the memory area pointed to by s with the constant byte c.

RETURN VALUE
       The memset() function returns a pointer to the memory area s.
*/

#include "../include/stdint.h"
#include "../include/stdlib.h"

void    *memset(void *buf, int c, size_t n)
{   
    unsigned char *tmp = (unsigned char *)buf;

    if (n <= 0)
        return buf;

    for (size_t i = 0; i < n; i++)
        tmp[i] = (unsigned int)c;

    return buf;
}
