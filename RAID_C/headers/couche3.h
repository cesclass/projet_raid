/**
 * @file couche3.h
 * @author Cyril E (cyril.esclassan@univ-tlse3.fr)
 * 
 * @brief   Fichier de declaration des fonctions de 
 *          la couche 3 pour le projet RAID
 * 
 * @copyright Licence MIT
 */

#ifndef __COUCHE3_H__
#define __COUCHE3_H__

#include <stdio.h>
#include <stdlib.h>
#include "../headers/raid_defines.h"

// Liste des fonctions
void read_inode_table(void);
void write_inode_table(void);
void delete_inode(void);
void get_unused_inode(void);
void init_inode(void);
void read_super_block(void);
void write_super_block(void);
void set_first_free_byte(void);

#endif