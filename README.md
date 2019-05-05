# projet_raid
Projet RAID - L2 Informatique - TOULOUSE III Paul Sabatier 

## Comment exécuter le systeme RAID ?

### Initialisation de l'environement :
En C ou en Java, le système RAID 5 utilise un repertoire dans lequels il stoque les disques virtuels qu'il utilise pour le stockage.
 - `vDisk0`, `vDisk1`, `vDisk2`, `vDisk3` correspondent aux disques virtuels utilisés par le RAID 5 en C
 - `jVDsik0`, `jVDisk1`, `jVDisk2`, `jVDisk3` correspondent aux disques du système en Java.
Par defaut, le dossier `RAID` à la racine du projet contient ces disques.
Pour réinitialiser ces disques, et partir d'un système RAID vierge, il faut supprimer ces disques virtuels.

### Raid 5 C :
L'executable du RAID 5 C est à la racine du dossier du projet (dans le dossier `projet_raid`)
Pour l'exécuter, il suffit de lancer la commande dans ce même dossier :
```shell
./raid5 repertoire_disque
```
Le `repertoire_disque` est le dossier qui contient ou contiendra les disques virtuels.
Par defaut, le dossier `RAID` à la racine du projet contient ces disques et peut donc être utilisé en parametre de cette commande.
Si les disques n'existent pas, ils seront générés. On peut donc passer un dossier vide au programme.

### Raid 5 Java :
L'executable du RAID 5 Java est aussi à la racine du dossier projet.
Il sagit du fichier raid5_java.jar.
Pour qu'il s'execute correctement, il faut qu'il soit lancé dans le même dossier qui contient le dossier RAID (dossier qui contient les disques virtuels)
C'est le cas par défaut à la racine du projet. Il suffit donc de lancer le programme raid5_java.jar

## Crédits

Il serait déraisonable de ne pas cloturer ce fichier README par un petit crédit aux développeurs de génie qui ont participé à la construction de ce projet.
J'ai nommé :
 - Cyril Esclassan, Chef de projet Tortionaire qui n'a jamais daigné payer un centime ses subordonés, mais heureusement, il faisait plutôt bien son job.
 - Dylan Caron, Responsable conception de génie sans qui le code serait probablement bien moins artistique.
 - Guillaume Broise, Responsable developement, graçe a qui le developpement est actuelement excelement développé.
 
Auteur de ce README : Dylan CARON (vous l'aviez deviné)
