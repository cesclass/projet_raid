package raid;

/**
 * @author Dylan
 *
 */
public class Inode {
	private byte[] filename = new byte[32];
	private int size;
	private int nBlocks;
	private int firstByte;
	
	public Inode() {
		filename[0] = 0;
		size = 0;
		nBlocks = 0;
		firstByte = 0;
	}
}
