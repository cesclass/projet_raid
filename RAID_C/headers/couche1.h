/**
 * @file couche1.h
 * @author Guillaume B (guillaume.broise@univ-tlse3.fr)
 * 
 * @brief   
 * Fichier de declaration des fonctions de la couche 1
 * pour le systeme RAID 5
 * 
 * @copyright Licence MIT
 * 
 */

#ifndef __COUCHE1_H_
#define __COUCHE1_H_

#include <stdlib.h>
#include <string.h>

#include "raid_defines.h"
#include "couche3.h"

/* Erreur */
#define ERROR_FILE 1
#define ERROR_FILE_CLOSE 2
#define ERROR_WRITE 3
#define ERROR_READ 4

#define SUCCES_OFF 10

#define MAX_DISK 4
#define NAME_DISK "vDisk"   


/**
 * @brief
 * 
 * Initialise les champs de la variables globales r5Disk
 * Elle ouvre tous les disk virtuels present dans le repertoire
 * 
 * @param directory : nom du repertoire ou se trouve le systeme RAID
 * 
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
 * @return int : nombre de block necessaire
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
void block_repair(int pos, int numDisk, block_t *repair);

/**
 * @brief 
 * 
 * Affiche le contenu de block sous la forme hexadecimal
 * 
 * @param block : block a afficher en hexa
 * 
 */
void dump_block_hexa(block_t block);

#endif