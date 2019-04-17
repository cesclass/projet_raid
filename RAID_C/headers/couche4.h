/**
 * @file couche4.h
 * @author Cyril ESCLASSAN (cyril.esclassan@univ-tlse3.fr)
 * 
 * @brief 
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

uint search_inode(char * filename);

uint write_file(char * filename, file_t * file);

uint read_file(char * filename, file_t * file);

uint delete_file(char * filename);

uint load_file_from_host(char * filename);

uint store_file_to_host(char * filename);

#endif