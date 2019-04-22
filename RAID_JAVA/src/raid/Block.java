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
        r5Disk.getStorage(numdisk).write(writeB.data, position, writeB.data.length);

        return 0;
    }

    /* A completer */
    public Block readBlock(VirtualDisk r5Disk, int position, int numdisk, Block readB) throws IOException { 
        r5Disk.getStorage(numdisk).read(readB.data, position, readB.data.length);

        return readB;
    }

    /* A completer */
    public void repairBlock(VirtualDisk r5Disk, int position, int numdisk) throws IOException {
        Block repair = new Block();
        for(int i = 0; i < RaidDefine.BLOCK_SIZE; repair.data[i++]=0b0);

        Block read = new Block();
        for(int i = 0; i < RaidDefine.MAXDISK; i++) {
            if( i != numdisk){
                read = readBlock(r5Disk, position, i, repair);
                for(int j = 0; j < RaidDefine.BLOCK_SIZE; j++){
                    repair.data[j] ^= read.data[j];
                }
            }
        }
        writeBlock(r5Disk, position, numdisk, repair);
    }

    /* A completer */
    public void dumpBlockHexa(Block dump){
        StringBuilder strDump = new StringBuilder(dump.data.length*2);
        for(byte b: dump.data){
            strDump.append(String.format("%x", b));
        }
        System.out.println(" " + strDump);
    }

}