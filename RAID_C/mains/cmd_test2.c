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

#include <stdio.h>

#define ERR_ARGS    101

virtual_disk_t r5Disk;

/**
 * @brief 
 * Affiche proprement le buffer passe en parammetre sur stdout
 * 
 * @param buf_len       Taille du buffer a afficher en octet
 * @param buffer        buffer a afficher
 */
void dump_buffer(int buf_len, uchar *buffer) {
    for(int i = 0; i < buf_len;) {
        printf("000");
        if (i < 0x100) printf("0");
        if (i < 0x10)  printf("0");
        printf("%x  ", i);
        for (int j = 0; j < 8 && i < buf_len; j++) {
            if (buffer[i] < 0x10) printf("0");
            printf("%x ", buffer[i++]);
        }
        printf("\n");
    }
}

int main(int argc, char *argv[]) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : %s repertoire_disques\n", argv[0]);

    /*  Gestion des erreurs d'usage */
    if (argc < 2 || argc > 2) {
        fprintf(stderr, "%s", usage);
        exit(ERR_ARGS);
    }

    /*  Init du RAID 5 */
    init_disk_raid5("../RAID/");

    /*  Lecture des 255 octets */
    printf("Lecture de 255 octets sur le systeme RAID 5 : \n");

    uchar buffer[255];
    read_chunk(255, buffer, 0);

    dump_buffer(255, buffer);
}