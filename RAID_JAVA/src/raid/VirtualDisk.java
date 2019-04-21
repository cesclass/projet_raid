package raid;

import java.io.*;

public class VirtualDisk{

    private SuperBlock superBlock;
    private Inonde tabInode = new Inode[RaidDefine.INODE_TABLE_SIZE];
    private int nbDisque = 0;
    private int nbFile = 0;
    /* Def raid type */
    private RandomAccessFile []storage;

    /* Constructor */
    public VirtualDisk(){

        for(int i = 0; i < RaidDefine.MAX_DISK; i++){
            storage[i] = new RandomAccessFile(RaidDefine.PATH + RaidDefine.NAMEDISK + i, "rw");
        }
    }

    /* Getters et Setters */
    public RandomAccessFile getStorage(int indice){
        return storage[indice];
    }


}