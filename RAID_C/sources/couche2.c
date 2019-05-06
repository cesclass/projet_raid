/**
 * @file couche2.c
 * @author Dylan CARON (dcaron81.dc@gmail.com)
 * 
 * @brief 
 * Definitions des fonctions relatives a la couche 2,
 *  soit a la gestion des stripes et du controle d'erreur.
 * 
 * @copyright Licence MIT
 */

#include "../headers/couche1.h"
#include "../headers/couche2.h"
#include "../headers/raid_defines.h"

#include <stdlib.h>

extern virtual_disk_t rDisk;

int compute_nstripe(int nb_block) {
    return nb_block / (rDisk.ndisk - 1) + !(nb_block % (rDisk.ndisk - 1) == 0);
}

void compute_parity(int nb_block, block_t *block_tab, block_t *parity_block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        parity_block->data[i] = 0;
        for(int j = 0; j < nb_block; parity_block->data[i] ^= block_tab[j++].data[i]);
    }
}

int parity_index(int num_stripe) {
    return (- ((num_stripe + 1) % rDisk.ndisk) + rDisk.ndisk) % rDisk.ndisk;
}

/*
 * write_stripe
 *****************************************************************************/

void write_stripe_other(int pos, const stripe_t *src) {
    for (int i = 0; i < src->nblocks; i++)
        write_block(pos, src->stripe[i], rDisk.storage[i]);
}

void write_stripe_r5(int pos, const stripe_t *src) {
    /*  Calcul de l'indice du bloc de parite */
    int i_parity = parity_index(pos);

    for (int i = 0; i < src->nblocks; i++) {
        if (i < i_parity)           /*  Ecriture des blocs positionnees avant le bloc de parite */
            write_block(pos, src->stripe[i], rDisk.storage[i]);
        else if (i > i_parity)      /*  Ecriture des blocs positionnees apres le bloc de parite */
            write_block(pos, src->stripe[i - 1], rDisk.storage[i]);
        else                        /*  Ecriture du bloc de paritee */
            write_block(pos, src->stripe[src->nblocks - 1], rDisk.storage[i]);
    }
}

void write_stripe(int pos, const stripe_t *src) {
    switch (rDisk.raidmode) {
        case ZERO :
        case UN :
            write_stripe_other(pos, src);
            break;
        case CINQ :
            write_stripe_r5(pos, src);
            break;
        default :
            break;
    }
}

/*
 * read_stripe
 *****************************************************************************/

void read_stripe_other(int pos, stripe_t *dest) {
    for (int i = 0; i < dest->nblocks; i++) {
        if (read_block(pos, dest->stripe + i, rDisk.storage[i]) == ERROR_READ)
            block_repair(pos, i, dest->stripe + i);
    }
}

void read_stripe_r5(int pos, stripe_t *dest) {
    /*  Calcul de l'indice du bloc de parite */
    int i_parity = parity_index(pos);

    for (int i = 0; i < dest->nblocks; i ++) {
        if (i < i_parity) {             /*  Lecture des blocs positionnees avant le bloc de parite */
            if (read_block(pos, dest->stripe + i, rDisk.storage[i]) == ERROR_READ)
                block_repair(pos, i, dest->stripe + i);
        } else if (i > i_parity) {      /*  Lecture des blocs positionnees apres le bloc de parite */
            if (read_block(pos, dest->stripe + (i - 1), rDisk.storage[i]) == ERROR_READ)
                block_repair(pos, i, dest->stripe + (i - 1));
        } else {                        /*  Lecture du bloc de paritee */
            if (read_block(pos, dest->stripe + (dest->nblocks - 1), rDisk.storage[i]) == ERROR_READ)
                block_repair(pos, i, dest->stripe + (dest->nblocks - 1));
        }
    }
}

void read_stripe(int pos, stripe_t *dest) {
    switch (rDisk.raidmode) {
        case ZERO :
        case UN :
            read_stripe_other(pos, dest);
            break;
        case CINQ :
            read_stripe_r5(pos, dest);
            break;
        default :
            break;
    }
}

/*
 * write_chunk
 *****************************************************************************/

uint write_chunk_r0(int buf_len, const uchar *buffer, uint pos) {
    stripe_t str;
    str.nblocks = rDisk.ndisk;
    str.stripe = malloc(str.nblocks * sizeof(block_t));

    pos = compute_nstripe(compute_nblock(pos));

    for (int i_buf = 0; i_buf < buf_len;) {
        /*  Construction de la stripe */
        int i_block;
        for( i_block = 0; i_block < str.nblocks; i_block++){
            for(int i_octet = 0; i_octet < BLOCK_SIZE; i_octet ++){
                if(i_buf < buf_len)
                    str.stripe[i_block].data[i_octet] = buffer[i_buf ++];
                else 
                    str.stripe[i_block].data[i_octet] = '\0';
            }
        }

        /*  Ecriture de la stripe sur le disque */
        write_stripe(pos++, &str);
    } 

    return (int)(pos) * rDisk.ndisk * BLOCK_SIZE;
}

uint write_chunk_r1(int buf_len, const uchar *buffer, uint pos) {
    stripe_t str;
    str.nblocks = rDisk.ndisk;
    str.stripe = malloc(str.nblocks * sizeof(block_t));

    pos = compute_nstripe(compute_nblock(pos));

    for (int i_buf = 0; i_buf < buf_len;) {
        /*  Construction de la stripe */
        int i_block;
        for (int i_octet = 0; i_octet < BLOCK_SIZE; i_octet++) {
            for (i_block = 0; i_block < str.nblocks; i_block++) {
                if (i_buf < buf_len)
                    str.stripe[i_block].data[i_octet] = buffer[i_buf];
                else
                    str.stripe[i_block].data[i_octet] = '\0';
            }
            i_buf++;
        } 

        /*  Ecriture de la stripe sur le disque */
        write_stripe(pos++, &str);
    } 

    return (int)(pos) * rDisk.ndisk * BLOCK_SIZE;
}

uint write_chunk_r5(int buf_len, const uchar *buffer, uint pos) {
    stripe_t str;
    str.nblocks = rDisk.ndisk;
    str.stripe = malloc(str.nblocks * sizeof(block_t));

    pos = compute_nstripe(compute_nblock(pos));

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

    return (int)(pos) * rDisk.ndisk * BLOCK_SIZE;
}

uint write_chunk(int buf_len, const uchar *buffer, uint pos) {    
    switch (rDisk.raidmode) {
        case ZERO :
            return write_chunk_r0(buf_len, buffer, pos);
        case UN :
            return write_chunk_r1(buf_len, buffer, pos);
        case CINQ :
            return write_chunk_r5(buf_len, buffer, pos);
        default :
            return 0;
    }
}

/*
 * read_chunk
 *****************************************************************************/

void read_chunk_r0(int buf_len, uchar *buffer, uint pos) {
    stripe_t str;
    str.nblocks = rDisk.ndisk;
    str.stripe = malloc(str.nblocks * sizeof(block_t));

    pos = compute_nstripe(compute_nblock(pos));

    for (int i_buf = 0; i_buf < buf_len;) {
        /*  Lecture d'une Stripe */
        read_stripe(pos++, &str);

        /*  Ecriture de la Stripe lue dans le buffer */
        for (int i_block = 0; i_block < str.nblocks; i_block++) {
            for (int i_octet = 0; i_octet < BLOCK_SIZE; i_octet++) {
                if (i_buf < buf_len)
                    buffer[i_buf++] = str.stripe[i_block].data[i_octet];
            }
        }
    }    
}

void read_chunk_r1(int buf_len, uchar *buffer, uint pos) {
    stripe_t str;
    str.nblocks = rDisk.ndisk;
    str.stripe = malloc(str.nblocks * sizeof(block_t));

    pos = compute_nstripe(compute_nblock(pos));

    for (int i_buf = 0; i_buf < buf_len;) {
        /*  Lecture d'une Stripe */
        read_stripe(pos++, &str);

        /*  Ecriture de la Stripe lue dans le buffer */
        for (int i_octet = 0; i_octet < BLOCK_SIZE; i_octet++) {
            if (i_buf < buf_len)
                buffer[i_buf++] = str.stripe[0].data[i_octet];
        }
    } 
}

void read_chunk_r5(int buf_len, uchar *buffer, uint pos) {
    stripe_t str;
    str.nblocks = rDisk.ndisk;
    str.stripe = malloc(str.nblocks * sizeof(block_t));

    pos = compute_nstripe(compute_nblock(pos));
    
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

void read_chunk(int buf_len, uchar *buffer, uint pos) {
    switch (rDisk.raidmode) {
        case ZERO :
            read_chunk_r0(buf_len, buffer, pos);
            break;
        case UN :
            read_chunk_r1(buf_len, buffer, pos);
            break;
        case CINQ :
            read_chunk_r5(buf_len, buffer, pos);
            break;
        default :
            break;
    }
}
