#include "../headers/gestion_panne.h"

#define ERROR_INIT 1

virtual_disk_t r5Disk;

void dump_stripe_hexa(int pos){
    /*calcule du block de partie */
    int pos_parite = parity_index(pos);

    /* initialisation de la stripe pour la lecture */
    stripe_t stripe;
    stripe.nblocks = r5Disk.ndisk;
    stripe.stripe = malloc(stripe.nblocks * sizeof(block_t));
    /* lecture de la stripe correspond a pos */
    read_stripe(pos, &stripe);

    /*affichage des blocks de la stripe */
    for(int i = 0; i < MAX_DISK; i++){
        dump_block_hexa(stripe.stripe[i]); 
    }
    printf("\tblock parite [%d]\n", pos_parite);
}


int main(int argc, char * argv[]){

    if(argc != 3){
        fprintf(stderr,"Usage : %s repertoire taille", argv[0]);
        exit(ERROR_INIT);
    }

    /* recuperation des arguments du programme */
    char *directory = argv[1];
    int size = atoi(argv[2]);

    /* ouverture du systeme raid5 */
    init_disk_raid5(directory);

    /* calcule le nombre de block necessaire pour ecrire size octet */
    int nb_block = compute_nblock(size);
    /* calcule le nombre de stripe necessaire pour nb_block */
    int nb_stripe = compute_nstripe(nb_block);

    /* affiche des stripes */
    for(int i = 0; i != nb_stripe; i++){
        dump_stripe_hexa(i);
    }

    switch_off_raid();
    return 0;
}