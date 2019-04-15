#include "../headers/couche3.h"

#include <stdio.h>

#define RED_COL     "\x1B[31m"
#define GRN_COL     "\x1B[32m"
#define RST_COL     "\x1B[0m"

extern virtual_disk_t r5Disk;

void cmd_help() {
    printf("A propos du systeme RAID 5\n");
    printf("Vous pouvez interagir avec le systeme RAID 5 ");
    printf("grace aux commandes suivantes :\n");

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

    //read_inode_table();

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
                sprintf(taille_str, "%d Octets\n", r5Disk.inodes[i].size);
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

    }
}

void cmd_rm(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : rm <nom_de_fichier>\n");

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
        
    }

}

void cmd_edit(char *arg) {
    char usage[BUFSIZ];
    sprintf(usage, "Usage : edit <nom_de_fichier>\n");

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