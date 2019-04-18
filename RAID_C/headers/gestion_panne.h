/**
 * @file gestion_panne.h
 * @author Guillaume B (guillaume.broise@univ-tlse3.fr)
 * 
 * @brief   
 * Fichier de declaration de la fonction de reparation de 
 * disks pour le systeme RAID 5
 * 
 * @copyright Licence MIT
 * 
 */
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