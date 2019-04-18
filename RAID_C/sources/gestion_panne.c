/**
 * @file gestion_panne.c
 * @author Guillaume B (guillaume.broise@univ-tlse3.fr)
 * 
 * @brief   
 * Fichier de definition de la fonction de reparation de 
 * disks pour le systeme RAID 5
 * 
 * @copyright Licence MIT
 * 
 */

#include "../headers/gestion_panne.h"

extern virtual_disk_t r5Disk;

void repair_disk(int numdisk){
    block_t repair;
    int disk = (numdisk == 0);

    /* calcule du nombre de block a reparer */
    fseek(r5Disk.storage[disk], 0, SEEK_END);
    int taille = ftell(r5Disk.storage[disk]);
    fseek(r5Disk.storage[disk], 0, SEEK_SET);
    int nb_block = compute_nblock(taille);

    /* repare tous les blocks errones */
    for(int i = 0; i != nb_block; i++){
        block_repair(i, numdisk, &repair);
        write_block(i, repair, r5Disk.storage[numdisk]);
    }
}
