#ifndef __R5_DEFINES__
#define __R5_DEFINES__

#include <stdio.h>

#define ERREUR -1
#define BLOCK_SIZE 4 // octets
#define FILENAME_MAX_SIZE 32 // caractères
#define MAX_FILE_SIZE (50*1024) // uchar
#define INODE_TABLE_SIZE 10 // taille fixe = nb max fichiers
#define MAX_MSG 1024 // uchar
#define SUPER_BLOCK_SIZE 4 // nb blocs avec parité
#define INODES_START SUPER_BLOCK_SIZE*BLOCK_SIZE // en octets
#define INODE_SIZE 11 // en blocks avec parité

typedef unsigned int uint; // même taille que int
typedef unsigned char uchar; // 8 bits = octet
enum raid {ZERO,UN,CINQ,ZERO_UN,UN_ZERO,CINQUANTE,CENT};

/* Type of a block of data */
typedef struct block_s{
    uchar data[BLOCK_SIZE]; // une case par octet
} block_t;

/* Type of the pseudo-inode structure */
typedef struct inode_s{
  char filename[FILENAME_MAX_SIZE]; // dont '\0'
  uint size; // du fichier en octets
  uint nblock; // nblock du fichier = (size+BLOCK_SIZE-1)/BLOCK_SIZE ?
  uint first_byte; // start block number on the virtual disk
} inode_t;

/* Type of the inode table */

typedef inode_t inode_table_t[INODE_TABLE_SIZE];// la taille est fixe

typedef struct super_block_s{
  enum raid raid_type;
  uint nb_blocks_used; //
  uint first_free_byte; // premier octet libre
  } super_block_t;

/* Type of the virtual disk system */
typedef struct virtual_disk_s {
    int number_of_files;
    super_block_t super_block;
    inode_table_t inodes;// tableau
    int ndisk;
    enum raid raidmode; // type de RAID
    FILE **storage; //tab[NUMBER_OF_DISKS];
} virtual_disk_t;

//=======================================================
typedef struct stripe_s {
  // inclut le bloc de parité
  int nblocks; // egal à NB_DISK : un bloc par disque
  block_t *stripe; // stripe[NB_DISK] les data
} stripe_t;

typedef struct file_s{
  uint size; // Size of file in bytes
  uchar data [MAX_FILE_SIZE]; // only text files
} file_t;

#endif // __R5_DEFINES__
