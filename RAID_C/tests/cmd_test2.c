/**
 * @file cmd_test2.c
 * @author Dylan CARON (dcaron81.dc@gmail.com)
 * 
 * @brief 
 * Fichier de test de la couche2 : LECTURE
 * Initialise le systeme RAID 5 et lit les octets de 0 a 255 sur le systeme
 * avant de les afficher sur stdout
 * 
 * @copyright Licence MIT
 */

#include "../headers/couche1.h"
#include "../headers/couche2.h"

virtual_disk_t r5Disk;

void dump_buffer(int buf_len, uchar *buffer) {

    for(int i = 0; i < buf_len;) {
        printf("000");
        if (i < 0x100) printf("0");
        if (i < 0x10)  printf("0");
        printf("%x  ", i);
        for (int j = 0; j < 10 && i < buf_len; j++) {
            if (buffer[i] < 0x10) printf("0");
            printf("%x ", buffer[i++]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    /*  Init du RAID 5 */
    printf("Initialisation du systeme RAID 5... \n");

    init_disk_raid5("../RAID/");

    /*  Creation du buffer */
    printf("Lecture des 255 octets sur le systeme RAID 5... \n");

    uchar buffer[255];
    read_chunk(255, buffer, 0);

    /*  Affichage du buffer */
    printf("Affichage du contenu lu : \n");

    dump_buffer(255, buffer);
}