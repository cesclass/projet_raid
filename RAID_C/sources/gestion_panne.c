#include "../headers/gestion_panne.h"

extern virtual_disk_t r5Disk;

int repair_disk(int numdisk){
    block_t repair;
    int disk = (numdisk == 0);

    /* calcule du nombre de block a reparer */
    fseek(r5Disk.storage[disk], 0, SEEK_END);
    int taille = ftell(r5Disk.storage[disk]);
    fseek(r5Disk.storage[disk], 0, SEEK_SET);
    int nb_block = compute_nblock(taille);

    for(int i = 0; i != nb_block; i++){
        block_repair(i, numdisk, &repair);
        write_block(i, repair, r5Disk.storage[numdisk]);
    }
    return 0;
}
