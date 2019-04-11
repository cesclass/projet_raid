#include "../headers/gestion_panne.h"

extern virtual_disk_t r5Disk;

int repair_disk(int numdisk){
    block_t repair;
    
    for(int i = 0; i != r5Disk.super_block.nb_blocks_used; i++){
        block_repair(i, numdisk, &repair);
        write_block(i, repair, r5Disk.storage[numdisk]);
    }
    return 0;
}
