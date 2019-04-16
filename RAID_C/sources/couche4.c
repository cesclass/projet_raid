/**
 * @file couche4.c
 * @author Cyril ESCLASSAN (cyril.esclassan@univ-tlse3.fr)
 * 
 * @brief 
 * 
 * @copyright Licence MIT
 * 
 */

#include "../headers/couche4.h"

extern virtual_disk_t r5disk;

int search_inode(char * filename);

uint write_file(char * filename, file_t * file) {
    super_block_t * sb = &(r5disk.super_block);
    inode_table_t inodes = &(r5disk.inodes);
    uint id = search_inode(filename);

    // Inode existante mais pas assez de place
    if(file->size > r5disk.inodes[id].size) {
        delete_inode(id);
    }

    // Inode inexistante : creation d'une inode (avec gestion d'erreur)
    if(id == NO_INODE_MATCH) {
        id = get_unused_inode();
        uint init = init_inode(filename, file->size, sb->first_free_byte);
        if(init == ERR_UNUSED_INODE) return ERR_UNUSED_INODE;
    }

    // Ecriture et MaJ de l'inode et du super block
    inodes[id].size = file->size;
    uint pos = write_chunk(file->size, file->data, inodes[id].first_byte);

    if (pos > sb->first_free_byte) {
        sb->first_free_byte = pos;
    }

    return 0;
}



int search_inode(char * filename) {
    for(int i = 0; i < INODE_TABLE_SIZE; i++) {
        if(!strcmp(filename, r5disk.inodes[i].filename)) return i;
    }
    return NO_INODE_MATCH;
}