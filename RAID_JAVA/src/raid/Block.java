package raid;

public class Block{

    private byte []data = new byte[RaidDefine.BLOCK_SIZE];

    /* Getters and Setters */
    public byte getDataI(int indice){
        return data[indice];
    }

    public void setDataI(int indice, byte valeur){
        data[indice] = valeur;
    }

    /* A completer */
    public int computeNBlock(int taille){
        return 0;
    }

    /* A completer */
    public int writeBlock(){
        return 0;
    }

    /* A completer */
    public int readBlock(){
        return 0;
    }

    /* A completer */
    public void repairBlock(){

    }

    /* A completer */
    public void dumpBlockHexa(){

    }

}