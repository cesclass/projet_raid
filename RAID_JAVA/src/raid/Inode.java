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

	public void init(byte[] fileName, int size, int firstFreeByte) {
		setFileName(fileName);
		this.size = size;
		nBlocks = Block.computeNBlock(size);
		firstByte = firstFreeByte;
	}

	public void deleteInode() {
		this.init("\0".getBytes(), 0, 0);
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

	public void setSize(int size) {
		this.size = size;
		this.nBlocks = Block.computeNBlock(size);
	}

	public byte[] getFileName() {
		String filename = new String(this.fileName);
		filename = filename.replace("$", "");
		return filename.getBytes();
	}

	public int getSize() {
		return this.size;
	}

	public int getFirstByte() {
		return this.firstByte;
	}

	public boolean isUnused() {
		return fileName[0] == 0;
	}

	public static int read(VirtualDisk r5Disk, int pos, byte[] buffer) throws ClassNotFoundException, IOException {
		Stripe str = new Stripe();
		pos = str.readChunk(r5Disk, buffer.length, buffer, pos);

		return pos;
	}

	public int write(VirtualDisk r5Disk, int pos) throws IOException {
		byte[] buff = serialize();
		Stripe str = new Stripe();
		return str.writeChunk(r5Disk, buff.length, buff, pos);
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
