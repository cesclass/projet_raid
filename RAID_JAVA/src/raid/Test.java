package raid;

import java.io.*;
import raid.*;

public class Test {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        /* Tests des inodes */
        Inode i1 = new Inode("Inode".getBytes(), 0, 0);
        System.out.println("Inode pre serial : \n" + i1);
        
        byte[] is = i1.serialize();
        System.out.println("Inode serialized size : " + is.length);
        
        Inode i2 = Inode.deserialize(is);
        System.out.println("Inode post serial : \n" + i2);

        /* Tests des SuperBlock */
        SuperBlock s1 = new SuperBlock();
        System.out.println("SuperBlock : \n" + s1);

        byte[] ss = s1.serialize();
        System.out.println("SuperBlock serialized size : " + ss.length);

        SuperBlock s2 = SuperBlock.deserialize(ss);
        System.out.println("SuperBlock : \n" + s2);
    }

}