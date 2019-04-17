/**
 * @file test_complet_c3.c
 * @author Cyril ESCLASSAN (cyril.esclassan@univ-tlse3.fr)
 * 
 * @brief 
 * Fichier de test final (inodes, super block)
 * 
 * @copyright Licence MIT
 * 
 */

#include "../headers/couche1.h"
#include "../headers/couche3.h"

virtual_disk_t r5Disk;

void dumpping(void);
void dump_inode(const inode_t * inode);
void dump_super_block(const super_block_t * block);

int main(int argc, char ** argv) {
    // gestion d'erreur sur les arguments
    if (argc < 2 || argc > 2) {
        exit(EXIT_FAILURE);
    }

    printf("> Lancement du TEST ! \n");

    // initialisation RAID 5
    init_disk_raid5(argv[1]);

    // super bloc
    printf("> Initialisation du super bloc \n");
    super_block_t * block = &r5Disk.super_block;
    set_first_free_byte(REAL_SUPER_BLOCK_SIZE+INODE_TABLE_TOTAL_SIZE);
    block->nb_blocks_used = 1100;
    block->raid_type = CINQ;


    // inodes (0 et 1)
    printf("> Initialisation des inodes \n");
    if(init_inode("Fichier1", 88, 800)) printf("erreur init inode");
    if(init_inode("Fichier2", 44, 1000)) printf("erreur init inode");

    // ecriture sur les disques virtuels
    printf("> Ecriture du super bloc et des inodes \n");
    write_super_block();
    write_inode_table();

    // dump
    printf("\n");
    dumpping();

    // reset du super block
    printf("> Suppression du super bloc\n");
    block->first_free_byte = 0;
    block->nb_blocks_used = 0;
    block->raid_type = ZERO;

    // reset des inodes
    printf("> Suppression des inodes\n");
    delete_inode(get_unused_inode()-1);
    delete_inode(get_unused_inode()-1);

    // dump
    printf("\n");
    dumpping();

    // lecture des disques virtuels
    printf("> Lecture du super bloc et des inodes\n");
    read_super_block();
    read_inode_table();

    // dump
    printf("\n");
    dumpping();

    return 0;
}

void dumpping(void) {
    // dump du super bloc
    printf("# DUMP Super bloc\n");
    dump_super_block(&(r5Disk.super_block));

    // dump de la table d'inode
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
        if (r5Disk.inodes[i].filename[0] != '\0') {
            printf("# DUMP Inode %d\n", i);
            dump_inode(&(r5Disk.inodes[i]));
        }
    }
}

void dump_inode(const inode_t * inode) {
    printf("filename : %s\nsize : %d\nfirst byte : %d\nnb blocks : %d\n\n",
            inode->filename, inode->size, inode->first_byte, inode->nblock);
}

void dump_super_block(const super_block_t * block) {
    printf("RAID Type : %d\nfirst free byte : %d\nnb block used : %d\n\n",
            block->raid_type, block->first_free_byte, block->nb_blocks_used);
}