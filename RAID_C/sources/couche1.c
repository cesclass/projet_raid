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


/**
 * @brief calcule le nombre de block necessaire pour un fichier
 * 
 * @param filename 
 * @return int 
 */
int compute_nblock(char filename[]){

  struct dirent *current;
  struct stat info_file;
  int nb_block = 0;
  DIR *directory = opendir("./"); /*repertoire ouvert avant ??*/

  /* parcours l'ensemble des fichiers de directory jusqu'a filename */
  /* si filename non trouve exit du programme */
  do {
    current = readdir(directory);
    if(current == NULL){
      fprintf(stderr,"FILE not found\n");
      exit(ERROR_FILE);
    }
  } while(strcmp(current->d_name,filename));


  if(stat(current->d_name,&info_file) == 0){
      off_t size = info_file.st_size;

      /* si size%BLOCK_SIZE == 0 nb_block = size/BLOCK_SIZE */
      /* sinon nb_block = size/BLOCK_SIZE */
      nb_block = ((size%BLOCK_SIZE)==0)? size/BLOCK_SIZE : size/BLOCK_SIZE + 1;
  }
  closedir(directory);

  return nb_block;
}





int main(void){
    int nb_block = compute_nblock("test.txt");
    printf("Nb block %d",nb_block);
}