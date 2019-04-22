package raid;

import java.io.*;

public class VirtualDisk{

    private Superblock superBlock;
    private Inode[] tabInode = new Inode[RaidDefine.INODE_TABLE_SIZE];
    private int nbDisque = 0;
    private int nbFile = 0;
    private RaidType raidType = RaidType.CINQ;
    /* Def raid type */
    private RandomAccessFile []storage = new RandomAccessFile[RaidDefine.BLOCK_SIZE];

    /* Constructor */
    public VirtualDisk() {
        this.superBlock = new Superblock();
        for (int i = 0; i < this.tabInode.length; this.tabInode[i++] = new Inode());
    }

    /* Getters et Setters */
    public RandomAccessFile getStorage(int indice){
        return storage[indice];
    }


}