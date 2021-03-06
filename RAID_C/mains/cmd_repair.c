/**
 * @file cmd_repair.c
 * @author Guillaume B (guillaume.broise@univ-tlse3.fr)
 * 
 * @brief   
 * Programme de reparation d'un disk errone
 * 
 * @copyright Licence MIT
 * 
 */

#include "../headers/gestion_panne.h"

#define ERROR_INIT 1
#define ERROR_CREATE_DISK 2

virtual_disk_t rDisk;

int main (int argc, char * argv[]){

    if( argc != 3){
        fprintf(stderr, "Usage : %s repertoire numdisk", argv[0]);
        exit(ERROR_INIT);
    }

    printf("Debut de la reparation du disk\n");
    /* recuperation des arguments du programme */
    char *directory = argv[1];
    int numdisk = atoi(argv[2]);
    char acces[BUFSIZ];

    /* Allocation memoire pour rDisk.storage */
    rDisk.storage = malloc(sizeof(FILE *));

    /* Ouverture des disks du systeme raid */
    for(int i = 0; i < MAX_DISK_R5; i++){
        sprintf(acces,"%s%s%d%s",directory, NAME_DISK, i, "r5");
        if(i != numdisk){     
            /* ouverture en lecture des disks intactes */  
            rDisk.storage[i] = fopen(acces, "rb");
        }
        else {
            /* ouverture en ecriture du disk corrompu */
            rDisk.storage[i] = fopen(acces,"wb");
        }
    }

    printf("Lancement reparation\n");

    repair_disk(numdisk);

    printf("Reparation terminee\n");
    printf("Fermeture du systeme RAID\n");
    switch_off_raid();
    return 0;
}