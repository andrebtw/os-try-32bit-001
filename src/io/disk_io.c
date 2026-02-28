#include "../../include/disk_io.h"
#include "../../include/stdint.h"
#include "../../include/ATA.h"

uint32 disk_use = ATA;

uint8 read_sectors(uint32 lba, uint32 sector_count, uint16 *buffer)
{
    if (disk_use == ATA)
    {
        uint32 ret_code = read_sectors_ATA(lba, sector_count, buffer);
        if (ret_code)
            return ret_code;
    }

    return 0;
}

