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