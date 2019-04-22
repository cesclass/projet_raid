package raid;
import java.io.*;

public class Block{

    private byte []data = new byte[RaidDefine.BLOCK_SIZE];

    /* Getters and Setters */
    public byte getDataI(int indice){
        return data[indice];
    }

    public void setDataI(int indice, byte valeur){
        data[indice] = valeur;
    }

    /**
     * calcule le nombre de block necessaire pour ecrire taille 
     * 
     * @param taille : taille a decouper en block
     * @return : nombre de block necessaire
     * 
     */

    public int computeNBlock(int taille){
        return taille / RaidDefine.BLOCK_SIZE + (taille % RaidDefine.BLOCK_SIZE);
    }

    /* A completer */
    public int writeBlock(VirtualDisk r5Disk, int position, int numdisk, Block writeB) throws IOException {
        RandomAccessFile dest = new RandomAccessFile(r5Disk.getStorage(numdisk), "rw");

        dest.write(, off, len);
        dest.close();

        return 0;
    }

    /* A completer */
    public int readBlock(VirtualDisk r5Disk, int position, int numdisk, Block readB) throws IOException {
        RandomAccessFile source = new RandomAccessFile(r5Disk.getStorage(numdisk), "rw");

        source.seek(position);


        return 0;
    }

    /* A completer */
    public void repairBlock(){

    }

    /* A completer */
    public void dumpBlockHexa(){

    }

}