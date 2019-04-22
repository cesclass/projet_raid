package raid;

import java.io.*;
import raid.*;

public class Test {
    public static void main(String[] args) throws IOException {
        /* Ici c'est la zone de test des lapinous */
        /*
        Inode i1 = new Inode("Inode0".getBytes(), 15, 55);
        System.out.println("Inode pre serial : " + i1.toString());
        
        byte[] is = i1.serialize();
        System.out.println("Inode serialize" + is.toString());
        
        Inode i2 = (Inode) Inode.deserialize(is);
        System.out.println("Inode post serial : " + i2.toString());
        */
        // <3
        RandomAccessFile test = new RandomAccessFile(RaidDefine.PATH + RaidDefine.NAMEDISK + 0 , "rw");
        System.out.println(test.length());

        /* test methode Block */
        int size = 400;
        System.out.println("Compute nblock : " + Block.computeNBlock(size));
        
        /* Write & Read block */
        Block write = new Block();
        Block read = new Block();
        byte a = 65;
        for(int i = 0; i < RaidDefine.BLOCK_SIZE; write.setDataI(i++,a));
        
        System.out.println("Ecriture de write");
        write.dumpBlockHexa();
        test.write(write.data, 0, write.data.length);
        write.dumpBlockHexa();

        read.dumpBlockHexa();
        System.out.println("Lecture de read");

        test.seek(0);
        test.read(read.data);
        test.read(read.data, 0, read.data.length);
        //test.read(read.data, 0,4);

        read.dumpBlockHexa();
        test.close();
    }

}