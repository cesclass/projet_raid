#include "../headers/couche3.h"

#define ERR_ARGS 101

virtual_disk_t r5Disk;

void dump_inode(const inode_t * inode) {
    printf("filename : %s\nsize : %d\nfirst byte : %d\nnb blocks : %d\n\n",
            inode->filename, inode->size, inode->first_byte, inode->nblock);
}

int main(int argc, char *argv[]) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : %s repertoire_de_travail\n", argv[0]);

    /*  Gestion de l'erreur d'usage  */
    if (argc < 2 || argc > 2) {
        fprintf(stderr, "%s", usage);
        exit(ERR_ARGS);
    }

    /*  Initialisation du systeme RAID 5  */
    init_disk_raid5(argv[1]);

    /*  Lecture de la table d'inode  */
    read_inode_table();

    /*  Dump de la table d'inode  */
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
        if (r5Disk.inodes[i].size != 0) {
            printf("# Inode %d\n", i);
            dump_inode(&(r5Disk.inodes[i]));
        }
    }
}