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
	public final static char BLOCK_SIZE = 4;
	public final static char FILENAME_MAX_SIZE = 32;
	public final static int MAX_FILE_SIZE = 50*1024;
	public final static char INODE_TABLE_SIZE = 10;
	public final static int MAX_MSG = 1024;
	public final static char SUPER_BLOCK_SIZE = 4;
	public final static char INODES_START = SUPER_BLOCK_SIZE * BLOCK_SIZE;
	public final static char INODE_SIZE = 11;
}
