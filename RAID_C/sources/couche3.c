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

/* 
 * Gestion des inodes
 * ***************************************************************************/

void read_inode_table(void) {
    uchar buff[INODE_TABLE_TOTAL_SIZE];
    read_chunk(INODE_TABLE_TOTAL_SIZE, buff, INODES_START);

    // cast et copie des inodes dans la table
    inode_t *table = (inode_t *) buff;
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
        r5Disk.inodes[i] = table[i];
    } 
}

void write_inode_table(void) {
    uchar * buff = (uchar*) r5Disk.inodes;
    write_chunk(INODE_TABLE_TOTAL_SIZE, buff, INODES_START);
}

void delete_inode(int indice) {
    inode_t * inode = &r5Disk.inodes[indice];
    inode->filename[0] = '\0';
    inode->first_byte = 0;
    inode->nblock = 0;
    inode->size = 0;
}

uint get_unused_inode(void) {
    for(uint i = 0; i < INODE_TABLE_SIZE; i++) {
        // si size vaut 0, l'inode est vide
        if (r5Disk.inodes[i].filename[0] == '\0') return i;
    }
    return ERR_UNUSED_INODE;
}

uint init_inode(char * filename, uint size, uint first_byte) {
    uint indice = get_unused_inode();
    if(indice == ERR_UNUSED_INODE) return indice;

    inode_t * inode = &(r5Disk.inodes[indice]);
    sprintf(inode->filename, filename);
    inode->size = size;
    inode->first_byte = first_byte;
    inode->nblock = compute_nblock(size);
    return indice;
}

/*
 * Gestion du super block
 * ***************************************************************************/

void read_super_block(void) {
    uchar buff[REAL_SUPER_BLOCK_SIZE];
    read_chunk(REAL_SUPER_BLOCK_SIZE, buff, 0);

    // cast et copie du super block
    super_block_t * block = (super_block_t*) buff;
    r5Disk.super_block = (*block);
}

void write_super_block(void) {
    uchar * buff = (uchar*) &(r5Disk.super_block);
    write_chunk(REAL_SUPER_BLOCK_SIZE, buff, 0);
}

void set_first_free_byte(uint first_free_byte) {
    r5Disk.super_block.first_free_byte = first_free_byte;
}
