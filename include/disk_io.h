#ifndef DISK_IO_H
#define DISK_IO_H

#include "stdint.h"

enum disk_use_type
{
    ATA = 1,
    DMA = 2
};

uint16 *read_sectors(uint32 lba, uint32 sector_count);

#endif
