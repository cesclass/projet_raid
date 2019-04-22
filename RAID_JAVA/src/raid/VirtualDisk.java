package raid;

import java.io.*;

public class VirtualDisk{

    private SuperBlock superBlock;
    private Inode[] tabInode = new Inode[RaidDefine.INODE_TABLE_SIZE];
    private int nbDisque = RaidDefine.MAXDISK;
    private int nbFile = 0;
    private RaidType raidType = RaidType.CINQ;
    private RandomAccessFile []storage = new RandomAccessFile[RaidDefine.BLOCK_SIZE];

    /* Constructor */
    public VirtualDisk() throws IOException {
        /* ouverture des disks du systeme RAID*/
        for(int i = 0; i < nbDisque; i++){
            storage[i] = new RandomAccessFile(RaidDefine.PATH + RaidDefine.NAMEDISK + i, "rw");
        }

        if(storage[0].length() == 0){
            /* SuperBlock */
            this.superBlock = new SuperBlock();
            
            /* Inodes */
            for (int i = 0; i < this.tabInode.length; this.tabInode[i++] = new Inode());
        } else {
            /* SuperBlock */
            this.superBlock = SuperBlock.read();
            
            /* Inode */
            for (int i = 0; i < this.tabInode.length; i++) {
                this.tabInode[i] = Inode.deserialize();
            }
        }
    }

    /* Getters et Setters */
    public RandomAccessFile getStorage(int indice){
        return storage[indice];
    }

    /**
     * 
     * Ferme tous les disks du systeme RAID
     * 
     */
    public void switchOffRaid() throws IOException {
        for(int i = 0; i < nbDisque; i++){
            storage[i].close();
        }
    }
}