package raid;

import java.io.*;

public class Test {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        VirtualDisk r5Disk = new VirtualDisk();
        System.out.println(r5Disk);

        /*  Test de readBlock, writeBlock, dumpBlockHexa */
        Block in = new Block();
        Block out = new Block();
        
        in.setDataI(0, (byte) 0x12);
        in.setDataI(1, (byte) 0x34);
        in.setDataI(2, (byte) 0x56);
        in.setDataI(3, (byte) 0x78);

        in.writeBlock(r5Disk, 0, 0);
        out.readBlock(r5Disk, 0, 0);

        System.out.print("> Block in  :");
        in.dumpBlockHexa();
        System.out.print("> Block out :");
        out.dumpBlockHexa();
        for (int i = 0; i < 4; i ++) {
            if (in.getDataI(i) != out.getDataI(i)) {
                System.err.println("> [ERR] Block 'in' different de Block 'out'");
                return;
            }
        }
        System.out.println("> Block 'in' = Block 'out'");

        

        /*
        Inode i = r5Disk.getUnusedInode();
        if(i == null) {
            System.err.println("[ERR] Aucun inode de libre...");
        }*/
        r5Disk.switchOffRaid();
        
    }
}