#include <stdio.h>

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
    
}

void cmd_cat(char *arg) {

}

void cmd_rm(char *arg) {

}

void cmd_create(char *arg) {

}

void cmd_edit(char *arg) {

}

void cmd_load(char *arg) {

}

void cmd_store(char *arg) {

}