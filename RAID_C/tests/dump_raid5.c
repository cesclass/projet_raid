#include "../headers/gestion_panne.h"



#define ERROR_INIT 1

virtual_disk_t r5Disk;

void dump_stripe_hexa(int pos){
    int pos_parite = parity_index(pos);
    stripe_t stripe;
    read_stripe(pos, &stripe);

    for(int i = 0; i < MAX_DISK; dump_block_hexa(stripe.stripe[i++]));
    printf("\t indice block parite  : %d\n", pos_parite);
}

int main(int argc, char * argv[]){

    if(argc != 3){
        fprintf(stderr,"Usage : %s repertoire taille", argv[0]);
        exit(ERROR_INIT);
    }

    char *directory = argv[1];
    int size = atoi(argv[2]);
    int nb_block = compute_nblock(size);

    init_disk_raid5(directory);

    for(int i = 0; i != nb_block; dump_stripe_hexa(i++));

    return 0;
}