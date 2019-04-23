package raid;

import java.io.*;

public class VirtualDisk{

    private SuperBlock superBlock;
    private Inode[] tabInode = new Inode[RaidDefine.INODE_TABLE_SIZE];
    private int nbDisque = RaidDefine.MAXDISK;
    private int nbFile = 0;
    private RaidType raidType = RaidType.CINQ;
    private RandomAccessFile []storage = new RandomAccessFile[RaidDefine.MAXDISK];

    /* Constructor */
    public VirtualDisk() throws IOException, ClassNotFoundException {
        /* ouverture des disks du systeme RAID  */
        for(int i = 0; i < nbDisque; i++){
            storage[i] = new RandomAccessFile(RaidDefine.PATH + RaidDefine.NAMEDISK + i, "rw");
        }

        int pos = Stripe.computeNStripe(Block.computeNBlock(RaidDefine.SUPER_BLOCK_BYTE_SIZE)) * 
                    RaidDefine.BLOCK_SIZE * nbDisque;

        if(storage[0].length() == 0){
            /* SuperBlock */
            superBlock = new SuperBlock();
            
            /* Inodes */
            /*
            for (int i = 0; i < this.tabInode.length; i++) {
                this.tabInode[i] = new Inode();
                pos = tabInode[i].write(this, pos);
            }
            */
            superBlock.setFirstFreeByte(pos);
            superBlock.write(this);

        } else {
            /* SuperBlock */
            SuperBlock.read(this, this.superBlock);
            
            /* Inode */
            /*
            for (int i = 0; i < this.tabInode.length; i++) {
                pos = Inode.read(this, pos, tabInode[i]);
            }
            */
        }
    }

    /* Getters et Setters */
    public RandomAccessFile getStorage(int indice){
        return storage[indice];
    }

    public Inode getUnusedInode() {
        for (int i = 0; i < RaidDefine.INODE_TABLE_SIZE; i++) {
            if (tabInode[i].isUnused()) return tabInode[i];
        }

        return null;
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


    public String toString() {
        String str = "";

        str += " > superBlock : \n" + this.superBlock.toString();
        str += "\n > tabInodes : \n";
        /*
        for(int i = 0; i < this.tabInode.length; i++) {
            if(!this.tabInode[i].isUnused()) {
                str += "inode " + i + " :\n" + this.tabInode[i].toString() + "\n";
            }
        }
        */
        str += "\n > nbDisks : " + this.nbDisque + "\n";
        str += "\n > nbFiles : " + this.nbFile + "\n";
        str += "\n > raidType : " + this.raidType.name() + "\n";

        str += "\n";
        return str;
    }
 }

