#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "headers/couche1.h"
#include "headers/couche2.h"

#define NB_DISK 4

virtual_disk_t r5Disk;

int main() {
    /*  Initialisation du système RAID 5 */
    init_disk_raid5(DESIGNATION);
    
    printf("TEST compute_nstripe : ");
    assert(compute_nstripe(20) == 7);
    assert(compute_nstripe(18) == 6);
    printf("\tOK !\n");

    printf("TEST compute_parity : ");
    stripe_t s;
    s.nblocks = 4;
    s.stripe = malloc(s.nblocks * sizeof(block_t));
    /*  Creation de mon stripe */
    for(int i = 0; i < BLOCK_SIZE; i ++) {
        s.stripe[0].data[i] = 0xA0;
        s.stripe[1].data[i] = 0xBD;
        s.stripe[2].data[i] = 0x12;
    }
    compute_parity(3, s.stripe, (s.stripe) + 3);
    // Vérification que compute_parity n'aie pas cassé mon stripe
    for(int i = 0; i < BLOCK_SIZE; i ++) {
        assert(s.stripe[0].data[i] == 0xA0);
        assert(s.stripe[1].data[i] == 0xBD);
        assert(s.stripe[2].data[i] == 0x12);
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

    printf("TEST write_stripe : ");
    /*
    write_stripe(0, &s, 3);
    write_stripe(1, &s, 2);
    write_stripe(2, &s, 1);
    */    
    printf("\tVérifiez les disques ! (cmd : od -x vDisk_)\n");

    printf("TEST write_chunk : ");
    uchar buff[15];
    buff[0] = 0xAB;
    buff[1] = 0x00;
    buff[2] = 0x00;
    buff[3] = 0x00;
    buff[4] = 0x44;
    buff[5] = 0x44;
    buff[6] = 0x44;
    buff[7] = 0x44;
    buff[8] = 0x88;
    buff[9] = 0x88;
    buff[10] = 0x88;
    buff[11] = 0x88;
    buff[12] = 0xDD;
    buff[13] = 0xDD;
    buff[14] = 0xDD;
    write_chunk(15, buff, 1);

    block_t test;
    test.data[0]=10;
    test.data[1]=20;
    test.data[2]=30;
    test.data[3]=42;

    write_block(0,test,r5Disk.storage[0]);

    block_t lecture;
    read_block(0,&lecture,r5Disk.storage[0]);
    printf("BLOCK WRITE\n");
    hexa_display(test);
    printf("BLOCK READ\n");
    hexa_display(lecture);

    printf("\tVérifiez les ! (cmd : od -x vDisk_)");

    return 0;
}
