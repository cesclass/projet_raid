package raid;

import java.io.*;

public class Test {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        VirtualDisk r5Disk = new VirtualDisk();
        
        FS.writeFile(r5Disk, "mv.txt".getBytes(), "Touche a ton cul qui croyait prendre.".getBytes());
        FS.writeFile(r5Disk, "null".getBytes(), "NULL".getBytes());
        FS.writeFile(r5Disk, "file".getBytes(), "With text inside".getBytes());
        FS.writeFile(r5Disk, "1337".getBytes(), "2.9.4.\n7.5.3\n6.1.8".getBytes());

        System.out.println(r5Disk);

        r5Disk.switchOffRaid();
        
    }
}