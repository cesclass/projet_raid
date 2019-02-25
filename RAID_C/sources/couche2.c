//#include "../headers/couche1.h"
#include "../headers/couche2.h"
#include "../headers/raid_defines.h"

int compute_nstripe(int nb_block, int nb_disk) {
    return nb_block / (nb_disk - 1) + !(nb_block % (nb_disk - 1) == 0);
}

void compute_parity(int nb_block, block_t *block_tab, block_t *parity_block) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        parity_block->data[i] = 0;
        for(int j = 0; j < nb_block; parity_block->data[i] ^= block_tab[j++].data[i]);
    }
}

int parity_index(int num_bande, int nb_disk) {
    return (- (num_bande % nb_disk) + nb_disk) % nb_disk;
}

void write_stripe(int pos, const stripe_t *bande, int parity_index) {
    /**
     * @TODO
     * Tester cette fonction avec write_block dès qu'elle sera codé
     * Ne pas oublier de vérifier les arguments 
     */
    for (int i = 0; i < bande->nblocks; i++) {
        if (i < parity_index)
            write_block(pos + i, bande->stripe[i]);
        else if (i > parity_index)
            write_block(pos + i, bande->stripe[i - 1]);
        else
            write_block(pos + i, bande->stripe[bande->nblocks - 1]);
    }
}

