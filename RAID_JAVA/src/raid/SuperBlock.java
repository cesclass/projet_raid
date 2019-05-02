package raid;
import java.io.*;

/**
 * @author Dylan
 *
 */
public class SuperBlock implements Serializable{
	private static final long serialVersionUID = 1L;
	private RaidType raidType;
	private int nbBlocksUsed;
	private int firstFreeByte;
	
	public SuperBlock() {
		raidType = RaidType.CINQ;
		nbBlocksUsed = 0;
		firstFreeByte = 0;
	}

	public void setFirstFreeByte(int ffb) {
		this.firstFreeByte = ffb;
	}

	public int getFirstFreeByte() {
		return this.firstFreeByte;
	}

	public void write(VirtualDisk r5Disk) throws IOException {
		byte[] buff = serialize();
		Stripe str = new Stripe();
		str.writeChunk(r5Disk, buff.length, buff, 0);
	}

	public static void read(VirtualDisk r5Disk, byte[] buffer) throws ClassNotFoundException, IOException {
		Stripe str = new Stripe();
		str.readChunk(r5Disk, buffer.length, buffer, 0);
	}

	public byte[] serialize() throws IOException {
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		ObjectOutputStream os = new ObjectOutputStream(out);
		os.writeObject(this);
		return out.toByteArray();
	}
	
	public static SuperBlock deserialize(byte[] data) throws IOException, ClassNotFoundException {
		ByteArrayInputStream in = new ByteArrayInputStream(data);
		ObjectInputStream is = new ObjectInputStream(in);
		return SuperBlock.class.cast(is.readObject());
	}

	public String toString() {
		return ("RaidType :      " + raidType + '\n' +
				"nbBlocksUsed :  " + nbBlocksUsed + '\n' +
				"FirstFreeByte : " + firstFreeByte + '\n');
	}

	
}
