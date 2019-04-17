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

void write_stripe(int pos, const stripe_t *src) {
    /*  Calcul de l'indice du bloc de parite */
    int i_parity = parity_index(pos);

    for (int i = 0; i < src->nblocks; i++) {
        if (i < i_parity)           /*  Ecriture des blocs positionnees avant le bloc de parite */
            write_block(pos, src->stripe[i], r5Disk.storage[i]);
        else if (i > i_parity)      /*  Ecriture des blocs positionnees apres le bloc de parite */
            write_block(pos, src->stripe[i - 1], r5Disk.storage[i]);
        else                        /*  Ecriture du bloc de paritee */
            write_block(pos, src->stripe[src->nblocks - 1], r5Disk.storage[i]);
    }
}

void read_stripe(int pos, stripe_t *dest) {
    /*  Calcul de l'indice du bloc de parite */
    int i_parity = parity_index(pos);

    for (int i = 0; i < dest->nblocks; i ++) {
        if (i < i_parity) {             /*  Lecture des blocs positionnees avant le bloc de parite */
            if (read_block(pos, dest->stripe + i, r5Disk.storage[i]) == ERROR_READ)
                block_repair(pos, i, dest->stripe + i);
        } else if (i > i_parity) {      /*  Lecture des blocs positionnees apres le bloc de parite */
            if (read_block(pos, dest->stripe + (i - 1), r5Disk.storage[i]) == ERROR_READ)
                block_repair(pos, i, dest->stripe + (i - 1));
        } else {                        /*  Lecture du bloc de paritee */
            if (read_block(pos, dest->stripe + (dest->nblocks - 1), r5Disk.storage[i]) == ERROR_READ)
                block_repair(pos, i, dest->stripe + (dest->nblocks - 1));
        }
    }
}

uint write_chunk(int buf_len, const uchar *buffer, uint pos) {    
    stripe_t str;
    str.nblocks = r5Disk.ndisk;
    str.stripe = malloc(str.nblocks * sizeof(block_t));

    pos /= (MAX_DISK * BLOCK_SIZE);

    for (int i_buf = 0; i_buf < buf_len;) {
        /*  Construction de la stripe */
        int i_block;
        for (i_block = 0; i_block < str.nblocks - 1; i_block++) {
            for (int i_octet = 0; i_octet < BLOCK_SIZE; i_octet++) {
                if (i_buf < buf_len)
                    str.stripe[i_block].data[i_octet] = buffer[i_buf++];
                else
                    str.stripe[i_block].data[i_octet] = '\0';
            } 
        }   

        /*  Calcul de la paritee */
        compute_parity(str.nblocks - 1, str.stripe, (str.stripe) + i_block);

        /*  Ecriture de la stripe sur le disque */
        write_stripe(pos++, &str);
    } 

    return (int)(pos) * MAX_DISK * BLOCK_SIZE;
}

void read_chunk(int buf_len, uchar *buffer, uint pos) {
    stripe_t str;
    str.nblocks = r5Disk.ndisk;
    str.stripe = malloc(str.nblocks * sizeof(block_t));

    pos /= (MAX_DISK * BLOCK_SIZE);

    for (int i_buf = 0; i_buf < buf_len;) {
        /*  Lecture d'une Stripe */
        read_stripe(pos++, &str);

        /*  Ecriture de la Stripe lue dans le buffer */
        for (int i_block = 0; i_block < str.nblocks - 1; i_block++) {
            for (int i_octet = 0; i_octet < BLOCK_SIZE; i_octet++) {
                if (i_buf < buf_len)
                    buffer[i_buf++] = str.stripe[i_block].data[i_octet];
            }
        }
    }
}