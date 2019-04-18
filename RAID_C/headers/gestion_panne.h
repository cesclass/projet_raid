#ifndef GESTION_PANNE_H_
#define GESTION_PANNE_H_

#include "couche1.h"
#include "couche2.h"
#include "raid_defines.h"

/**
 * @brief 
 * 
 * Repare la totalite du disk a l'aide de la fonction block_repair
 * de la couche 1
 * 
 * @param numdisk : numero du disk a reparer
 * 
 */
void repair_disk(int numdisk);

#endif