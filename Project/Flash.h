
#ifndef FLASH_HAL_H
#define FLASH_HAL_H

void Flash_Enable(void);
int Flash_Erase(int blockCount);
int Flash_Write(const void* data, int wordCount);
void Flash_Read(void* data, int wordCount);

#endif
