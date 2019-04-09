#ifndef _COUCHE2_H
#define _COUCHE2_H

#include "../headers/raid_defines.h"

/**
 * @brief 
 * Calcule le nombre de stripe nécessaire pour stoquer un certains nombre de block.
 * 
 * @param nb_block      Nombre de block
 * 
 * @return int          Nombre de stripe nécessaire
 */
int compute_nstripe(int nb_block);

/**
 * @brief 
 * Calcule le block de parité des block composant block_tab.
 * Le block de parité est placé dans le 3ème paramètre
 * 
 * @param nb_block      Nombre de block dans block_tab
 * @param block_tab     Tableau de block
 * @param parity_block  Block de stockage pour la paritée
 */
void compute_parity(int nb_block, block_t *block_tab, block_t *parity_block);

/**
 * @brief 
 * Calcule le numéro du disque sur lequel doit être stoqué 
 * le bloc de parité
 * 
 * @param num_stripe    Numéro du stripe (/!\ démmare à 0 !)
 * 
 * @return int          Numéro du disque (/!\ démmare à 0 !)
 */
int parity_index(int num_stripe);

/**
 * @brief 
 * Écrit une bande à une position donné sur le système RAID 5
 * 
 * @param pos           N° de la ligne ou ecrire la bande
 * @param stripe        Bande à écrire
 */
void write_stripe(int pos, const stripe_t *stripe, int parity_index);

/**
 * @brief 
 * Ecrit sur le système RAID 5 le contenu du buffer
 * à partir de la position start_byte
 * 
 * @param buf_len       Taille du buffer en octet
 * @param buffer        Buffer à écrire
 * @param start_byte    Position de départ sur le RAID
 * @param nb_disk       Nombre de disque du système RAID
 */
void write_chunk(int buf_len, uchar *buffer, uchar start_byte, int nb_disk);

#endif