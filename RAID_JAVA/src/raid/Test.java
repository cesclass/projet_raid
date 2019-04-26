package raid;

import java.io.*;

public class Test {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        VirtualDisk r5Disk = new VirtualDisk();

        byte[] filename = "monfichier.txt".getBytes();

        FS.deleteFile(r5Disk, filename);

        /*
        FS.writeFile(r5Disk, filename, 
                "Touche a ton cul qui croyait prendre.".getBytes());
        
        System.out.println(new String(FS.readFile(r5Disk, filename)));
        */

        System.out.println(r5Disk);

        r5Disk.switchOffRaid();
        
    }
}