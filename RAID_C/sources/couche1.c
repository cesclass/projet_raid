#include "../headers/couche1.h"
#include "../headers/couche3.h"

extern virtual_disk_t r5Disk;


void init_disk_raid5(char *directory){
  
  /* initialisation des attributs de r5Disk */
  r5Disk.raidmode = CINQ;
  r5Disk.number_of_files = 0;
  r5Disk.ndisk = MAX_DISK;
  r5Disk.storage = malloc(MAX_DISK*sizeof(FILE *));

  char acces[BUFSIZ];
  
  /* ouverture des disks du systeme RAID */
  for(int i = 0; i < MAX_DISK; i++){
      sprintf(acces, "%s%s%d", directory, NAME_DISK, i);
      if(!(r5Disk.storage[i] = fopen(acces, "rb+"))){
        perror("Error open disk");
      }
  }
  
  /* Init Super_Block  && Inode_Table RAID  */

 
  if( ftell(r5Disk.storage[0]) == EOF ){
    /* Super Block */
    r5Disk.super_block.raid_type = r5Disk.raidmode;
    r5Disk.super_block.nb_blocks_used = INODE_TABLE_SIZE * INODE_SIZE + REAL_SUPER_BLOCK_SIZE;
    r5Disk.super_block.first_free_byte = r5Disk.super_block.nb_blocks_used;
    write_super_block();

    /* Table d'inode & Inode */
    for(int i = 0; i++ < INODE_TABLE_SIZE;init_inode("\0",0, 0));
    write_inode_table();
    
  }
  else {
    read_inode_table();
    read_super_block();
  }
  

}

void switch_off_raid(){

  /* fermeture des disk du systeme RAID */
  for(int i = 0; i < r5Disk.ndisk; ++i){
    if(fclose(r5Disk.storage[i]) != 0){
      fprintf(stderr, "Error close disk %d", i);
    }
    printf("Disk n°%d close\n", i);
  }
  exit(SUCCES_OFF);
}


int compute_nblock(int size){
  return size/BLOCK_SIZE + (size % BLOCK_SIZE);
}


int write_block(int pos, block_t block, FILE *dest){

  int block_wr;

  /* verification de pos dans le disk */
  if(fseek(dest, pos*sizeof(block_t), SEEK_SET)){
    return ERROR_WRITE;
  }

  /* block_wr = nombre de block reellement ecrit */
  block_wr = fwrite(&block, sizeof(block_t), 1, dest);

  /* si block_wr different de la taille d'un block retourne ERROR_WRITE */
  return (block_wr * sizeof(block_t) == 1) ? EXIT_SUCCESS : ERROR_WRITE;
}


int read_block(int pos, block_t *block, FILE * src){

  /* verification de pos dans le disk */
  if(fseek(src, pos * sizeof(block_t), SEEK_SET)){
    return ERROR_READ;
  }

  /* verifie que le nombre d'element lu correspond a la taille d'un block */
  return (fread(block, sizeof(block_t) ,1 , src) == 1)? EXIT_SUCCESS : ERROR_READ;
}


void block_repair(int pos, int num_disk, block_t *repair){
  block_t read;
 
  /* set les valeurs du block a reparer a 0 */
  for(int i=0; i < MAX_DISK; repair->data[i++] = 0);

  for(int i = 0 ; i < MAX_DISK; i++){
    if(i != num_disk){
      read_block(pos,&read,r5Disk.storage[i]);
      for(int j = 0; j < BLOCK_SIZE; j++){
        /* XOR des block lu sur les disks intactes du systeme */
        repair->data[j] ^= read.data[j];
      }
    }
  }
  
}


void dump_block_hexa(block_t block){

  int value;
  for(int i = 0; i < BLOCK_SIZE; i++){
    value = (int)block.data[i];
    printf("%x ", value);
  }
  printf("\n");
}
