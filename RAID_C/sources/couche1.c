/**
 * @file couche1.c
 * @author Guillaume B (guillaume.broise@univ-tlse3.fr)
 * 
 * @brief   
 * Fichier de definition des fonctions de la couche 1
 * pour le systeme RAID
 * 
 * @copyright Licence MIT
 * 
 */

#include "../headers/couche1.h"
#include "../headers/couche3.h"

extern virtual_disk_t rDisk;


uint init_disk_raid(int raid_type, char *directory){
  
  /* initialisation des attributs de rDisk */
  switch (raid_type) {
    case 0 :
      rDisk.raidmode = ZERO;
      break;
    case 1 :
      rDisk.raidmode = UN;
      break;
    case 5 :
      rDisk.raidmode = CINQ;
      break;
    default :
      /* Aucun systeme de RAID connu */
      return 0;
  }

  rDisk.number_of_files = 0;
  rDisk.ndisk = raid_type == 5 ? MAX_DISK_R5 : MAX_DISK_OTHER;
  rDisk.storage = malloc(rDisk.ndisk*sizeof(FILE *));

  char acces[BUFSIZ];
  
  /* ouverture des disks du systeme RAID */
  for(int i = 0; i < rDisk.ndisk ; i++){
      sprintf(acces, "%s%s%d%c%d", directory, NAME_DISK, i, 'r', raid_type);
      if(!(rDisk.storage[i] = fopen(acces, "rb+"))){
        perror(acces);
      }
  }
  
  /* Init Super_Block & Inode_Table RAID  */
  if( fgetc(rDisk.storage[0]) == EOF ){
    /* Table d'inode & Inode */
    for(int i = 0; i++ < INODE_TABLE_SIZE; init_inode("\0",0, 0));
    write_inode_table();

    /* Super Block */
    rDisk.super_block.raid_type = rDisk.raidmode;
    set_first_free_byte( write_inode_table());
    rDisk.super_block.nb_blocks_used = rDisk.super_block.first_free_byte / BLOCK_SIZE;
    write_super_block();

  }
  else {
    read_inode_table();
    read_super_block();

    /* Compte le nombre fichier */
    for(int i = 0; i < INODE_TABLE_SIZE; i++){
      if( rDisk.inodes[i].filename[0] != '\0'){
        rDisk.number_of_files ++;
      }
    }
  }

  return 1;
}

void switch_off_raid(){

  /* fermeture des disk du systeme RAID */
  for(int i = 0; i < rDisk.ndisk; ++i){
    if(fclose(rDisk.storage[i]) != 0){
      fprintf(stderr, "Error close disk %d", i);
    }
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
  for(int i = 0; i < BLOCK_SIZE; repair->data[i++] = 0);

  for(int i = 0 ; i < rDisk.ndisk; i++){
    if(i != num_disk){
      read_block(pos,&read,rDisk.storage[i]);
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
    /* converti le caractere en entier pour l'affichage */
    value = (int)block.data[i];
    printf("%2x ", value);
  }
  printf(" | ");
}
