#ifndef ATA_H
#define ATA_H

#include "stdint.h"

// Data register : read:write pio data bytes
#define ATA_BASE 0x1F0

#define ATA_DATA_PORT ATA_BASE
#define ATA_ERROR_PORT ATA_BASE + 1
#define ATA_FEATURE_PORT ATA_BASE + 1
#define ATA_SECTORS_COUNT_PORT ATA_BASE + 2	
#define ATA_LBA_LOW_PORT ATA_BASE + 3
#define ATA_LBA_MID_PORT ATA_BASE + 4
#define ATA_LBA_HIGH_PORT ATA_BASE + 5
#define ATA_DRIVE_HEAD_PORT ATA_BASE + 6
#define ATA_STATUS_PORT ATA_BASE + 7
#define ATA_CMD_PORT ATA_BASE + 7

#define ATA_IDENTIFY_CMD 0xEC
#define ATA_READ_CMD 0x20
#define ATA_WRITE_CMD 0x30
#define ATA_FLUSH_CMD 0xE7

// ATA driver
int8    drive_init_ATA(void); 
int8    read_sectors_ATA(uint32 lba, uint32 sector_count, uint16 *buffer);
int8    write_sectors_ATA(uint32 lba, uint32 sector_count, uint16 *words, uint64 len);

// Err
#define ERRK_BSY 3
#define ERRK_DRQ 4

#endif