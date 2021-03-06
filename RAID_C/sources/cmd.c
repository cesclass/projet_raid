/**
 * @file cmd.c
 * @author Dylan CARON (dcaron81.dc@gmail.com)
 * 
 * @brief 
 * Définitions des fonctions relatives aux commandes
 *  utilisables avec le systeme RAID
 * 
 * @copyright Licence MIT
 */

#include "../headers/couche3.h"
#include "../headers/couche4.h"
#include "../headers/cmd.h"

#include <stdio.h>

#define RED_COL     "\x1B[31m"
#define GRN_COL     "\x1B[32m"
#define RST_COL     "\x1B[0m"

extern virtual_disk_t rDisk;

void cmd_help() {
    printf("A propos du systeme RAID\n");
    printf("Vous pouvez interagir avec le systeme RAID ");
    printf("grace aux commandes suivantes :\n");

    printf("help : Affiche l'aide suivante.\n");

    printf("ls [-l] : Affiche l'enssemble des fichiers ");
    printf("presents sur le systeme.\n");
    printf("\t-l permet l'affichage au format liste (avec les tailles).\n");

    printf("cat <nom_de_fichier> : affiche a l'ecran ");
    printf("le contenu d'un fichier.\n");

    printf("rm <nom_de_fichier> : supprime un fichier du systeme RAID.\n");

    printf("create <nom_de_fichier> : cree un nouveau fichier ");
    printf("sur le systeme RAID.\n");

    printf("edit <nom_de_fichier> : edite un fichier ");
    printf("pour modifier son contenu.\n");

    printf("load <nom_de_fichier> : copie le contenu d'un fichier ");
    printf("du systeme \"hote\" sur le RAID avec le meme nom\n");

    printf("store <nom_de_fichier> : copie le contenu d'un fichier ");
    printf("du RAID sur systeme \"hote\" avec le meme nom\n");

    printf("quit : quitte les systeme RAID.\n");
}

void cmd_ls(char *arg) {
    char usage[BUFSIZ], print[BUFSIZ] = "";
    sprintf(usage, "Usage : ls [-l]\n");

    /*  Affichage en mode liste detaille */
    if (!strcmp(arg, "-l")) {
        uint taille, total = 0;
        char taille_str[16];
        
        for (int i = 0; i < INODE_TABLE_SIZE; i ++) {
            if ((taille = strlen(rDisk.inodes[i].filename))) {
                /*  Construction de l'affichage du ls -l */
                /*   - Nom du fichier */
                strcat(print, GRN_COL);
                strcat(print, rDisk.inodes[i].filename);
                strcat(print, RST_COL);

                /*   - Alignement avec des espaces */
                for (int j = taille; j < 33; j ++) strcat(print, " ");
                
                /*   - Taille du fichier */
                sprintf(taille_str, "%d \tOctets\n", rDisk.inodes[i].size);
                strcat(print, taille_str);

                /*  Calcul du poid total des fichier du systeme RAID */
                total += rDisk.inodes[i].size;
            }
        }

        /*  Affichage du resultat de la commande ls -l */
        printf("Total : %d Octets\n", total);
        printf("%s", print);
    }

    /*  Affichage normal */
    else if (!strcmp(arg, "")) {
        printf("%s", GRN_COL);
        for (int i = 0; i < INODE_TABLE_SIZE; i ++) {
            if (rDisk.inodes[i].filename[0] != '\0') 
                printf("%s  ", rDisk.inodes[i].filename);
        }
        printf("%s\n", RST_COL);
    }

    /*  Erreur d'argument */
    else {
        fprintf(stderr, "%s[ERR]%s %s Argument invalide\n",
                RED_COL, RST_COL, arg);
        fprintf(stderr, "%s", usage);
    }
}

void cmd_cat(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : cat <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, "%s", usage);
    }

    /*  Recherche du fichier */
    else {
        file_t f;
        if (read_file(arg, &f)) {
            for(int i = 0; i < f.size; putc(f.data[i++] , stdout));
            printf("\n");
        } else
            fprintf(stderr, "%s[ERR]%s %s : Fichier introuvable\n",
                    RED_COL, RST_COL, arg);
    }
}

void cmd_rm(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : rm <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, "%s", usage);
    }

    /*  Suppression du fichier */
    else {
        if (delete_file(arg)) {
            printf("%s : Fichier supprime\n", arg);
            write_inode_table();
        } else
            fprintf(stderr, "%s[ERR]%s %s : Fichier introuvable\n",
                    RED_COL, RST_COL, arg);
    }
}

void cmd_create(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : create <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, "%s", usage);
        return;
    }

    if (strlen(arg) > FILENAME_MAX_SIZE - 1) {
        fprintf(stderr, "%s[ERR]%s %s : ",
                RED_COL, RST_COL, arg);
        fprintf(stderr, "Nom de fichier trop long. (Max 31 caracteres)\n");
        return;
    }

    if (arg[0] == ' ') {
        fprintf(stderr, "%s[ERR]%s %s : ",
                RED_COL, RST_COL, arg);
        fprintf(stderr, "Nom invalide.\n");
        fprintf(stderr, "le nom du fichier ne peut commencer par un espace.\n");
        return;
    }

    /*  Recherche du fichier */
    else {
        /*  Si le fichier existe deja */
        if (search_inode(arg) != NO_INODE_MATCH)
            fprintf(stderr, "%s[ERR]%s %s : Le fichier existe deja.\n",
                    RED_COL, RST_COL, arg);
        
        /*  Creation du nouveau fichier */
        else {
            file_t f;
            printf("Veuillez saisir le contenu du nouveau fichier %s.\n", arg);
            printf("Pour terminer votre saisie, tapez '$' puis ENTREE.\n");
            
            /*  Saisie du nouveau fichier */
            for (f.size = 0; (f.data[f.size] = getchar()) != '$'; ++ f.size);
            getchar();
            f.data[f.size ++] = '\0';
            
            /*  Enregistrement du nouveau fichier */
            if (write_file(arg, &f)) {
                printf("%s : Fichier sauvegarde.\n", arg);
            } else {
                fprintf(stderr, "%s[ERR]%s %s : Le fichier n'a pas pu etre ecrit.\n",
                        RED_COL, RST_COL, arg);
            }
        }
    }
}

void cmd_edit(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : edit <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, "%s", usage);
    }

    /*  Edition du fichier */
    else {
        file_t f;

        /*  Si le fichier existe */
        if (read_file(arg, &f)) {

            /*  Affichage de l'ancien fichier */
            printf("%s (%d Octets)\n", arg, f.size);
            printf("%s\n", f.data);

            printf("\nVeuillez saisir le contenu du fichier %s.\n", arg);
            printf("Pour terminer votre saisie, tapez '$' puis ENTREE.\n");
            
            /*  Saisie du nouveau fichier */
            for (f.size = 0; (f.data[f.size] = getchar()) != '$'; ++ f.size);
            getchar();
            f.data[f.size ++] = '\0';
            
            /*  Enregistrement du nouveau fichier */
            write_file(arg, &f);
        } 

        /*  Si le fichier n'existe pas */
        else
            fprintf(stderr, "%s[ERR]%s %s : Fichier introuvable\n",
                    RED_COL, RST_COL, arg);
    }
}

void rename_file(char *src, char * dest) {
    int i = 0, j = 0;
    while(src[i] != '\0') {
        if(src[i] == '/') {
            j = 0;
            i++;
        } else {
            dest[j++] = src[i++];
        }
    }
    dest[j] = '\0';
}

void cmd_load(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : load <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, "%s", usage);
    }

    char filename[FILENAME_MAX_SIZE];
    rename_file(arg, filename);
    

    if (strlen(filename) > FILENAME_MAX_SIZE - 1) {
        fprintf(stderr, "%s[ERR]%s %s : ",
                RED_COL, RST_COL, arg);
        fprintf(stderr, "Nom de fichier trop long. (Max 31 caracteres)\n");
        return;
    }

    if (arg[0] == ' ') {
        fprintf(stderr, "%s[ERR]%s %s : ",
                RED_COL, RST_COL, arg);
        fprintf(stderr, "Nom invalide.\n");
        fprintf(stderr, "le nom du fichier ne peut commencer par un espace.\n");
        return;
    }

    /*  Recherche du fichier */
    else {
        char reponse;

        /*  Demande de confirmation */
        do {
            printf("Si le fichier %s existe sur le RAID, ", arg);
            printf("il sera ecrase.\n");
            printf("Confirmez-vous l'operation ? (o ou n) ");

            if ((reponse = getchar()) != 'o' && reponse != 'O'
                    && reponse != 'n' && reponse != 'N')
                printf("%c : reponse invalide.\n", reponse);
            getchar();

        } while (reponse != 'o' && reponse != 'O' && reponse != 'n'
                && reponse != 'N');

        if (reponse == 'o' || reponse == 'O') {

            if (load_file_from_host(arg, filename))
                printf("%s correctement copie sur le RAID.\n", arg);
            else
                fprintf(stderr, "%s[ERR]%s %s : Fichier introuvable\n",
                        RED_COL, RST_COL, arg);
        } else
            printf("load %s avorte\n", arg);
    }
}

void cmd_store(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : store <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, "%s", usage);
    }

    /*  Recherche du fichier */
    else {
        char reponse;

        /*  Demande de confirmation */
        do {
            printf("Si le fichier %s existe sur le systeme hote, ", arg);
            printf("il sera ecrase.\n");
            printf("Confirmez-vous l'operation ? (o ou n) ");

            if ((reponse = getchar()) != 'o' && reponse != 'O'
                    && reponse != 'n' && reponse != 'N')
                printf("%c : reponse invalide.\n", reponse);
            getchar();

        } while (reponse != 'o' && reponse != 'O' && reponse != 'n'
                && reponse != 'N');

        if (reponse == 'o' || reponse == 'O') {
            if (store_file_to_host(arg))
                printf("%s correctement copie sur l'hote.\n", arg);
            else
                fprintf(stderr, "%s[ERR]%s %s : Fichier introuvable\n",
                        RED_COL, RST_COL, arg);
        } else
            printf("load %s avorte\n", arg);
    }
}