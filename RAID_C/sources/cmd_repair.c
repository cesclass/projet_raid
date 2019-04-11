#include "headers/gestion_panne.h"

#define ERROR_INIT 1
#define ERROR_CREATE_DISK 2

extern virtual_disk_t r5Disk;

int main (int argc, char * argv[]){

    if( argc != 3){
        fprintf(stderr, "Usage : %s repertoire numdisk", argv[0]);
        exit(ERROR_INIT);
    }

    printf("Debut de la reparation du disk\n");
    char *directory = argv[1];
    int numdisk = atoi(argv[2]);
    char acces[BUFSIZ];

    sprintf(acces,"%s%s%d", directory,NAME_DISK, numdisk);
    if(!(r5Disk.storage[numdisk] = fopen(acces,"wb+"))){
        perror("Error reopen wrong disk");
        exit(ERROR_CREATE_DISK);
    }
    printf("Lancement reparation\n");

    repair_disk(numdisk);

    printf("Reparation terminee\n");
}