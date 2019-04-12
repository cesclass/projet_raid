/**
 * @file couche3.h
 * @author Cyril E (cyril.esclassan@univ-tlse3.fr)
 * 
 * @brief   
 * Fichier de declaration des fonctions de 
 *  la couche 3 pour le projet RAID
 * 
 * @copyright Licence MIT
 */

#ifndef __COUCHE3_H__
#define __COUCHE3_H__

#include <stdlib.h>

#include "../headers/raid_defines.h"
#include "../headers/couche2.h"
#include "../headers/couche1.h"

#define INODE_TABLE_TOTAL_SIZE  INODE_TABLE_SIZE*INODE_SIZE*BLOCK_SIZE
#define INODE_BYTE_SIZE         INODE_SIZE*BLOCK_SIZE

#define ERR_UNUSED_INODE        11

// Liste des fonctions

/**
 * @brief 
 * 
 */
void read_inode_table(void);

/**
 * @brief 
 * 
 */
void write_inode_table(void);

/**
 * @brief 
 * 
 * @param indice 
 */
void delete_inode(int indice);

/**
 * @brief Get the unused inode object
 * 
 * @return uint 
 */
uint get_unused_inode(void);

/**
 * @brief 
 * 
 * @param filename 
 * @param size 
 * @param first_byte 
 * @return uint 
 */
uint init_inode(char * filename, uint size, uint first_byte);


void read_super_block(void);
void write_super_block(void);
void set_first_free_byte(void);

#endif