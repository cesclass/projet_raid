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



#endif