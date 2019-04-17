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

uint write_file(char * filename, file_t * file) {
    super_block_t * block = &(r5disk.super_block);
    inode_table_t inodes = &(r5disk.inodes);
    uint id = search_inode(filename);
    uint new_pos;

    // Inode existante mais pas assez de place
    if(id != NO_INODE_MATCH && file->size > inodes[id].size) delete_inode(id);

    // Inode inexistante : creation d'une inode (avec gestion d'erreur)
    if(id == NO_INODE_MATCH) {
        id = init_inode(filename, file->size, block->first_free_byte);
        if(id == ERR_UNUSED_INODE) return 0;
    
    // Inode existante : MaJ de l'inode
    } else {
        inodes[id].size = file->size;
    }

    // Ecriture du fichier
    new_pos = write_chunk(
        file->size, 
        file->data, 
        inodes[id].first_byte
    );
    
    // Ecriture de l'inode
    write_inode_table();

    // MaJ du super block et ecriture si necessaire
    if (new_pos > block->first_free_byte) {
        block->first_free_byte = new_pos;
        write_super_block();
    }

    return 1;
}

uint read_file(char * filename, file_t * file) {
    uint id = search_inode(filename);
    if(id == NO_INODE_MATCH) {
        return 0;
    } else {
        file->size = r5disk.inodes[id].size;
        read_chunk(
            r5disk.inodes[id].size,
            file->data,
            r5disk.inodes[id].first_byte
        );
        return 1;
    }
}

uint delete_file(char * filename) {
    uint id = search_inode(filename);
    if (id == NO_INODE_MATCH) {
        return 0;
    } else {
        delete_inode(id);
        return 1;
    }
}

uint search_inode(char * filename) {
    for(int i = 0; i < INODE_TABLE_SIZE; i++) {
        if(!strcmp(filename, r5disk.inodes[i].filename)) return i;
    }
    return NO_INODE_MATCH;
}