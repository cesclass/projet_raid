#include "../headers/couche3.h"

#define ERR_ARGS        101
#define ERR_RAID_TYPE   102

virtual_disk_t rDisk;

void dump_inode(const inode_t * inode) {
    printf("filename : %s\nsize : %d\nfirst byte : %d\nnb blocks : %d\n\n",
            inode->filename, inode->size, inode->first_byte, inode->nblock);
}

int main(int argc, char *argv[]) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : %s repertoire_de_travail\n", argv[0]);

    /*  Gestion des erreurs d'arguments */
    if (argc != 3) {
        fprintf(stderr, "%s", usage);
        exit(ERR_ARGS);
    }

    /*  Initialisation du systeme RAID 5 */
    if (!init_disk_raid(atoi(argv[1]), argv[2])) {
        fprintf(stderr, "%s", "raid_type inconnu");
        fprintf(stderr, "%s", usage);
        exit(ERR_RAID_TYPE);
    }

    /*  Lecture de la table d'inode  */
    read_inode_table();

    /*  Dump de la table d'inode  */
    for (int i = 0; i < INODE_TABLE_SIZE; i++) {
        if (rDisk.inodes[i].size != 0) {
            printf("# Inode %d\n", i);
            dump_inode(&(rDisk.inodes[i]));
        }
    }
}