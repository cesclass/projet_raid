/**
 * @file couche3.c
 * @author Cyril E (cyril.esclassan@univ-tlse3.fr)
 * 
 * @brief   
 * Fichier de definition des fonctions de 
 *  la couche 3 pour le projet RAID
 * 
 * @copyright Licence MIT
 */

#include "../headers/couche3.h"

extern virtual_disk_t r5Disk;

void read_inode_table(void) {
    uchar buff[INODE_TABLE_TOTAL_SIZE];
    read_chunk(INODE_TABLE_TOTAL_SIZE, buff, INODES_START);

    inode_t *table = (inode_t *) buff;
    for (int i = 0; i < INODE_TABLE_SIZE; i ++) {
        r5Disk.inodes[i] = table[i];
    }
}

void write_inode_table(void) {
    uchar * buff = (uchar*) r5Disk.inodes;
    write_chunk(INODE_TABLE_TOTAL_SIZE, buff, INODES_START);
}

void delete_inode(int indice) {
    inode_t * inode = &r5Disk.inodes[indice];
    for(int i = 0; i < FILENAME_MAX_SIZE; inode->filename[i++] = '\0');
    inode->first_byte = 0;
    inode->nblock = 0;
    inode->size = 0;
}

uint get_unused_inode(void) {
    for(uint i = 0; i < INODE_TABLE_SIZE; i++) {
        if (!r5Disk.inodes[i].size) return i;
    }
    return ERR_UNUSED_INODE;
}

uint init_inode(char * filename, uint size, uint first_byte) {
    uint indice = get_unused_inode();
    if(indice == ERR_UNUSED_INODE) {
        return indice;
    }

    inode_t * inode = &(r5Disk.inodes[indice]);
    sprintf(inode->filename, filename);
    inode->size = size;
    inode->first_byte = first_byte;
    inode->nblock = compute_nblock(size);
    /*DUGAT*/
    return 0;
}

void read_super_block(void) {
    return;
}

void write_super_block(void) {
    return;
}

void set_first_free_byte(void) {
    return;
}
