package raid;

import java.io.*;

public abstract class FS {

    public static byte[] readFile(VirtualDisk r5Disk, byte[] filename) throws IOException {
        Inode id = r5Disk.searchInode(filename);
        byte[] buff = null;
        if (id != null) {
            buff = new byte[id.getSize()];
            new Stripe().readChunk(r5Disk, id.getSize(), buff, id.getFirstByte());
        }
        return buff;
    }

    public static boolean writeFile(VirtualDisk r5Disk, byte[] filename, byte[] data) throws IOException {
        Inode id = r5Disk.searchInode(filename);

        /* Cas ou le fichier existe mais pas assez de place */
        if (id != null && data.length > id.getSize()) {
            id.deleteInode();
            r5Disk.setNbFile(r5Disk.getNbFile() - 1);
            id = null;
        }

        if (id == null) {
            id = r5Disk.getUnusedInode();
            if (id == null)
                return false;
            id.init(filename, data.length, r5Disk.getSuperBlock().getFirstFreeByte());
            r5Disk.setNbFile(r5Disk.getNbFile() + 1);
        } else
            id.setSize(data.length);

        int newPos = new Stripe().writeChunk(r5Disk, id.getSize(), data, id.getFirstByte());

        r5Disk.writeInodeTable();

        if (newPos > r5Disk.getSuperBlock().getFirstFreeByte()) {
            r5Disk.getSuperBlock().setFirstFreeByte(newPos);
            r5Disk.writeSuperBlock();
        }

        return true;
    }

    public static boolean deleteFile(VirtualDisk r5Disk, byte[] filename) throws IOException {
        Inode id = r5Disk.searchInode(filename);
        if (id != null) {
            id.deleteInode();
            r5Disk.setNbFile(r5Disk.getNbFile() - 1);
            r5Disk.writeInodeTable();
            r5Disk.writeSuperBlock();
            return true;
        }
        return false;
    }

    public static boolean loadFileFromHost(VirtualDisk r5Disk, File file) {
        try {
            RandomAccessFile raf = new RandomAccessFile(file, "r");
            byte[] buff = new byte[(int) file.length()];
            raf.read(buff);
            raf.close();
            if (!writeFile(r5Disk, file.getName().getBytes(), buff)) {
                return false;
            }
        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
        return true;
    }

    public static boolean storeFileToHost(VirtualDisk r5Disk, byte[] filename, String path) {
        path += (path.charAt(0) == '/') ? '/' : '\\';
        path += new String(filename);

        try {
            byte[] buff = readFile(r5Disk, filename);
            if (buff == null) return false;
            
            RandomAccessFile raf = new RandomAccessFile(path, "rw");
            raf.write(buff);
            raf.close();

        } catch (IOException e) {
            e.printStackTrace();
            return false;
        }
        
        return true;
    }

    public static boolean fileExist(VirtualDisk r5Disk, byte[] filename) {
        return (r5Disk.searchInode(filename) != null);
    }
    
}