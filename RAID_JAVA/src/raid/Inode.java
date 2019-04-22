package raid;

import java.io.*;

/**
 * @author Dylan
 *
 */
public class Inode {
	private byte[] fileName = new byte[32];
	private int size;
	private int nBlocks;
	private int firstByte;
	
	public Inode() {
		fileName[0] = 0;
		size = 0;
		nBlocks = 0;
		firstByte = 0;
	}

	public Inode(byte[] fileName, int size, int firstFreeByte) {
		this.fileName = fileName;
		this.size = size;
		nBlocks = Block.computeNBlock(size);
		firstByte = firstFreeByte;
	}

	/*
	public Inode(Object inode) {
		this.fileName = inode.fileName;

	}
	*/

	public boolean isUnused() {
		return fileName[0] == 0;
	}
	
	public byte[] serialize() throws IOException {
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		ObjectOutputStream os = new ObjectOutputStream(out);
		os.writeObject(this);
		return out.toByteArray();
	}
	
	public static Inode deserialize(byte[] data) throws IOException, ClassNotFoundException {
		ByteArrayInputStream in = new ByteArrayInputStream(data);
		ObjectInputStream is = new ObjectInputStream(in);
		return (Inode) is.readObject();
	}

	public String toString() {
		return ("Filename :  " + fileName.toString() + '\n' +
				"Size :      " + size + '\n' +
				"NBlock :    " + nBlocks + '\n' +
				"firstByte : " + firstByte + '\n');
	}
}
