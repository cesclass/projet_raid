//#include "../headers/couche1.h"
#include "../headers/couche2.h"
#include "../headers/raid_defines.h"

#include <stdlib.h>

extern virtual_disk_t r5disk;

int compute_nstripe(int nb_block) {
    return nb_block / (r5disk.ndisk - 1) + !(nb_block % (r5disk.ndisk - 1) == 0);
}

void compute_parity(int nb_block, block_t *block_tab, block_t *parity_block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        parity_block->data[i] = 0;
        for(int j = 0; j < nb_block; parity_block->data[i] ^= block_tab[j++].data[i]);
    }
}

int parity_index(int num_bande) {
    return (- (num_bande % r5disk.ndisk) + r5disk.ndisk) % r5disk.ndisk;
}

void write_stripe(int pos, const stripe_t *bande, int parity_index) {
    /**
     * @TODO
     * Tester cette fonction avec write_block dès qu'elle sera codé
     * Ne pas oublier de vérifier les arguments 
     */
    /*
    for (int i = 0; i < bande->nblocks; i++) {
        if (i < parity_index)
            write_block(pos + i, bande->stripe[i]);
        else if (i > parity_index)
            write_block(pos + i, bande->stripe[i - 1]);
        else
            write_block(pos + i, bande->stripe[bande->nblocks - 1]);
    }
    */
}

void write_chunk(int n, uchar *buffer, uchar start_byte, int nb_disk) {
    /**
     * @TODO
     * Tester cette fonction avec write_block dès qu'elle sera codé
     * Ne pas oublier de vérifier les arguments 
     */
    /*
    stripe_t bande;
    bande.nblocks = nb_disk;
    bande.stripe = malloc(nb_disk * sizeof(block_t));
    int num_bande = 0;

    for (int i_buff = 0; i_buff < n;) {
        int i_block;
        for (i_block = 0; i_block < nb_disk - 1; i_block++) {
            for (int i_octet = 0; i_octet < BLOCK_SIZE; i_octet++) {
                if (i_buff < n)
                    bande.stripe[i_block].data[i_octet] = buffer[i_buff++];
                else
                    bande.stripe[i_block].data[i_octet] = 0;
            } 
        }   

        compute_parity(nb_disk - 1, bande.stripe, (bande.stripe)+i_block);
        write_stripe(start_byte, &bande, parity_index(num_bande));
        num_bande = (num_bande + 1) % nb_disk;
    }
    */
}
