package raid;

/**
 * @author Dylan
 *
 */
public class SuperBlock {
	private RaidType raidType;
	private int nbBlocksUsed;
	private int firstFreeByte;
	
	public SuperBlock() {
		raidType = null;
		nbBlocksUsed = 0;
		firstFreeByte = 0;
	}
}
