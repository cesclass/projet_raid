/**
 * @file cmd.h
 * @author Dylan CARON (dcaron81.dc@gmail.com)
 * 
 * @brief
 * Interface des differentes commandes disponibles
 *  sur le systeme RAID.
 * Celles-ci sont destinees a etre utilisee
 *  par les systemes d'exploitation des differents systemes RAID
 * 
 * @copyright Licence MIT
 */

#ifndef _CMD_H
#define _CMD_H

/**
 * @brief 
 * Affiche le manuel d'utilisation du systeme RAID 5 
 */
void cmd_help();

/**
 * @brief 
 * Affiche sur la sortie standard le nom des fichiers
 *  presents sur les disques du systeme RAID.
 * l'argument "-l" permet un affichage sous forme de liste detaillee
 *  en affichant en plus les poids correspondant.
 * 
 * @param arg           Argument de la commande (uniquement "-l")
 */
void cmd_ls(char *arg);

/**
 * @brief 
 * Affiche sur la sortie standard le contenu d'un fichier
 *  du systeme RAID passe en parametre.
 * 
 * @param arg           Argument de la commande (nom du fichier)
 */
void cmd_cat(char *arg);

/**
 * @brief 
 * Supprime un fichier dont le nom est passe en parametre
 *  du systeme RAID.
 * 
 * @param arg           Argument de la commande (nom du fichier)
 */
void cmd_rm(char *arg);

/**
 * @brief 
 * Cree un fichier vide dont le nom est passe en parametre
 *  sur le systeme RAID.
 * 
 * @param arg           Argument de la commande (nom du fichier)
 */
void cmd_create(char *arg);

/**
 * @brief 
 * Edite un fichier du systeme RAID,
 *  dont le nom est passe en parametre,
 *  pour modifier son contenu.
 * 
 * @param arg           Argument de la commande (nom du fichier)
 */
void cmd_edit(char *arg);

/**
 * @brief 
 * Copie un fichier du systeme "hote" vers le systeme RAID
 *  avec le meme nom.
 * 
 * @param arg           Argument de la commande (nom du fichier)
 */
void cmd_load(char *arg);

/**
 * @brief 
 * Copie un fichier du systeme RAID vers le systeme "hote"
 *  avec le meme nom.
 * 
 * @param arg           Argument de la commande (nom du fichier)
 */
void cmd_store(char *arg);

#endif