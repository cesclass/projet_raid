/**
 * 
 */
package raid;

/**
 * @author Dylan
 * Definition des constantes du systeme RAID 5
 */


public class RaidDefine {
	public final static int ERREUR = -1; /* Code de retour d'erreur */
	public final static int BLOCK_SIZE = 4; /* Taille d'un block en octet */
	public final static int FILENAME_MAX_SIZE = 32; /* Longueur maximale du nom d'un fichier */
	public final static int MAX_FILE_SIZE = 50*1024; /* Taille maximale d'un fichier */
	public final static int INODE_TABLE_SIZE = 10;	 /* Taille de la table d'inode */
	public final static int MAX_MSG = 1024;	 /* Taille maximale d'un message */
	public final static int SUPER_BLOCK_SIZE = 4; /* Taille d'un SuperBlock */
	public final static int INODES_START = SUPER_BLOCK_SIZE * BLOCK_SIZE; /* Position de debut de la table d'inode */
	public final static int INODE_SIZE = 11; /* Taille d'une inode */
	public final static int MAXDISK = 4;	/* Nombre maximal de disk */

	public final static String PATH  = "RAID/"; /* Chemin d'acces aux disks virtuels */
	public final static String NAMEDISK = "jVDisk"; /* Nom des disks */

	public final static int INODE_BYTE_SIZE = 143; /* Taille d'une inode en octet */
	public final static int SUPER_BLOCK_BYTE_SIZE = 170; /* Taille d'un SuperBlock en octet */
}
