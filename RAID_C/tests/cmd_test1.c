/**
 * @file cmd_test1.c
 * @author Dylan CARON (dcaron81.dc@gmail.com)
 * 
 * @brief 
 * Fichier de test de la couche2 : ECRITURE
 * Initialise le systeme RAID 5 et ecrit les octets de 0 a 255 sur le systeme.
 * 
 * @copyright Licence MIT
 */

#include "../headers/couche1.h"
#include "../headers/couche2.h"

#define ERR_ARGS    101

virtual_disk_t r5Disk;

int main(int argc, char *argv[]) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : %s repertoire_disques\n", argv[0]);

    /*  Gestion des erreurs d'usage */
    if (argc < 2 || argc > 2) {
        fprintf(stderr, usage);
        exit(ERR_ARGS);
    }

    /*  Init du RAID 5 */
    init_disk_raid5("../RAID/");

    /*  Creation du buffer */
    uchar buffer[255];
    for(uchar i = 0; i < 255; buffer[i] = i++);

    /*  Ecriture sur le RAID 5 */
    printf("Ecriture de 255 octets sur le systeme RAID 5... \n");

    write_chunk(255, buffer, 32);
}