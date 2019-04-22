/**
 * 
 */
package raid;

/**
 * @author Dylan
 *
 */
public class RaidDefine {
	public final static int ERREUR = -1;
	public final static int BLOCK_SIZE = 4;
	public final static int FILENAME_MAX_SIZE = 32;
	public final static int MAX_FILE_SIZE = 50*1024;
	public final static int INODE_TABLE_SIZE = 10;
	public final static int MAX_MSG = 1024;
	public final static int SUPER_BLOCK_SIZE = 4;
	public final static int INODES_START = SUPER_BLOCK_SIZE * BLOCK_SIZE;
	public final static int INODE_SIZE = 11;
	public final static int MAXDISK = 4;

	public final static String PATH  = "../RAID/";
	public final static String NAMEDISK = "vDisk";
}
