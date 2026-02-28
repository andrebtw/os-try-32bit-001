#include "../../include/stdint.h"

uint64 strlen(char *string)
{
    uint64 i = 0;

    if (!string)
        return 0;

    while (string[i] != '\0')
        i++;
    
    return i;
}
