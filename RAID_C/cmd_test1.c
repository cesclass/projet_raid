/**
 * @file cmd_test1.c
 * @author Dylan CARON (dcaron81.dc@gmail.com)
 * 
 * @brief 
 * Fichier de test d'ecriture de la couche2
 * Initialise le systeme RAID5 et ecrit les octets de 0 a 255 sur le systeme.
 * 
 * @copyright Licence MIT
 */

#include "headers/couche1.h"
#include "headers/couche2.h"

virtual_disk_t r5Disk;

int main(int argc, char *argv[]) {
    /*  Init du RAID 5 */
    printf("Initialisation du systeme RAID 5... \n");

    init_disk_raid5("../RAID/");

    /*  Creation du buffer */
    printf("Creation du buffer de 255 octets... \n");

    uchar buffer[255];
    for(uchar i = 0; i < 255; buffer[i] = i++);

    /*  Ecriture sur le RAID 5 */
    printf("Ecriture du buffer sur le systeme RAID 5... \n");

    write_chunk(255, buffer, 0);
}