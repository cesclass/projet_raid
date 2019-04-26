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

        if(storage[0].length() == 0){
            /* SuperBlock */
            this.superBlock = new SuperBlock();
            
            /* Inodes */
            for (int i = 0; i < this.tabInode.length; i++) {
                this.tabInode[i] = new Inode();
            }
            this.superBlock.setFirstFreeByte(this.writeInodeTable());
            this.writeSuperBlock();

        } else {
            /* SuperBlock */
            this.readSuperBlock();
            
            /* Inode */
            this.readInodeTable();
        }
    }

    public int writeInodeTable() throws IOException {
        Stripe str = new Stripe();
        int pos = str.computeNStripe(Block.computeNBlock(RaidDefine.SUPER_BLOCK_BYTE_SIZE)) * 
                    RaidDefine.BLOCK_SIZE * nbDisque;
                    
        for (int i = 0; i < this.tabInode.length; i++) {
            pos = tabInode[i].write(this, pos);
        }

        return pos;
    }

    public void readInodeTable() throws ClassNotFoundException, IOException {
        Stripe str = new Stripe();
        int pos = str.computeNStripe(Block.computeNBlock(RaidDefine.SUPER_BLOCK_BYTE_SIZE)) * 
                    RaidDefine.BLOCK_SIZE * nbDisque;

        byte[] buff = new byte[RaidDefine.INODE_BYTE_SIZE];
        for (int i = 0; i < this.tabInode.length; i++) {
            pos = Inode.read(this, pos, buff);
            this.tabInode[i] = Inode.deserialize(buff);
        }
    }

    public void writeSuperBlock() throws IOException {
        this.superBlock.write(this);
    }

    public void readSuperBlock() throws ClassNotFoundException, IOException {
        byte[] buff = new byte[RaidDefine.SUPER_BLOCK_BYTE_SIZE];
        SuperBlock.read(this, buff);
        this.superBlock = SuperBlock.deserialize(buff);
    }

    /* Getters et Setters */
    public RandomAccessFile getStorage(int indice){
        return storage[indice];
    }

    public int getNbFile() {
        return this.nbFile;
    }

    public void setNbFile(int nbf) {
        this.nbFile = nbf;
    }

    public Inode getUnusedInode() {
        for (int i = 0; i < RaidDefine.INODE_TABLE_SIZE; i++) {
            if (tabInode[i].isUnused()) return tabInode[i];
        }

        return null;
    }

    public SuperBlock getSuperBlock() {
        return this.superBlock;
    }

    public Inode searchInode(byte[] filename) {
        String sfilename = new String(filename);
        String sinode;
        for (Inode i : tabInode) {
            sinode = new String(i.getFileName());
            if(sinode.equals(sfilename)) {
                return i;
            }
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

        str += " > superBlock : \n" + this.superBlock;
        
        str += "\n > tabInodes : \n";
        for(int i = 0; i < this.tabInode.length; i++) {
            if(!this.tabInode[i].isUnused()) {
                str += "inode " + i + " :\n" + this.tabInode[i].toString() + "\n";
            }
        }

        str += "\n > nbDisks : " + this.nbDisque + "\n";
        str += "\n > nbFiles : " + this.nbFile + "\n";
        str += "\n > raidType : " + this.raidType.name() + "\n";

        str += "\n";
        return str;
    }
 }

