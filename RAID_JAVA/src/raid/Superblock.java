package raid;

/**
 * @author Dylan
 *
 */
public class Superblock {
	private RaidType raidType;
	private int nbBlocksUsed;
	private int firstFreeByte;
	
	public Superblock() {
		raidType = null;
		nbBlocksUsed = 0;
		firstFreeByte = 0;
	}
}
