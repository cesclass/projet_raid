/**
 * @file couche3.h
 * @author Cyril E (cyril.esclassan@univ-tlse3.fr)
 * 
 * @brief   
 * Fichier de declaration des fonctions de 
 *  la couche 3 pour le projet RAID.
 * 
 * @copyright Licence MIT
 */

#ifndef __COUCHE3_H__
#define __COUCHE3_H__

#include <stdlib.h>

#include "../headers/raid_defines.h"
#include "../headers/couche2.h"
#include "../headers/couche1.h"

// Taille(s)
#define INODE_TABLE_TOTAL_SIZE  INODE_TABLE_SIZE*INODE_SIZE*BLOCK_SIZE
#define INODE_BYTE_SIZE         INODE_SIZE*BLOCK_SIZE
#define REAL_SUPER_BLOCK_SIZE   12

// Erreur(s)
#define ERR_UNUSED_INODE        11

/* 
 * Gestion des inodes
 * ***************************************************************************/

/**
 * @brief 
 * Charge la table d'inodes depuis les disques virtuels.
 */
void read_inode_table(void);

/**
 * @brief 
 * Ecrit la table d'inodes sur les disques virtuels.
 * 
 * @return uint             Premier octet apres l'ecriture
 */
uint write_inode_table(void);

/**
 * @brief 
 * Supprime (reinitialise) une inode dans la table d'inodes.
 * 
 * @param indice            Indice de l'inode a supprimer
 */
void delete_inode(int indice);

/**
 * @brief
 * Cherche une inode vide et retourne son indice.
 * Retourne un code d'erreur si aucune inode n'est disponnible.
 * 
 * @return uint             Indice de la premiere inode vide
 *                      OU  ERR_UNUSED_INODE (aucune inode vide)
 */
uint get_unused_inode(void);

/**
 * @brief 
 * Initialise une nouvelle inode avec les valeurs passes en parametre.
 * La nouvelle inode est selectionnee avec get_unused_inode().
 * 
 * @param filename          Nom du fichier (31 caractere(s) max)
 * @param size              Taille du fichier en octets
 * @param first_byte        Indice du premier octet sur les disques virtuels
 * @return uint             Indice de l'inode initialise
 *                      OU  ERR_UNUSED_INODE (aucune inode vide)
 */
uint init_inode(char * filename, uint size, uint first_byte);

/*
 * Gestion du super block
 * ***************************************************************************/

/**
 * @brief 
 * Charge le super bloc depuis les disques virtuels.
 */
void read_super_block(void);

/**
 * @brief 
 * Ecrit le super block sur les disques virtuels. 
 * 
 * @return uint             Premier octet apres l'ecriture
 */
uint write_super_block(void);

/**
 * @brief
 * Met a jour la valeur du premier octet libre sur le systeme RAID.
 * 
 * @param first_free_byte   Premier octet libre sur les disques
 */
void set_first_free_byte(uint first_free_byte);

#endif