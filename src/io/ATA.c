#include "../../include/ATA.h"
#include "../../include/io.h"
#include "../../include/vga_text.h"

static void Wait_400ns(void)
{
    uint8 status;

    for (uint64 i = 0; i < 15; i++)
        status = inb(ATA_STATUS_PORT);
}

static int8    Wait_Until_BSY_Cleared(void)
{
    uint32 timeout = 0;
    while (inb(ATA_STATUS_PORT) & 0b10000000 && timeout < 100000)
    {
        timeout++;
    }
    if (timeout >= 100000)
        return 1;
    return 0;
}

static int8    Wait_Until_DRQ_Set(void)
{
    uint32 timeout = 0;
    while (!(inb(ATA_STATUS_PORT) & 0b00001000) && timeout < 100000)
    {
        timeout++;
    }
    if (timeout >= 100000)
        return 1;
    return 0;
}

static int8    Wait_Until_DRQ_Cleared(void)
{
    uint32 timeout = 0;
    while (inb(ATA_STATUS_PORT) & 0b00001000 && timeout < 100000)
    {
        timeout++;
    }
    if (timeout >= 100000)
        return 1;
    return 0;
}

static int8 Wait_Until_Drive_Ready(void)
{
    uint32 timeout = 0;
    if (Wait_Until_BSY_Cleared())
        return 1;
    if (Wait_Until_DRQ_Cleared())
        return 1;
    return 0;
}

int8    drive_init_ATA(void)
{
    uint16 buffer[256];

    uint8 status = inb(ATA_STATUS_PORT);

    // Wait for one of BSY or DRQ to be at 0
    while (status & 0b10000000 && status & 0x00001000)
        status = inb(ATA_STATUS_PORT);

    outb(ATA_SECTORS_COUNT_PORT, 0);
    outb(ATA_LBA_LOW_PORT, 0);
    outb(ATA_LBA_MID_PORT, 0);
    outb(ATA_LBA_HIGH_PORT, 0);
    outb(ATA_DRIVE_HEAD_PORT, 0b11100000);

    Wait_400ns();

    if (Wait_Until_BSY_Cleared())
        return ERRK_BSY;

    if (Wait_Until_DRQ_Set())
        return ERRK_DRQ;

    // Read command
    outb(ATA_CMD_PORT, ATA_READ_CMD);

    // Wait while BSY is 1
    while ((inb(ATA_STATUS_PORT) & 0b10000000));

    // Wait until DRQ is set to 0
    while (!(inb(ATA_STATUS_PORT) & 0b00001000));

    for (uint64 i = 0; i < 256; i++)
        buffer[i] = inw(ATA_DATA_PORT);
    
    if (Wait_Until_BSY_Cleared())
        return ERRK_BSY;
    return 0;
}

/*
works i think
*/
int8   read_sectors_ATA(uint32 lba, uint32 sector_count, uint16 *buffer)
{
    uint64 buffer_index = 0;
    uint16 data;

    uint8 status = inb(ATA_STATUS_PORT);

    if (Wait_Until_Drive_Ready())
        return ERRK_DRQ;

    // Select lba(sector) and sector count to read
    outb(ATA_SECTORS_COUNT_PORT, sector_count);
    outb(ATA_LBA_LOW_PORT, lba & 0xFF);
    outb(ATA_LBA_MID_PORT, lba >> 8);
    outb(ATA_LBA_HIGH_PORT, lba >> 16);
    outb(ATA_DRIVE_HEAD_PORT, (0b11100000 | (lba >> 24)));
    outb(ATA_CMD_PORT, ATA_READ_CMD);

    Wait_400ns();

    if (Wait_Until_BSY_Cleared())
        return ERRK_BSY;

    if (Wait_Until_DRQ_Set())
        return ERRK_DRQ;
    
    // Read words with inw data port
    for (uint64 i = 0; i < 256 * sector_count; i++)
    {
        data = inw(ATA_DATA_PORT);
        buffer[i] = (uint16)data;
    }
    return 0;
}

/*

Todo :
Should work?
*/
int8    write_sectors_ATA(uint32 lba, uint32 sector_count, uint16 *words, uint64 len)
{
    uint64 buffer_index = 0;
    uint16 data;

    uint8 status = inb(ATA_STATUS_PORT);

    if (Wait_Until_Drive_Ready())
        return ERRK_DRQ;

    outb(ATA_SECTORS_COUNT_PORT, sector_count);
    outb(ATA_LBA_LOW_PORT, lba & 0xFF);
    outb(ATA_LBA_MID_PORT, lba >> 8);
    outb(ATA_LBA_HIGH_PORT, lba >> 16);
    outb(ATA_DRIVE_HEAD_PORT, (0b11100000 | (lba >> 24)));
    outb(ATA_CMD_PORT, ATA_WRITE_CMD);

    Wait_400ns();

    if (Wait_Until_DRQ_Set())
        return ERRK_DRQ;

    // Write words with outw data port
    for (size_t i = 0; i < 256; i++)
    {
        outw(ATA_DATA_PORT, words[i]);
        asm volatile (".byte 0xEB, 0x00" ::: "memory");   // Tiny delay using jmp opcode
    }

    if (Wait_Until_BSY_Cleared())
        return ERRK_BSY;

    outb(ATA_CMD_PORT, ATA_FLUSH_CMD);

    return 0;
}
