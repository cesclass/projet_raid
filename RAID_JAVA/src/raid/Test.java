package raid;

import java.io.*;

public class Test {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        VirtualDisk r5Disk = new VirtualDisk();
        System.out.println(r5Disk);
        
        /*
        Inode i = r5Disk.getUnusedInode();
        if(i == null) {
            System.err.println("[ERR] Aucun inode de libre...");
        }*/
        
    }
}