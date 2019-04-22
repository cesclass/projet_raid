package raid;

import java.io.*;

public class VirtualDisk{

    private SuperBlock superBlock;
    private Inonde tabInode = new Inode[RaidDefine.INODE_TABLE_SIZE];
    private int nbDisque = 0;
    private int nbFile = 0;
    /* Def raid type */
    private File []storage = new File[RaidDefine.MAX_DISK];

    /* Constructor */
    public VirtualDisk(){

    }

    /* Getters et Setters */
    public File getStorage(int indice){
        return storage[indice];
    }


}