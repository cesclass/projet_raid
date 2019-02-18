#include "../headers/layer1.h"
/**
 * @brief 
 * 
 * @param filename 
 * @author dena
 * @return int 
 */


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



int compute_nblock(int size){

   return int nb_block = ((size%BLOCK_SIZE)==0)? size/BLOCK_SIZE : size/BLOCK_SIZE + 1;
}






int main(void){
    int nb_block = compute_nblock("test.txt");
    printf("Nb block %d",nb_block);
}