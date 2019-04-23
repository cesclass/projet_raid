package raid;

import java.io.*;

/**
 * @author Dylan
 *
 */
public class Inode implements Serializable {
	private static final long serialVersionUID = 1L;
	private byte[] fileName = new byte[RaidDefine.FILENAME_MAX_SIZE];
	private int size;
	private int nBlocks;
	private int firstByte;
	
	public Inode() {
		setFileName("\0".getBytes());
		size = 0;
		nBlocks = 0;
		firstByte = 0;
	}

	public Inode(byte[] fileName, int size, int firstFreeByte) {
		setFileName(fileName);
		this.size = size;
		nBlocks = Block.computeNBlock(size);
		firstByte = firstFreeByte;
	}

	public void setFileName(byte[] fileName) {
		int i;
		for (i = 0; i < fileName.length; i++) {
			this.fileName[i] = fileName[i];
		}
		for (; i < RaidDefine.FILENAME_MAX_SIZE; i++) {
			this.fileName[i] = '$';
		}
	}

	public byte[] getFileName() {
		byte[] fileName = new byte[RaidDefine.FILENAME_MAX_SIZE];
		for (int i = 0; this.fileName[i] != '$' && i < this.fileName.length; i++) {
			fileName[i] = this.fileName[i];
		}

		return fileName;
	}

	public boolean isUnused() {
		return fileName[0] == 0;
	}

	

	public static int read(VirtualDisk r5Disk, int pos, Inode i) throws ClassNotFoundException, IOException {
		byte[] buff = new byte[RaidDefine.INODE_BYTE_SIZE];
		pos = Stripe.readChunk(r5Disk, buff.length, buff, pos);
		i =  deserialize(buff);

		return pos;
	}

	public int write(VirtualDisk r5Disk, int pos) throws IOException {
		byte[] buff = serialize();
		return Stripe.writeChunk(r5Disk, buff.length, buff, pos);
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
		return Inode.class.cast(is.readObject());
	}

	public String toString() {
		return ("Filename :  " + new String(this.getFileName()) + '\n' +
				"Size :      " + size + '\n' +
				"NBlock :    " + nBlocks + '\n' +
				"firstByte : " + firstByte + '\n');
	}
}
