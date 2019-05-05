package raid;
import java.io.*;

/**
 * Cree, Gere et serialise le SuperBlock
 * 
 * @version 19.05.05
 */
public class SuperBlock implements Serializable{
	private static final long serialVersionUID = 1L;
	private RaidType raidType;
	private int nbBlocksUsed;
	private int firstFreeByte;
	
	/**
	 * Constructeur du superBlock
	 */
	public SuperBlock() {
		raidType = RaidType.CINQ;
		nbBlocksUsed = 0;
		firstFreeByte = 0;
	}

	/**
	 * Setter de l'attribut firstFreeByte
	 * 
	 * @param ffb			firstFreeByte
	 * 
	 * @throws IOException
	 */
	public void setFirstFreeByte(int ffb) {
		this.firstFreeByte = ffb;
	}

	/**
	 * Getter de l'attribut firstFreeByte
	 * 
	 * @return				firstFreeByte
	 */
	public int getFirstFreeByte() {
		return this.firstFreeByte;
	}

	/**
	 * Ecrit le SuperBlock sur le systeme RAID.
	 * 
	 * @param r5Disk		Systeme RAID 5
	 * 
	 * @throws IOException
	 */
	public void write(VirtualDisk r5Disk) throws IOException {
		byte[] buff = serialize();
		Stripe str = new Stripe();
		str.writeChunk(r5Disk, buff.length, buff, 0);
	}

	/**
	 * Lis le SuperBlock sur le systeme RAID et le stoque dans un buffer.
	 * 
	 * @param r5Disk		Systeme RAID 5
	 * @param buffer		Buffer de reception du SuperBlock
	 * 
	 * @throws ClassNotFoundException
	 * @throws IOException
	 */
	public static void read(VirtualDisk r5Disk, byte[] buffer) throws ClassNotFoundException, IOException {
		Stripe str = new Stripe();
		str.readChunk(r5Disk, buffer.length, buffer, 0);
	}

	/**
	 * Serialise le SuperBlock,
	 *  C'est a dire transforme l'objet en tableau de Byte.
	 * 
	 * @return				Tableau de Byte representant le SuperBlock
	 * 
	 * @throws IOException
	 */
	public byte[] serialize() throws IOException {
		ByteArrayOutputStream out = new ByteArrayOutputStream();
		ObjectOutputStream os = new ObjectOutputStream(out);
		os.writeObject(this);
		return out.toByteArray();
	}
	
	/**
	 * Deserialise le SuperBlock,
	 * 	C'est a dire transforme le tableau de Byte representant 
	 * 	le SuperBlock en objet.
	 * 
	 * @param data			Tableau de Byte representant le SuperBlock
	 * 
	 * @return				Objet SuperBlock
	 * 
	 * @throws IOException
	 * @throws ClassNotFoundException
	 */
	public static SuperBlock deserialize(byte[] data) throws IOException, ClassNotFoundException {
		ByteArrayInputStream in = new ByteArrayInputStream(data);
		ObjectInputStream is = new ObjectInputStream(in);
		return SuperBlock.class.cast(is.readObject());
	}

	/**
	 * Retourne un String représentant l'objet SuperBlock.
	 * 
	 * @return				String représentant l'objet SuperBlock
	 */
	public String toString() {
		return ("RaidType :      " + raidType + '\n' +
				"nbBlocksUsed :  " + nbBlocksUsed + '\n' +
				"FirstFreeByte : " + firstFreeByte + '\n');
	}
}
