/**
 * @file couche4.c
 * @author Cyril ESCLASSAN (cyril.esclassan@univ-tlse3.fr)
 * 
 * @brief 
 * Fichier de definition des fonctions de 
 *  la couche 4 pour le projet RAID.
 * 
 * @copyright Licence MIT
 * 
 */

#include "../headers/couche4.h"

extern virtual_disk_t rDisk;

uint write_file(char * filename, file_t * file) {
    super_block_t * block = &(rDisk.super_block);
    inode_t * inodes = rDisk.inodes;
    uint id = search_inode(filename);
    uint new_pos;

    // Inode existante mais pas assez de place
    if(id != NO_INODE_MATCH && file->size > inodes[id].size) {
        delete_inode(id);
        id = NO_INODE_MATCH;
    }

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
        file->size = rDisk.inodes[id].size;
        read_chunk(
            file->size,
            file->data,
            rDisk.inodes[id].first_byte
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

uint load_file_from_host(char *path, char * filename) {
    FILE * file = fopen(path, "r");
    if (file == NULL) return 0;

    file_t read;
    read.size = 0;
    uchar c = getc(file);
    while(!feof(file)) {
        read.data[read.size++] = c;
        c = getc(file);
    }
    fclose(file);
    
    if(!write_file(filename, &read)) return 0;

    return 1;
}

uint store_file_to_host(char * filename) {
    file_t write;
    if(!read_file(filename, &write)) return 0;

    FILE * file = fopen(filename, "w");
    if(file == NULL) return 0;

    fwrite(write.data, 1, write.size-1, file);
    fclose(file);

    return 1;
}

uint search_inode(char * filename) {
    for(int i = 0; i < INODE_TABLE_SIZE; i++) {
        if(!strcmp(filename, rDisk.inodes[i].filename)) return i;
    }
    return NO_INODE_MATCH;
}