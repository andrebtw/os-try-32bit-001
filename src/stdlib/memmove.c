// Standard C library (libc, -lc)

// SYNOPSIS
//        #include <string.h>

//        void *memmove(size_t n;
//                      void dest[n], const void src[n], size_t n);

// DESCRIPTION
//        The  memmove()  function  copies  n bytes from memory area src to memory area dest.  The memory areas may overlap: copying
//        takes place as though the bytes in src are first copied into a temporary array that does not overlap src or dest, and  the
//        bytes are then copied from the temporary array to dest.

// RETURN VALUE
//        The memmove() function returns a pointer to dest.

#include "../include/stdint.h"
#include "../include/stdlib.h"

void    *memmove(void *dest, const void *src, size_t n)
{
    const unsigned char *src_tmp = (const unsigned char *)src;
    unsigned char *dest_tmp = (unsigned char *)dest;

    // NORMAL COPY
    for (size_t i = 0; i < n; i++)
        dest_tmp[i] = src_tmp[i];

    // OVERLAP PROTECTION COPY
    if (dest < src)
    {
        for (int i = n; i >= 0; i--)
            dest_tmp[i] = src_tmp[i];
    }

    return dest_tmp;
}
