#include "../headers/couche1.h"
#include "../headers/couche2.h"
#include "../headers/raid_defines.h"

#include <stdlib.h>

extern virtual_disk_t r5Disk;

int compute_nstripe(int nb_block) {
    return nb_block / (r5Disk.ndisk - 1) + !(nb_block % (r5Disk.ndisk - 1) == 0);
}

void compute_parity(int nb_block, block_t *block_tab, block_t *parity_block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        parity_block->data[i] = 0;
        for(int j = 0; j < nb_block; parity_block->data[i] ^= block_tab[j++].data[i]);
    }
}

int parity_index(int num_stripe) {
    return (- ((num_stripe + 1) % r5Disk.ndisk) + r5Disk.ndisk) % r5Disk.ndisk;
}

void write_stripe(int pos, const stripe_t *stripe, int parity_index) {
    for (int i = 0; i < stripe->nblocks; i++) {
        if (i < parity_index)       /*  Ecriture des blocs positionnees avant le bloc de parite */
            write_block(pos, stripe->stripe[i], r5Disk.storage[i]);
        else if (i > parity_index)  /*  Ecriture des blocs positionnees apres le bloc de parite */
            write_block(pos, stripe->stripe[i - 1], r5Disk.storage[i]);
        else                        /*  Ecriture du bloc de paritee */
            write_block(pos, stripe->stripe[stripe->nblocks - 1], r5Disk.storage[i]);
    }
}

void write_chunk(int buf_len, uchar *buffer, uchar pos) {
    /**
     * @TODO
     * Tester cette fonction avec write_block dès qu'elle sera codé
     */
    
    stripe_t stripe;
    stripe.nblocks = r5Disk.ndisk;
    stripe.stripe = malloc(r5Disk.ndisk * sizeof(block_t));
    int num_stripe = 0;

    for (int i_buff = 0; i_buff < buf_len;) {
        /*  Construction de la stripe */
        int i_block;
        for (i_block = 0; i_block < r5Disk.ndisk - 1; i_block++) {
            for (int i_octet = 0; i_octet < BLOCK_SIZE; i_octet++) {
                if (i_buff < buf_len)
                    stripe.stripe[i_block].data[i_octet] = buffer[i_buff++];
                else
                    stripe.stripe[i_block].data[i_octet] = '\0';
            } 
        }   

        /*  Calcul de la paritee */
        compute_parity(r5Disk.ndisk - 1, stripe.stripe, (stripe.stripe) + i_block);

        /*  Ecriture de la stripe sur le disque */
        write_stripe(pos + num_stripe, &stripe, parity_index(num_stripe));

        num_stripe ++;
    } 
}