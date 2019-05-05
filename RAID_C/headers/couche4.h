/**
 * @file couche4.h
 * @author Cyril ESCLASSAN (cyril.esclassan@univ-tlse3.fr)
 * 
 * @brief 
 * Fichier de declaration des fonctions de 
 *  la couche 4 pour le projet RAID.
 * 
 * @copyright Licence MIT
 * 
 */

#ifndef __COUCHE4_H__
#define __COUCHE4_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/raid_defines.h"
#include "../headers/couche2.h"
#include "../headers/couche3.h"

#define NO_INODE_MATCH 11

/**
 * @brief 
 * Cherche l'inode representant le fichier ayant le nom "filename" et
 *  retourne l'indice de cette inode dans la table.
 * 
 * @param filename      Nom du fichier recherche
 * @return uint         Indice de l'inode
 *                  OU  NO_INODE_MATCH en cas d'erreur
 */
uint search_inode(char * filename);

/**
 * @brief 
 * Ecrit le contenue de "file" sur les disques virtuels et met a jour
 *  le super bloc et la table d'inode.
 * 
 * @param filename      Nom du fichier a ecrire
 * @param file          Structure contenant les donnees du fichier
 * @return uint         1 : OK / 0 : KO
 */
uint write_file(char * filename, file_t * file);

/**
 * @brief 
 * Lit le fichier nomme "filename" sur les disques virtuels et rempli 
 *  la structure "file".
 * 
 * @param filename      Nom du fichier a lire
 * @param file          Structure accueillant les donnees du fichier
 * @return uint         1 : OK / 0 : KO
 */
uint read_file(char * filename, file_t * file);

/**
 * @brief 
 * Supprime le fichier nomme "filename" de la table d'inodes.
 * 
 * @param filename      Fichier a supprimer
 * @return uint         1 : OK / 0 : KO
 */
uint delete_file(char * filename);

/**
 * @brief 
 * Lit un fichier sur la machine et ecrit son contenu sur les disques virtuels.
 * 
 * @param filename      Nom (chemin) du fichier a lire
 * @return uint         1 : OK / 0 : KO
 */
uint load_file_from_host(char * filename);

/**
 * @brief 
 * lit un fichier sur les disques virtuels et ecrit son contenu sur la machine.
 * 
 * @param filename      Nom du fichier a lire
 * @return uint         1 : OK / 0 : KO
 */
uint store_file_to_host(char * filename);

#endif