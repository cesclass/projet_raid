#include "../headers/gestion_panne.h"

#define ERROR_INIT 1
#define ERROR_CREATE_DISK 2

virtual_disk_t r5Disk;

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

    /* Allocation memoire pour r5Disk.storage */
    r5Disk.storage = malloc(sizeof(FILE *));

    /* Ouverture des disks du systeme raid */
    for(int i = 0; i < MAX_DISK; i++){
        sprintf(acces,"%s%s%d",directory, NAME_DISK, i);
        if(i != numdisk){     
            /* ouverture en lecture des disks intactes */  
            r5Disk.storage[i] = fopen(acces, "rb");
        }
        else {
            /* ouverture en ecriture du disk corrompu */
            r5Disk.storage[i] = fopen(acces,"wb");
            printf("ECRITURE:%s\n", acces);
        }
    }

    printf("Lancement reparation\n");

    repair_disk(numdisk);

    printf("Reparation terminee\n");
    printf("Fermeture du systeme RAID\n");
    switch_off_raid();
    return 0;
}