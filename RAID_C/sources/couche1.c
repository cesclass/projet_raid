#include "../headers/couche1.h"


virtual_disk_t init_disk_raid5(DIR *directory){
  
  virtual_disk_t *r5Disk;
  r5Disk->number_of_files = 0;

  struct dirent *current;
  struct stat info_file;

  opendir(directory);

  while(current = readdir(directory)!= NULL){
    if(stat(current->d_name,&info_file) == 0){
      if(S_ISREG(info_file.st_mode)){
       r5Disk->number_of_files ++;
      }
    }    
  }
}


void switch_off_raid(DIR *directory, virtual_disk_t *r5Disk){

  for(int i = 0; i < r5Disk->ndisk; ++i){
    if(fclose(r5Disk->storage[i])!=0){
      fprintf(stderr,"Error close disk %d",i);
    }
  }
  closedir(directory);
  exit(SUCCES_OFF);
}






int compute_nblock(int size){
  int nb_block;
  return nb_block = ((size%BLOCK_SIZE)==0)? size/BLOCK_SIZE : size/BLOCK_SIZE + 1;
}






int main(void){
    int nb_block = compute_nblock("test.txt");
    printf("Nb block %d",nb_block);
}