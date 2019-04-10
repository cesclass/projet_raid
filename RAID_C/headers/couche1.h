#ifndef __COUCHE1_H_
#define __COUCHE1_H_

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#include "raid_defines.h"

#define ERROR_FILE 1
#define ERROR_FILE_CLOSE 2
#define ERROR_SEEK_WRITE 3
#define ERROR_WRITE 4
#define ERROR_SEEK_READ 5
#define ERROR_READ 6

#define SUCCES_OFF 10

#define MAX_DISK 4
#define NAME_DISK "vDisk"   


/**
 * @brief
 * 
 * Initialise les champs de la variables globales r5Disk
 * Elle ouvre tous les disk virtuels present dans le repertoire
 * designe par la directory
 * 
 * @param directory 
 */
void init_disk_raid5(char *directory);

/**
 * @brief 
 * 
 * Ferme tous les disks ouverts du systeme RAID
 * 
 */
void switch_off_raid();


/**
 * @brief
 * 
 * Calcule le nombre de block necessaire pour ecrire size
 * 
 * @param size : taille a decouper en block
 * 
 * @return int 
 */
int compute_nblock(int size);

/**
 * @brief
 * 
 * Ecris sur le fichier dest block a la position pos;
 * 
 * @param pos : position du block a ecrire
 * @param block : block a ecrire
 * @param dest : fichier sur lequel doit etre ecrit block
 * 
 * @return 0 en cas de succes, 3 en cas d'erreur de positionnement sur le fichier
 *                             4 en cas d'erreur d'ecriture
 */
int write_block(int pos, block_t block, FILE *dest);

/**
 * @brief
 * 
 * Lis sur le fichier src le block a la position pos
 * 
 * @param pos : position du block a lire
 * @param block : block a lire
 * @param src : fichier sur lequel doit etre lu le block
 * 
 * @return 0 en cas de succes, 5 en cas d'erreur de positionnement sur le fichier
 *                             6 en cas d'erreur de lecture
 */
int read_block(int pos, block_t *block, FILE *src);

/**
 * @brief 
 * 
 * Repare un block errone en faisant le XOR des autres blocks intactes 
 * a la meme position
 *  
 * @param pos : position du block a reparer
 * @param numDisk : numero du disk ou se situe le block
 * 
 */
void block_repair(int pos, int numDisk);

/**
 * @brief 
 * 
 * Affiche le contenu de block sous la forme hexadecimal
 * 
 * @param block : block a afficher en hexa
 * 
 */
void hexa_display(block_t block);

#endif