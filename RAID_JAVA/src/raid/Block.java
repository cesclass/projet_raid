package raid;
import java.io.*;

/**
 * La classe Block permet l'ecriture, la lecture et la reparation
 * des blocks sur le systeme RAID 5
 * 
 * @version 19.05.05
 */

public class Block{

    private byte []data = new byte[RaidDefine.BLOCK_SIZE];

    /**
     * Getter de []data
     * 
     * @param indice : indice du block de donnee
     * 
     * @return donnee a la position indice
     */
    public byte getDataI(int indice){
        return data[indice];
    }

    /**
     * Setter de []data
     * 
     * @param indice : indice du block de donnee
     * @param valeur : valeur a affecter
     *
     */
    public void setDataI(int indice, byte valeur){
        data[indice] = valeur;
    }

    /**
     * Calcule le nombre de block necessaire pour ecrire une certaine taille 
     * 
     * @param taille : taille a decouper en block
     * 
     * @return nombre de block necessaire
     */
    public static int computeNBlock(int taille){
        return taille / RaidDefine.BLOCK_SIZE + (taille % RaidDefine.BLOCK_SIZE);
    }

    /**
     * Ecrit le block sur un des disks du Raid a une position donnee
     * 
     * @param r5Disk : systeme de Raid contenant les disk
     * @param position : position du block a ecrire sur le disk
     * @param numdisk : numero du disk ou ecrire le block
     * 
     * @throws IOException
     */
    public void writeBlock(VirtualDisk r5Disk, int position, int numdisk) throws IOException {
        r5Disk.getStorage(numdisk).seek(position*RaidDefine.BLOCK_SIZE);
        r5Disk.getStorage(numdisk).write(this.data);
    }

    /**
     * Lit un block sur un des disks du Raid a une position donnee
     * 
     * @param r5Disk : systeme de Raid contenant les disk
     * @param position : position du block a lire sur le disk
     * @param numdisk : numero du disk ou lire le block
     * 
     * @throws IOException
     */
    public void readBlock(VirtualDisk r5Disk, int position, int numdisk) throws IOException { 
        r5Disk.getStorage(numdisk).seek(position*RaidDefine.BLOCK_SIZE);
        r5Disk.getStorage(numdisk).read(this.data);
    }

    /**
     * Repare le block sur un des disks du Raid a une position donnee
     * 
     * @param r5Disk : systeme de Raid contenant les disk
     * @param position : position du block a reparer sur le disk
     * @param numdisk : numero du disk ou reparer le block
     * 
     * @throws IOException
     */
    public void repairBlock(VirtualDisk r5Disk, int position, int numdisk) throws IOException {
        Block repair = new Block();
        /* Initialisation du block a 0 */
        for(int i = 0; i < RaidDefine.BLOCK_SIZE; repair.data[i++]=0b0);

        Block read = new Block();
        for(int i = 0; i < RaidDefine.MAXDISK; i++) {
            if( i != numdisk){
                read.readBlock(r5Disk, position, i);
                /* XOR des donnees des blocks repair et read */
                for(int j = 0; j < RaidDefine.BLOCK_SIZE; j++){

                    repair.data[j] ^= read.data[j];
                }
            }
        }
        repair.writeBlock(r5Disk, position, numdisk);
    }

    /**
     * Affiche un block sous la forme hexadecimal
     * 
     */
    public String toString() {
        String str = "";
        for(byte b: this.data){
            if (b < 0x10 && b >= 0x00) {
                str += 0;
            }
            str += String.format("%x", b);
        }
        return str;
    }

}