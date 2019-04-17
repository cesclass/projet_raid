#include "../headers/couche3.h"
#include "../headers/couche4.h"
#include "../headers/cmd.h"

#include <stdio.h>

#define RED_COL     "\x1B[31m"
#define GRN_COL     "\x1B[32m"
#define RST_COL     "\x1B[0m"

extern virtual_disk_t r5Disk;

void cmd_help() {
    printf("A propos du systeme RAID 5\n");
    printf("Vous pouvez interagir avec le systeme RAID 5 ");
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

    printf("quit : quitte les systeme RAID 5.\n");
}

void cmd_ls(char *arg) {
    char usage[BUFSIZ], print[BUFSIZ] = "";
    sprintf(usage, "Usage : ls [-l]\n");

    /*  Affichage en mode liste detaille */
    if (!strcmp(arg, "-l")) {
        uint taille, total = 0;
        char taille_str[16];
        
        for (int i = 0; i < INODE_TABLE_SIZE; i ++) {
            if (taille = strlen(r5Disk.inodes[i].filename)) {
                /*  Construction de l'affichage du ls -l */
                /*   - Nom du fichier */
                strcat(print, GRN_COL);
                strcat(print, r5Disk.inodes[i].filename);
                strcat(print, RST_COL);

                /*   - Alignement avec des espaces */
                for (int j = taille; j < 33; j ++) strcat(print, " ");
                
                /*   - Taille du fichier */
                sprintf(taille_str, "%d \tOctets\n", r5Disk.inodes[i].size);
                strcat(print, taille_str);

                /*  Calcul du poid total des fichier du systeme RAID */
                total += r5Disk.inodes[i].size;
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
            if (r5Disk.inodes[i].filename[0] != '\0') 
                printf("%s  ", r5Disk.inodes[i].filename);
        }
        printf("%s\n", RST_COL);
    }

    /*  Erreur d'argument */
    else {
        fprintf(stderr, "%s[ERR]%s %s Argument invalide\n",
                RED_COL, RST_COL, arg);
        fprintf(stderr, usage);
    }
}

/**
 * @TODO tester cette fonction avec read_file (couche 4)
 */
void cmd_cat(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : cat <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, usage);
    }

    /*  Recherche du fichier */
    else {
        file_t f;
        if (read_file(arg, &f))
            printf("%s\n", f.data);
        else
            fprintf(stderr, "%s[ERR]%s %s : Fichier introuvable\n",
                    RED_COL, RST_COL, arg);
    }
}

/**
 * @TODO tester cette fonction avec delete_file (couche 4)
 */
void cmd_rm(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : rm <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, usage);
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

/**
 * @TODO tester cette fonction avec write_file (couche 4)
 */
void cmd_create(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : create <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, usage);
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
            write_file(arg, &f);
            printf("%s : Fichier sauvegarde.\n", arg);
        }
    }

}

/**
 * @TODO tester cette fonction avec write_file et read_file (couche 4)
 */
void cmd_edit(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : edit <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, usage);
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

        /*  Si le fichier nexiste pas */
        else
            fprintf(stderr, "%s[ERR]%s %s : Fichier introuvable\n",
                    RED_COL, RST_COL, arg);
    }
}

void cmd_load(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : load <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, usage);
    }

    /*  Recherche du fichier */
    else {
        char reponse;

        /*  Demande de confirmation */
        /*do {
            printf("Si le fichier %s existe sur le RAID, ", arg);
            printf("il sera ecrase.\n ");
            printf("Confirmez-vous l'operation ? (o ou n)\n");

            if ((reponse = getchar()) != 'o' && reponse != 'O'
                    && reponse != 'n' && reponse != 'N')
                printf("%c : reponse invalide.\n", reponse);

        } while (reponse != 'o' && reponse != 'O' && reponse != 'n'
                && reponse != 'N');

        if (reponse == 'o' || reponse == 'O') {
            if (load_file_from_host(arg))
                printf("%s correctement copie sur le RAID.\n", arg);
            else
                fprintf(stderr, "%s[ERR]%s %s : Fichier introuvable\n",
                        RED_COL, RST_COL, arg);
        } else
            printf("load %s avorte\n", arg);*/
    }
}

void cmd_store(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : store <nom_de_fichier>\n");

    /*  Erreur d'argument */
    if (!strcmp(arg, "")) {
        fprintf(stderr, "%s[ERR]%s Argument vide\n",
                RED_COL, RST_COL);
        fprintf(stderr, usage);
    }

    /*  Recherche du fichier */
    else {
        
    }
}