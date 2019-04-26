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
    public static int computeNBlock(int taille){
        return taille / RaidDefine.BLOCK_SIZE + (taille % RaidDefine.BLOCK_SIZE);
    }

    /* A completer */
    public void writeBlock(VirtualDisk r5Disk, int position, int numdisk) throws IOException {
        r5Disk.getStorage(numdisk).seek(position*RaidDefine.BLOCK_SIZE);
        r5Disk.getStorage(numdisk).write(this.data);
    }

    /* A completer */
    public void readBlock(VirtualDisk r5Disk, int position, int numdisk) throws IOException { 
        r5Disk.getStorage(numdisk).seek(position*RaidDefine.BLOCK_SIZE);
        r5Disk.getStorage(numdisk).read(this.data);
    }

    /* A completer */
    public void repairBlock(VirtualDisk r5Disk, int position, int numdisk) throws IOException {
        Block repair = new Block();
        for(int i = 0; i < RaidDefine.BLOCK_SIZE; repair.data[i++]=0b0);

        Block read = new Block();
        for(int i = 0; i < RaidDefine.MAXDISK; i++) {
            if( i != numdisk){
                read.readBlock(r5Disk, position, i);
                for(int j = 0; j < RaidDefine.BLOCK_SIZE; j++){
                    repair.data[j] ^= read.data[j];
                }
            }
        }
        repair.writeBlock(r5Disk, position, numdisk);
    }

    /* A completer */
    public void dumpBlockHexa(){
        StringBuilder strDump = new StringBuilder(this.data.length*2);
        for(byte b: this.data){
            strDump.append(String.format("%x", b));
        }
        System.out.println(strDump);
    }

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