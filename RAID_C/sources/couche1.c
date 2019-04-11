#include "../headers/couche1.h"

extern virtual_disk_t r5Disk;

/*=========================================================*/

void init_disk_raid5(char *directory){
  
  r5Disk.raidmode = CINQ;
  r5Disk.number_of_files = 0;
  r5Disk.ndisk = MAX_DISK;
  r5Disk.storage = malloc(MAX_DISK*sizeof(FILE *));

  char acces[BUFSIZ];
 
  for(int i = 0; i < MAX_DISK; i++){
      sprintf(acces, "%s%s%d", directory, NAME_DISK, i);
      if(!(r5Disk.storage[i] = fopen(acces, "rb+"))){
        perror("Error open disk");
      }
  }
  
  /* Init Super_Block  && Inode_Table RAID 
  *
  * add couche3 fct
  * 
  */
}

void switch_off_raid(){

  for(int i = 0; i < r5Disk.ndisk; ++i){
    if(fclose(r5Disk.storage[i]) != 0){
      fprintf(stderr, "Error close disk %d", i);
    }
    printf("Disk n°%d close\n", i);
  }
  exit(SUCCES_OFF);
}

/*=========================================================*/

int compute_nblock(int size){
  return size/BLOCK_SIZE + (size % BLOCK_SIZE);
}


int write_block(int pos, block_t block, FILE *dest){

  int block_wr;

  if(fseek(dest, pos*sizeof(block_t), SEEK_SET)){
    perror("Error write pos");
    return ERROR_SEEK_WRITE;
  }
  block_wr = fwrite(&block, sizeof(block_t), 1, dest);

  return (block_wr * sizeof(block_t) == 1) ? EXIT_SUCCESS : ERROR_WRITE;
}


int read_block(int pos, block_t *block, FILE * src){

  if(fseek(src, pos * sizeof(block_t), SEEK_SET)){
    perror("Error read pos");
    return ERROR_SEEK_READ;
  }

  return (fread(block, sizeof(block_t) ,1 , src) == 1)? EXIT_SUCCESS : ERROR_READ;
}


void block_repair(int pos, int num_disk, block_t *repair){
  block_t read;
  for(int i=0; i < MAX_DISK; repair->data[i++] = 0);

  for(int i = 0 ; i < MAX_DISK; i++){
    if(i != num_disk){
      read_block(pos,&read,r5Disk.storage[i]);
      for(int j = 0; j < BLOCK_SIZE; j++){
        repair->data[j] ^= read.data[j];
      }
    }
  }
  
}

/*=========================================================*/

void dump_block_hexa(block_t block){

  int value;
  for(int i = 0; i < BLOCK_SIZE; i++){
    value = (int)block.data[i];
    printf("%x ", value);
  }
  printf("\n");
}
