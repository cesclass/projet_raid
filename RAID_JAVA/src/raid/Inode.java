package raid;

import java.io.*;

/**
 * Cree, Gere et serialise un Inode
 * 
 * @version 19.05.05
 */
public class Inode implements Serializable {
	private static final long serialVersionUID = 1L;
	private byte[] fileName = new byte[RaidDefine.FILENAME_MAX_SIZE];
	private int size;
	private int nBlocks;
	private int firstByte;
	
	/**
	 * Constructeur d'Inode (vide)
	 */
	public Inode() {
		setFileName("\0".getBytes());
		size = 0;
		nBlocks = 0;
		firstByte = 0;
	}

	/**
	 * Initialise une Inode avec les valeurs passes en parametres
	 * 
	 * @param fileName		Nom du fichier correspondant a l'Inode
	 * @param size			Taille du fichier	
	 * @param firstFreeByte	Premier octet  du fichier sur le disque
	 */
	public void init(byte[] fileName, int size, int firstFreeByte) {
		setFileName(fileName);
		this.size = size;
		nBlocks = Block.computeNBlock(size);
		firstByte = firstFreeByte;
	}

	/**
	 * Reinitialise l'inode (vide)
	 */
	public void deleteInode() {
		this.init("\0".getBytes(), 0, 0);
	}

	/**
	 * Met a jour le nom du fichier dans l'Inode.
	 * 
	 * @param fileName		Nouveau nom de fichier
	 */
	public void setFileName(byte[] fileName) {
		int i;
		for (i = 0; i < fileName.length; i++) {
			this.fileName[i] = fileName[i];
		}
		for (; i < RaidDefine.FILENAME_MAX_SIZE; i++) {
			this.fileName[i] = '$';
		}
	}

	/**
	 * Met a jour la taille du fichier
	 *  en octets et en Blocks dans l'Inode.
	 * 
	 * @param size			Taille du fichier en octets
	 */
	public void setSize(int size) {
		this.size = size;
		this.nBlocks = Block.computeNBlock(size);
	}

	/**
	 * Getter de l'attribut filename
	 * 
	 * @return 				fileName
	 */
	public byte[] getFileName() {
		String filename = new String(this.fileName);
		filename = filename.replace("$", "");
		return filename.getBytes();
	}

	/**
	 * Getter de l'attribut size
	 * 
	 * @return 				size
	 */
	public int getSize() {
		return this.size;
	}

	/**
	 * Getter de l'attribut firstByte
	 * 
	 * @return 				firstByte
	 */
	public int getFirstByte() {
		return this.firstByte;
	}

	/**
	 * Retourne si l'Inode est vide
	 * 
	 * @return				true si l'Inode est vide, false sinon
	 */
	public boolean isUnused() {
		return fileName[0] == 0;
	}

	/**
	 * Lis l'Inode sur le systeme RAID et le stoque dans un buffer.
	 * 
	 * @param r5Disk		Systeme RAID 5
	 * @param pos			Position de l'Inode sur le disque (en octets)
	 * @param buffer		Buffer de reception de l'inode
	 * 
	 * @return				Le numero de l'octet suivant l'Inode lue sur le systeme RAID
	 * 
	 * @throws ClassNotFoundException
	 * @throws IOException
	 */
	public static int read(VirtualDisk r5Disk, int pos, byte[] buffer) throws ClassNotFoundException, IOException {
		Stripe str = new Stripe();
		pos = str.readChunk(r5Disk, buffer.length, buffer, pos);

		return pos;
	}

	/**
	 * Ecrit l'Inode sur le systeme RAID.
	 * 
	 * @param r5Disk		Systeme RAID 5
	 * @param pos			Position de l'Inode sur le disque (en octets)
	 * 
	 * @return 				Le numero de l'octet suivant l'Inode Ecrite sur le systeme RAID 			
	 * 
	 * @throws IOException
	 */
	public int write(VirtualDisk r5Disk, int pos) throws IOException {
		byte[] buff = serialize();
		Stripe str = new Stripe();
		return str.writeChunk(r5Disk, buff.length, buff, pos);
	}
	
	/**
	 * Serialise l'Inode,
	 *  C'est a dire transforme l'objet en tableau de Byte.
	 * 
	 * @return				Tableau de Byte representant l'Inode
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
	 * Deserialise l'Inode,
	 * 	C'est a dire transforme le tableau de Byte representant l'Inode
	 *  en objet.
	 * 
	 * @param data			Tableau de Byte representant l'Inode
	 * 
	 * @return				Objet Inode
	 * 
	 * @throws IOException
	 * @throws ClassNotFoundException
	 */
	public static Inode deserialize(byte[] data) throws IOException, ClassNotFoundException {
		ByteArrayInputStream in = new ByteArrayInputStream(data);
		ObjectInputStream is = new ObjectInputStream(in);
		return Inode.class.cast(is.readObject());
	}

	/**
	 * Retourne un String représentant l'objet Inode.
	 * 
	 * @return				String représentant l'objet Inode
	 */
	public String toString() {
		return ("Filename :  " + new String(this.getFileName()) + '\n' +
				"Size :      " + size + '\n' +
				"NBlock :    " + nBlocks + '\n' +
				"firstByte : " + firstByte + '\n');
	}
}
