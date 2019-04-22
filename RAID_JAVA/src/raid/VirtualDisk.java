package raid;

import java.io.*;

public class VirtualDisk{

    private Superblock superBlock;
    private Inode[] tabInode = new Inode[RaidDefine.INODE_TABLE_SIZE];
    private int nbDisque = 0;
    private int nbFile = 0;
    private RaidType raidType = RaidType.CINQ;
    /* Def raid type */
    private File []storage = new File[RaidDefine.MAX_DISK];

    /* Constructor */
    public VirtualDisk() {
        this.superBlock = new Superblock();
        for (int i = 0; i < this.tabInode.length; this.tabInode[i++] = new Inode());
    }

    /* Getters et Setters */
    public File getStorage(int indice) {
        return storage[indice];
    }


}