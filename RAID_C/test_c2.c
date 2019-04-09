#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "headers/couche2.h"

#define NB_DISK 4

virtual_disk_t r5disk;

int main() {
    r5disk.ndisk = NB_DISK;
    r5disk.raidmode = CINQ;
    

    printf("TEST compute_nstripe : ");
    assert(compute_nstripe(20) == 7);
    assert(compute_nstripe(18) == 6);
    printf("\tOK !\n");

    printf("TEST compute_parity : ");
    stripe_t s;
    s.nblocks = 4;
    s.stripe = malloc(s.nblocks * sizeof(block_t));
    for(int i = 0; i < BLOCK_SIZE; i ++) {
        s.stripe[0].data[i] = 29;
        s.stripe[1].data[i] = 47;
        s.stripe[2].data[i] = 53;
    }
    compute_parity(3, s.stripe, (s.stripe) + 3);
    // Vérification que compute_parity n'aie pas cassé mon stripe
    for(int i = 0; i < BLOCK_SIZE; i ++) {
        assert(s.stripe[0].data[i] == 29);
        assert(s.stripe[1].data[i] == 47);
        assert(s.stripe[2].data[i] == 53);
    }
    //vérifications de la paritée
    for(int i = 0; i < BLOCK_SIZE; i ++) {
        assert((s.stripe[0].data[i] ^ s.stripe[1].data[i] ^ s.stripe[2].data[i]) == s.stripe[3].data[i]);
        assert((s.stripe[1].data[i] ^ s.stripe[2].data[i] ^ s.stripe[3].data[i]) == s.stripe[0].data[i]);
        assert((s.stripe[2].data[i] ^ s.stripe[3].data[i] ^ s.stripe[0].data[i]) == s.stripe[1].data[i]);
        assert((s.stripe[3].data[i] ^ s.stripe[0].data[i] ^ s.stripe[1].data[i]) == s.stripe[2].data[i]);
    }
    printf("\tOK !\n");

    printf("TEST parity_index : ");
    assert(parity_index(0) == 3);
    assert(parity_index(1) == 2);
    assert(parity_index(2) == 1);
    assert(parity_index(3) == 0);

    assert(parity_index(4) == 3);
    assert(parity_index(5) == 2);
    assert(parity_index(6) == 1);
    assert(parity_index(7) == 0);
    printf("\tOK !\n");

    return 0;
}
