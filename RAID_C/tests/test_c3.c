/**
 * @file test_c3.c
 * @author Cyril ESCLASSAN (cyril.esclassan@univ-tlse3.fr)
 * 
 * @brief 
 * 
 * @copyright Licence MIT
 * 
 */

#include "../headers/couche1.h"
#include "../headers/couche3.h"

#define ERR_ARGS 101

virtual_disk_t r5Disk;

int main(int argc, char *argv[]) {
    int unused_inode;
    char usage[BUFSIZ], cmd_dump_inode[BUFSIZ];
    sprintf(usage, "Usage : %s repertoire_de_travail\n", argv[0]);
    sprintf(cmd_dump_inode, "./cmd_dump_inode %s", argv[1]);

    /*  Gestion de l'erreur d'usage  */
    if (argc < 2 || argc > 2) {
        fprintf(stderr, usage);
        exit(ERR_ARGS);
    }

    /*  Initialisation du systeme RAID 5  */
    init_disk_raid5(argv[1]);

    /*  inode 0  */
    unused_inode = get_unused_inode();

    sprintf(r5Disk.inodes[unused_inode].filename, "nomFichier0");
    r5Disk.inodes[unused_inode].first_byte = 100;
    r5Disk.inodes[unused_inode].nblock = 101;
    r5Disk.inodes[unused_inode].size = 102;

    /*  inode 1  */
    unused_inode = get_unused_inode();

    sprintf(r5Disk.inodes[unused_inode].filename, "nomFichier1");
    r5Disk.inodes[unused_inode].first_byte = 200;
    r5Disk.inodes[unused_inode].nblock = 201;
    r5Disk.inodes[unused_inode].size = 202;

    /*  Ecriture de la table sur le disque  */
    write_inode_table();

    printf(">> Table d'inode ecrite sur le disque :\n");
    system(cmd_dump_inode);

    /*  RESET de la table d'inode  */
    delete_inode(0);
    delete_inode(1);

    write_inode_table();

    printf(">> Table d'inode reinitialisee :\n");
    system(cmd_dump_inode);   
}