#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "../headers/couche1.h"

virtual_disk_t r5Disk;

int main(){

    printf("\tVerification Initialisation Raid\n"); 

    init_disk_raid5("../RAID/");

    assert(r5Disk.raidmode == CINQ);
    assert(r5Disk.ndisk == 4);
    assert(r5Disk.storage != NULL);

    for(int i = 0; i < MAX_DISK; i++){
        assert(r5Disk.storage[i] != NULL);
    }

    /* Verification Super Block */
    assert(r5Disk.super_block.first_free_byte != 0);
    printf("First free byte : %d\n", r5Disk.super_block.first_free_byte);
    assert(r5Disk.super_block.nb_blocks_used != 0);
    printf("Nb blocks used : %d\n", r5Disk.super_block.nb_blocks_used);
    assert(r5Disk.super_block.raid_type == CINQ);
    printf("Raid type : %d\n", r5Disk.super_block.raid_type);    


    printf("OK\n");
    printf("---------------------------\n");

    printf("\tVerification write/read_block()\n\n");

    /* test write_block */
    block_t donnee;
    donnee.data[0]=0xAA;
    donnee.data[1]=0xBB;
    donnee.data[2]=0xCC;
    donnee.data[3]=0xDD;
    printf("Block : aa bb cc dd\n\n");
    printf("Block ecrit : ");
    dump_block_hexa(donnee);
    write_block(0,donnee,r5Disk.storage[0]);

    /* test read_block() */
    block_t lecture;
    read_block(0,&lecture,r5Disk.storage[0]);
    printf("Block lu : ");
    dump_block_hexa(lecture);
    write_block(2,lecture, r5Disk.storage[0]);
    printf("---------------------------\n");

    /* test block_repair */
     printf("\tVerification repair_block()\n\n");
    block_t disk0,disk1,disk2;
    block_t repair;

    disk0.data[0] = 0x01;
    disk0.data[1] = 0x01;
    disk0.data[2] = 0x01;
    disk0.data[3] = 0x01;
    write_block(0, disk0, r5Disk.storage[0]);

    disk1.data[0] = 0x00;
    disk1.data[1] = 0x00;
    disk1.data[2] = 0x02;
    disk1.data[3] = 0x00;
    write_block(0, disk1, r5Disk.storage[1]);

    disk2.data[0] = 0x00;
    disk2.data[1] = 0x00;
    disk2.data[2] = 0x00;
    disk2.data[3] = 0x00;
    write_block(0, disk2, r5Disk.storage[2]);

    block_repair(0, 3, &repair);
    printf("od -x ../RAID/vDisk3 : 0101 0103\n");
    printf("---------------------------\n");

    printf("\tFermeture systeme raid\n\n");
    switch_off_raid();
}