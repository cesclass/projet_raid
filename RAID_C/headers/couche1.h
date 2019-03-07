#ifndef __COUCHE1_H_
#define __COUCHE1_H_

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#include "raid_defines.h"

#define ERROR_FILE 1
#define ERROR_FILE_CLOSE 2
#define ERROR_SEEK_WRITE 3
#define ERROR_WRITE 4
#define ERROR_SEEK_READ 5
#define ERROR_READ 6

#define SUCCES_OFF 10

#define MAX_DISK 10



/**
 * @brief close all disk and close directory
 * 
 * @param directory 
 * @param r5Disk 
 */
void switch_off_raid(DIR *directory, virtual_disk_t *r5Disk);

/**
 * @brief calculate number of block need for a file with his size
 * 
 * @param size 
 * @return int 
 */
int compute_nblock(int size);

/**
 * @brief 
 * 
 * @param pos 
 * @param block 
 * @param dest 
 * @return 3 = Write error 
 */
int write_block(int pos, block_t block, FILE *dest);

int read_block(int pos, block_t *block, FILE *src);

#endif