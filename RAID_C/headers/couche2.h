/**
 * @file couche2.h
 * @author Dylan CARON (dcaron81.dc@gmail.com)
 * 
 * @brief
 * Interface de la couche 2 du système RAID5
 * Permet d'ecrire des tableaux de donnees au format uchar directement sur le systeme RAID5
 * 
 * @copyright Licence MIT
 */

#ifndef _COUCHE2_H
#define _COUCHE2_H

#include "../headers/raid_defines.h"

/**
 * @brief 
 * Ecrit sur le système RAID 5 le contenu du buffer
 * à partir de la position pos
 * 
 * @param buf_len       Taille du buffer en octet
 * @param buffer        Buffer à écrire
 * @param pos           Position de départ sur le RAID
 */
void write_chunk(int buf_len, const uchar *buffer, uchar pos);

/**
 * @brief
 * Lit sur le système RAID 5 un nombre d'octets definis par buf_len
 * et les stocke dans le buffer à partir de la position pos
 * 
 * @param buf_len       Taille du buffer en octet (et nombre d'octets a lire)
 * @param buffer        Buffer de srockage
 * @param pos           Position de départ sur le RAID
 */
void read_chunk(int buf_len, uchar *buffer, uchar pos);

#endif