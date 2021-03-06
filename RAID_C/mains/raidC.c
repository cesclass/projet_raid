/**
 * @file raid5.c
 * @author Dylan CARON (dcaron81.dc@gmail.com)
 * 
 * @brief 
 * Système d'exploitation du système RAID 5.
 * Permet de lancer un enssemble de commandes,
 *  (ls [-l]; cat; rm; create; edit; load; store)
 *  afin de lister, lire, ecrire, editer, stocker, recuperer 
 *  vers et depuis le systeme rAID 5.
 * La commande quit permet de quiter.
 * 
 * @copyright Licence MIT
 */

#include "../headers/couche1.h"
#include "../headers/couche2.h"
#include "../headers/cmd.h"

#include <stdio.h>
#include <stdlib.h>

#define CMD_LEN         10
#define ARG_LEN         256
#define PNK_COL         "\x1B[35m"
#define RST_COL         "\x1B[0m"

#define ERR_ARGS        101
#define ERR_RAID_TYPE   102

virtual_disk_t rDisk;

void show_raid(void) {
    /*  Efface tout le terminal */
    printf("\033[H\033[J");
    fflush(stdout);

    printf("+------------------+\n");
    printf("|  RAID - Storage  |\n");
    printf("+------------------+\n");

    printf("\nBienvenue sur le systeme de stockage RAID.\n");
    printf("Tapez \"help\" pour plus d'information.\n");
}

void read_cmd(char *cmd, char *arg) {
    int i, j;
    char read[CMD_LEN + ARG_LEN + 2];
    for (i = 0; (read[i] = getchar()) != '\n'; i++);
    for (i = 0; read[i] != ' ' && read[i] != '\n'; cmd[i] = read[i], i ++);
    cmd[i] = '\0';
    if (read[i] != '\n') {
        i++;
        for (j = 0; read[i] != '\n'; arg[j++] = read[i++]);
        arg[j] = '\0';
    }
}

int main(int argc, char *argv[]) {
    char usage[BUFSIZ], cmd[CMD_LEN], arg[CMD_LEN];
    sprintf(usage, "Usage : %s type_raid repertoire_disques\n", argv[0]);

    /*  Gestion des erreurs d'arguments */
    if (argc != 3) {
        fprintf(stderr, "%s", usage);
        exit(ERR_ARGS);
    }

    /*  Initialisation du systeme RAID */
    if (!init_disk_raid(atoi(argv[1]), argv[2])) {
        fprintf(stderr, "%s", "raid_type inconnu");
        fprintf(stderr, "%s", usage);
        exit(ERR_RAID_TYPE);
    }

    /*  Affichage du systeme RAID */
    show_raid();

    do {
        printf("%sRAID  >> %s", PNK_COL, RST_COL);
        cmd[0] = '\0'; arg[0] = '\0';
        read_cmd(cmd, arg);

        /*  Gestion des commandes */
        if      (!strcmp(cmd, "help"))      cmd_help();
        else if (!strcmp(cmd, "ls"))        cmd_ls(arg);
        else if (!strcmp(cmd, "cat"))       cmd_cat(arg);
        else if (!strcmp(cmd, "rm"))        cmd_rm(arg);
        else if (!strcmp(cmd, "create"))    cmd_create(arg);
        else if (!strcmp(cmd, "edit"))      cmd_edit(arg);
        else if (!strcmp(cmd, "load"))      cmd_load(arg);
        else if (!strcmp(cmd, "store"))     cmd_store(arg);
        else if (!strcmp(cmd, "quit")) {
            printf("Sortie du systeme RAID.\n");
            switch_off_raid();
        } else {
            printf("Commande non reconnue.\n");
            printf("Tapez \"help\" pour plus d'information.\n");
        }

    } while (strcmp(cmd, "quit"));
    
    return 0;
}