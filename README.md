# projet_raid
Projet RAID - L2 Informatique - TOULOUSE III Paul Sabatier 

## Comment exécuter le système RAID ?

### Initialisation de l'environnement :

En C ou en Java, le système RAID 5 utilise un répertoire dans lequel il stocke les disques virtuels qu'il utilise pour le stockage.
 - `vDisk0r0`, `vDisk1r0` correspondent aux disques virtuels utilisés par le système RAID 0 en C
 - `vDisk0r1`, `vDisk1r1` aux disques virtuels utilisés par le RAID 1 en C
 - `vDisk0r5`, `vDisk1r5`, `vDisk2r5`, `vDisk3r5` aux disques virtuels utilisés par le RAID 5 en C
 - `jVDsik0`, `jVDisk1`, `jVDisk2`, `jVDisk3` correspondent aux disques du système en Java.

Par defaut, c'est le dossier `RAID` à la racine du projet qui va contenir ces disques.

Le script shell `init_raid.sh` initialise ce dossier.
 - Si les disques virtuels n'existent pas, il les crée
 - Si les disques existes, il les supprime, puis en crée de nouveaux, vierges.

### Raid 0/1/5 C (sous unix) :

L'exécutable du RAID C est à la racine du projet.
**Il a été compilé sous Unix et est donc destiné à être lancé sous Unix !**
Il sera nécessaire de réeffectuer une compilation pour le lancer sur un autre système.

Pour l'exécuter, il suffit de lancer la commande dans ce même dossier :
```shell
./raid type_raid repertoire_disques
```
 - `type_raid` est un entier permettant d'identifier le type de RAID que l'on souhaite utiliser. Il peut être choisi parmi les valeurs {0, 1, 5}
 - `repertoire_disques` est le dossier qui contient les disques virtuels.
 
Par défaut, le dossier `RAID` à la racine du projet contient ces disques et peut donc être utilisé en paramètre de cette commande.

### Raid 5 Java :

L'executable du RAID 5 Java est aussi à la racine du dossier projet.
Il s'agit du fichier `raid5_java.jar`.
Pour qu'il s'exécute correctement, il faut qu'il soit lancé dans le même répertoire que le dossier `RAID` (qui contient les disques virtuels).
C'est aussi le cas par défaut à la racine du projet. 
Il suffit donc de lancer le programme `raid5_java.jar`.

## Crédits

Il serait déraisonnable de ne pas clôturer ce fichier README par un petit crédit aux développeurs de génie qui ont participé à la construction de ce projet.
J'ai nommé :
 - **Cyril Esclassan**, Chef de projet Tortionnaire qui n'a jamais daigné payer un centime ses subordonnés, mais heureusement, il fait plutôt bien son job.
 - **Dylan Caron**, Responsable conception de génie sans qui le code serait probablement bien moins artistique.
 - **Guillaume Broise**, Responsable dévelopement, grâce a qui le développement est actuellement excellemment bien développé.
 
Auteur de ce README : Dylan CARON (vous l'aviez deviné ?)
