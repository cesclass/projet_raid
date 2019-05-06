/**
 * @file couche2.h
 * @author Dylan CARON (dcaron81.dc@gmail.com)
 * 
 * @brief
 * Interface de la couche 2 du système RAID.
 * Permet d'ecrire des tableaux de donnees au format uchar directement sur le systeme RAID.
 * 
 * @copyright Licence MIT
 */

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
 * Le block de parité est placé dans le 3ème paramètre.
 * 
 * @param nb_block      Nombre de block dans block_tab
 * @param block_tab     Tableau de block
 * @param parity_block  Block de stockage pour la paritée
 */
void compute_parity(int nb_block, block_t *block_tab, block_t *parity_block);

/**
 * @brief 
 * Calcule le numéro du disque sur lequel doit être stoqué
 *  le bloc de parité.
 * 
 * @param num_stripe    Numéro du stripe (/!\ démmare à 0 !)
 * 
 * @return int          Numéro du disque (/!\ démmare à 0 !)
 */
int parity_index(int num_stripe);

/**
 * @brief 
 * Ecrit une bande à une position donnee sur le systeme RAID.
 * 
 * @param pos           N° de la ligne ou ecrire la Stripe
 * @param src           Stripe à écrire
 */
void write_stripe(int pos, const stripe_t *src);

/**
 * @brief
 * Lit une bande à une position donnee sur le systeme RAID.
 * 
 * @param pos           N° de la ligne ou lire la Stripe
 * @param dest          Destination de la Stripe
 */
void read_stripe(int pos, stripe_t *dest);

/**
 * @brief 
 * Ecrit sur le système RAID le contenu du buffer
 *  à partir de la position pos.
 * 
 * @param buf_len       Taille du buffer en octet
 * @param buffer        Buffer à écrire
 * @param pos           Position de départ pour l'ecriture sur le RAID (en octet)
 * 
 * @return uint         Premier octet libre
 */
uint write_chunk(int buf_len, const uchar *buffer, uint pos);

/**
 * @brief
 * Lit sur le système RAID un nombre d'octets definis par buf_len
 *  et les stocke dans le buffer à partir de la position pos.
 * 
 * @param buf_len       Taille du buffer en octet (et nombre d'octets a lire)
 * @param buffer        Buffer de srockage
 * @param pos           Position de départ pour la lecture sur le RAID (en octet)
 */
void read_chunk(int buf_len, uchar *buffer, uint pos);

#endif