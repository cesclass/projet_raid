#include "../headers/couche1.h"
#include "../headers/couche2.h"
#include "../headers/raid_defines.h"

#include <stdlib.h>

extern virtual_disk_t r5Disk;

/*  FONCTIONS PRIVEES
 *  (Non incluses dans l'interface couche2.h)
 * ******************************************* */

/**
 * @brief 
 * Calcule le nombre de stripe nécessaire pour stoquer un certains nombre de block.
 * 
 * @param nb_block      Nombre de block
 * 
 * @return int          Nombre de stripe nécessaire 
 */
int compute_nstripe(int nb_block) {
    return nb_block / (r5Disk.ndisk - 1) + !(nb_block % (r5Disk.ndisk - 1) == 0);
}

/**
 * @brief 
 * Calcule le block de parité des block composant block_tab.
 * Le block de parité est placé dans le 3ème paramètre
 * 
 * @param nb_block      Nombre de block dans block_tab
 * @param block_tab     Tableau de block
 * @param parity_block  Block de stockage pour la paritée
 */
void compute_parity(int nb_block, block_t *block_tab, block_t *parity_block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        parity_block->data[i] = 0;
        for(int j = 0; j < nb_block; parity_block->data[i] ^= block_tab[j++].data[i]);
    }
}

/**
 * @brief 
 * Calcule le numéro du disque sur lequel doit être stoqué 
 * le bloc de parité
 * 
 * @param num_stripe    Numéro du stripe (/!\ démmare à 0 !)
 * 
 * @return int          Numéro du disque (/!\ démmare à 0 !)
 */
int parity_index(int num_stripe) {
    return (- ((num_stripe + 1) % r5Disk.ndisk) + r5Disk.ndisk) % r5Disk.ndisk;
}

/**
 * @brief 
 * Ecrit une bande à une position donnee sur le systeme RAID 5
 * 
 * @param pos           N° de la ligne ou ecrire la Stripe
 * @param src           Stripe à écrire
 */
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

/**
 * @brief
 * Lit une bande à une position donnee sur le systeme RAID 5
 * 
 * @param pos           N° de la ligne ou lire la Stripe
 * @param dest          Destination de la Stripe
 */
void read_stripe(int pos, stripe_t *dest) {
    /*  Calcul de l'indice du bloc de parite */
    int i_parity = parity_index(pos);

    for (int i = 0; i < dest->nblocks; i ++) {
        if (i < i_parity)           /*  Lecture des blocs positionnees avant le bloc de parite */
            read_block(pos, dest->stripe + i, r5Disk.storage[i]);
        else if (i > i_parity)      /*  Lecture des blocs positionnees apres le bloc de parite */
            read_block(pos, dest->stripe + (i - 1), r5Disk.storage[i]);
        else                        /*  Lecture du bloc de paritee */
            read_block(pos, dest->stripe + (dest->nblocks - 1), r5Disk.storage[i]);
    }
}


/*  FONCTIONS PUBLIQUES
 *  (Incluses dans l'interface couche2.h)
 * *************************************** */

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
        write_stripe(pos + num_stripe, &stripe);

        num_stripe ++;
    } 
}

void read_chunk(int buf_len, uchar *buffer, uchar pos) {
    return;
}