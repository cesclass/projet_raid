#ifndef _COUCHE2_H
#define _COUCHE2_H

#include "../headers/raid_defines.h"

/**
 * @brief 
 * Calcule le nombre de stripe nécessaire pour un certains nombre de block,
 * en fonction du nombre de disque
 * 
 * @param nb_block Nombre de block
 * @param nb_disk Nombre de disque
 * @return int Nombre de stripe nécessaire
 */
int compute_nstripe(int nb_block, int nb_disk);

/**
 * @brief 
 * Calcule le block de parité des block composant block_tab.
 * Le block de parité est placé dans le 3ème paramètre
 * 
 * @param nb_block Nombre de block dans block_tab
 * @param block_tab Tableau de block
 * @param parity_block Block de stockage pour la paritée
 */
void compute_parity(int nb_block, block_t *block_tab, block_t *parity_block);

/**
 * @brief 
 * Calcule le numéro du disque sur lequel doit être stoqué 
 * le bloc de parité
 * 
 * @param num_bande Numéro du stripe (/!\ démmare à 1 !)
 * @param nb_disk Nombre de disque du système RAID
 * @return int Numéro du disque (/!\ démmare à 0 !)
 */
int parity_index(int num_bande, int nb_disk);

/**
 * @brief 
 * Écrit une bande à une position donné sur le système RAID 5
 * 
 * @param pos Position
 * @param bande Bande à écrire
 */
void write_stripe(int pos, const stripe_t *bande, int parity_index);

/**
 * @brief 
 * Ecrit sur le système RAID 5 le contenu du buffer
 * à partir de la position start_byte
 * 
 * @param n Taille du buffer en octet
 * @param buffer Buffer à écrire
 * @param start_byte Position de départ sur le RAID
 * @param nb_disk Nombre de disque du système RAID
 */
void write_chunk(int n, uchar *buffer, uchar start_byte, int nb_disk);

#endif