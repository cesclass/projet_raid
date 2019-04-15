#include "../headers/couche3.h"

#include <stdio.h>

#define RED_COL     "\x1B[31m"
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
    char usage[BUFSIZ];
    sprintf(usage, "Usage : ls [-l]\n");

    /*  Affichage en mode liste detaille */
    if (!strcmp(arg, "-l")) {

    }

    /*  Affichage normal */
    else if (!strcmp(arg, "")) {
        
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