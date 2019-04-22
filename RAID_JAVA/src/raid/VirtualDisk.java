package raid;

import java.io.*;

public class VirtualDisk{

    private SuperBlock superBlock;
    private Inonde tabInode = new Inode[RaidDefine.INODE_TABLE_SIZE];
    private int nbDisque = 0;
    private int nbFile = 0;
    /* Def raid type */
    private RandomAccessFile []storage = new RandomAccessFile[RaidDefine.BLOCK_SIZE];

    /* Constructor */
    public VirtualDisk(){

    }

    /* Getters et Setters */
    public RandomAccessFile getStorage(int indice){
        return storage[indice];
    }


}