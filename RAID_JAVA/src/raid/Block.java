package raid;

public class Block{

    private byte []data = new byte[RaidDefine.BLOCK_SIZE];

    /* Getters and Setters */
    public byte getData(int indice){
        return data[indice];
    }

    public void setDataI(int indice, byte valeur){
        data[indice] = valeur;
    }
}