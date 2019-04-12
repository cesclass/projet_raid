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

    inode_table_t table = (inode_t *) buff;
    for (int i = 0; i < INODE_TABLE_SIZE; i ++) {
        r5Disk.inodes[i] = table[i];
    }
}

void write_inode_table(void) {
    uchar * buff = (uchar*) r5Disk.inodes;
    write_chunk(INODE_TABLE_TOTAL_SIZE, buff, INODES_START);
}

void delete_inode(void) {
    return;
}

int get_unused_inode(void) {
    for(int i = 0; i < INODE_TABLE_SIZE; i++) {
        if (!r5Disk.inodes[i].size) return i;
    }
    return -1;
}

void init_inode(void) {
    return;
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
