#include "../headers/couche1.h"


/*=========================================================*/
void init_super_block_raid5(virtual_disk_t *r5Disk){

  r5Disk->super_block.raid_type = r5Disk->raidmode;
  r5Disk->super_block.nb_blocks_used = 0;
  r5Disk->super_block.first_free_byte = 0;
}

virtual_disk_t init_disk_raid5(DIR *directory){
  
  virtual_disk_t *r5Disk = malloc(sizeof(virtual_disk_t));
  r5Disk->raidmode = CINQ;
  r5Disk->number_of_files = 0;
  r5Disk->ndisk = 0;
  r5Disk->storage = malloc(MAX_DISK*sizeof(FILE *));

  init_super_block_raid5(r5Disk);

  struct dirent *current = NULL;
  char acces[BUFSIZ];

  while((current = readdir(directory))!= NULL){

    if(!strncmp(current->d_name,NAME_DISK,strlen(NAME_DISK))){
      //printf("File : %s\n",current->d_name);
      sprintf(acces,"%s%s",DESIGNATION,current->d_name);
      r5Disk->storage[r5Disk->ndisk++] = fopen(acces,"wb");
    }
    else if(strcmp(current->d_name,"../") > 0){
      r5Disk->number_of_files ++;
    }
  }
  return *r5Disk;
  
}



void switch_off_raid(DIR *directory, virtual_disk_t *r5Disk){

  for(int i = 0; i < r5Disk->ndisk; ++i){
    if(fclose(r5Disk->storage[i])!=0){
      fprintf(stderr,"Error close disk %d",i);
    }
    printf("Disk n°%d close\n",i);
  }
  closedir(directory);
  exit(SUCCES_OFF);
}
/*=========================================================*/

int compute_nblock(int size){
  int nb_block;
  return nb_block = ((size%BLOCK_SIZE)==0)? size/BLOCK_SIZE : size/BLOCK_SIZE + 1;
}


int write_block(int pos, block_t block, FILE *dest){

  int block_wr;

  if(fseek(dest,pos*sizeof(block_t),SEEK_SET)){
    perror("Error write pos");
    return ERROR_SEEK_WRITE;
  }
  block_wr = fwrite(&block,sizeof(block_t),1,dest);

  return (block_wr * sizeof(block_t) == 1)? EXIT_SUCCESS : ERROR_WRITE;
}


int read_block(int pos, block_t *block, FILE * src){

  if(fseek(src, pos * sizeof(block_t), SEEK_SET)){
    perror("Error read pos");
    return ERROR_SEEK_READ;
  }

  return (fread(block, sizeof(block_t) ,1 , src) == 1)? EXIT_SUCCESS : ERROR_READ;
}


/*=========================================================*/
int main(void){
    
  DIR* direc = opendir("../RAID/");
  if(!direc){
    perror("Error directory");
    exit(-1);
  }

  //FILE *src = fopen("../RAID/test","rt");
  //fclose(src);





  virtual_disk_t r5 = init_disk_raid5(direc);
  //printf("Nbdisk : %d\nNbfile : %d\n",r5.ndisk,r5.number_of_files);
    //printf("Raid mode : %d\n",r5.raidmode);
  
  printf("Nbr file/disk <%d,%d>\n",r5.number_of_files,r5.ndisk);
    
  switch_off_raid(direc,&r5);


// Test des fonctions write_block && read_block

/*

  FILE *src = fopen("source","w+b");

  if(!src){
    perror("Error open file");
    exit(-2);
  }

  block_t block,block_read;
  for(int i=0; i < BLOCK_SIZE;block.data[i++]='a');
  printf("%d\n",write_block(0,block,src));

  printf("<%d,%d> %d\n", EXIT_SUCCESS, ERROR_READ, read_block(0,&block_read,src));

  write_block(2,block_read,src);
  for(int i=0; i < BLOCK_SIZE; printf("Data read %3c\n",block_read.data[i++]));

  fclose(src);

*/

  closedir(direc);
}