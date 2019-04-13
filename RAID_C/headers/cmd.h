#ifndef _CMD_H
#define _CMD_H

/**
 * @brief 
 * Affiche le manuel d'utilisation du systeme RAID 5 
 */
void cmd_help();

void cmd_ls(char *arg);

void cmd_cat(char *arg);

void cmd_rm(char *arg);

void cmd_create(char *arg);

void cmd_edit(char *arg);

void cmd_load(char *arg);

void cmd_store(char *arg);

#endif