package raid;

import java.io.*;

/**
 * Cree et gere le VirtualDisk.
 *  Le VirtualDisk represente le systeme RAID et permet 
 *  de gerer ce systeme, sa table d'Inode et son SuperBlock.
 * 
 * @version 19.05.05
 */
public class VirtualDisk{

    /* Attributs */

    private SuperBlock superBlock;
    private Inode[] tabInode = new Inode[RaidDefine.INODE_TABLE_SIZE];
    private int nbDisque = RaidDefine.MAXDISK;
    private int nbFile = 0;
    private RaidType raidType = RaidType.CINQ;
    private RandomAccessFile []storage = new RandomAccessFile[RaidDefine.MAXDISK];

    /* Constructeur */

    /**
     * Constructeur du Virtual Disk contenant la table d'inode et
     *  le super block. 
     * Initialisation dynamique selon le contenu des disques virtuels.
     * 
     * @throws IOException
     * @throws ClassNotFoundException
     */
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

    /* Reader er Writer */

    /**
     * Ecrit la table d'inodes sur les disques virtuels et retourne
     *  la position du premier octet apres la table (sur les disques virtuels).
     * 
     * @return Premier octet apres l'ecriture de la table
     * 
     * @throws IOException
     */
    public int writeInodeTable() throws IOException {
        Stripe str = new Stripe();
        int pos = str.computeNStripe(Block.computeNBlock(RaidDefine.SUPER_BLOCK_BYTE_SIZE)) * 
                    RaidDefine.BLOCK_SIZE * nbDisque;
                    
        for (int i = 0; i < this.tabInode.length; i++) {
            pos = tabInode[i].write(this, pos);
        }

        return pos;
    }

    /**
     * Charge la table d'inodes depuis les disques virtuels.
     * 
     * @throws ClassNotFoundException
     * @throws IOException
     */
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

    /**
     * Ecrit le super block sur les disques virtuels.
     * 
     * @throws IOException
     */
    public void writeSuperBlock() throws IOException {
        this.superBlock.write(this);
    }

    /**
     * Charge le super bloc depuis les disques virtuels.
     * 
     * @throws ClassNotFoundException
     * @throws IOException
     */
    public void readSuperBlock() throws ClassNotFoundException, IOException {
        byte[] buff = new byte[RaidDefine.SUPER_BLOCK_BYTE_SIZE];
        SuperBlock.read(this, buff);
        this.superBlock = SuperBlock.deserialize(buff);
    }

    /* Getters et Setters */

    /**
     * Retourne un vDisk (RandomAccessFile) .
     * 
     * @param indice : Indice du vDisk a retourner 
     * 
     * @return vDisk (RandomAcessFile)
     */
    public RandomAccessFile getStorage(int indice){
        return storage[indice];
    }

    /**
     * Retourne le nombre de fichier(s) dans le RAID.
     * 
     * @return nombre de fichier(s) dans le RAID
     */
    public int getNbFile() {
        return this.nbFile;
    }

    /**
     * Met a jour le nombre de fichier(s) dans le RAID.
     * 
     * @param nbf : Nouveau nombre de fichier(s)
     */
    public void setNbFile(int nbf) {
        this.nbFile = nbf;
    }

    /**
     * Retourne une inode vide si il en reste.
     * 
     * @return Une inode vide si possible, null sinon
     */
    public Inode getUnusedInode() {
        for (int i = 0; i < RaidDefine.INODE_TABLE_SIZE; i++) {
            if (tabInode[i].isUnused()) return tabInode[i];
        }

        return null;
    }

    /**
     * Retourne le super block
     * 
     * @return Le super block
     */
    public SuperBlock getSuperBlock() {
        return this.superBlock;
    }

    /**
     * Retourne une inode de la table d'inodes.
     * 
     * @param indice : Indice de l'inode dans la table
     * 
     * @return L'inode correspondant a l'indice si possible, null sinon
     */
    public Inode getInode(int indice) {
        return this.tabInode[indice];
    }

    /**
     * Retourne l'inode designe par filename.
     * 
     * @param filename : Nom de l'inode
     * 
     * @return L'inode designe par filename si possible, null sinon
     */
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


    /* utils */

    /**
     * Ferme tous les disks du systeme RAID.
     * 
     * @throws IOException
     */
    public void switchOffRaid() throws IOException {
        for(int i = 0; i < nbDisque; i++){
            storage[i].close();
        }
    }

    /**
     * Retourne Une chaine contenant la representation du virtual disk et des
     *  objets qu'il contient (inodes, super block, vDisks...)
     * 
     * @return Une chaine contenant la representatino du virtual disk
     */
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

