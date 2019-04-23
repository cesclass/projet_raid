package raid;

import java.io.IOException;

/**
 * La classe Stripe permet de contruire la parite de la donnee, de l'ecrire et
 * de la lire sur le systeme RAID 5
 * 
 * @author Dylan
 * 
 * @version 19.04.20
 */
public class Stripe {
	private static int nBlocks = RaidDefine.MAXDISK;
	private static Block[] datas = new Block[nBlocks - 1];
	private static Block parity = new Block();

	/**
	 * Calcule le nombre de stripe necessaire pour stoquer un certains nombre de
	 * block.
	 * 
	 * @param nBlocks Nombre de block
	 * 
	 * @return int Nombre de Stripe necessaire
	 */
	public static int computeNStripe(int nBlocksToStore) {
		return nBlocksToStore / (nBlocks - 1) + ((nBlocksToStore % (nBlocks - 1) != 0) ? 1 : 0);
	}

	/**
	 * Calcule le block de parite de la Stripe et le met a jour.
	 */
	public static void computeParity() {
		for (int i = 0; i < RaidDefine.BLOCK_SIZE; i++) {
			for (int j = 0; j < (nBlocks - 1); parity.setDataI(i, (byte) (parity.getDataI(i) ^ datas[j++].getDataI(i))));
		}
	}

	/**
	 * Calcule le numero du disque sur lequel doit etre stoque le bloc de parite.
	 * 
	 * @param numStripe Numero du stripe (/!\ demmare a 0 !)
	 * 
	 * @return int Numero du disque (/!\ demmare a 0 !)
	 */
	public static int parityIndex(int numStripe) {
		return ((-((numStripe + 1) % nBlocks) + nBlocks) % nBlocks);
	}

	/**
	 * Ecrit une bande a une position donnee sur le systeme RAID 5.
	 * 
	 * @param pos N* de la ligne ou ecrire la Stripe
	 * @throws IOException
	 */
	public static void writeStripe(VirtualDisk r5Disk, int pos) throws IOException {
		/*	Calcul de l'indice du bloc de parite */
		int iParity = parityIndex(pos);
		
		for (int i = 0; i < nBlocks; i++) {
			if (i < iParity)			/*	Ecriture des blocs positionnees avant le bloc de parite */
				datas[i].writeBlock(r5Disk, pos, i);
			else if(i > iParity)		/*	Ecriture des blocs positionnees apres le bloc de parite */
				datas[i - 1].writeBlock(r5Disk, pos, i);
			else						/*	Ecriture du bloc de paritee */
				parity.writeBlock(r5Disk, pos, i);
		}	
	}
	
	/**
	 * Lit une bande a une position donnee sur le systeme RAID 5
	 * 
	 * @param pos           N* de la ligne ou lire la Stripe
	 * @throws IOException
	 */
	public static void readStripe(VirtualDisk r5Disk, int pos) throws IOException {
		/*	Calcul de l'indice du bloc de parite */
		int iParity = parityIndex(pos);
		
		/*	Creation de la Stripe */
		for (int i = 0; i < nBlocks - 1; datas[i++] = new Block());

		for (int i = 0; i < nBlocks; i ++) {
			if (i < iParity) {			/*  Lecture des blocs positionnees avant le bloc de parite */
				try {
					datas[i].readBlock(r5Disk, pos, i);
				} catch (IOException e) {
					datas[i].repairBlock(r5Disk, pos, i);
				}
			} else if (i > iParity)	{	/*  Lecture des blocs positionnees apres le bloc de parite */
				try {
					datas[i - 1].readBlock(r5Disk, pos, i);
				} catch (IOException e) {
					datas[i - 1].repairBlock(r5Disk, pos, i);
				}
			} else {					/*  Lecture du bloc de parite */
				try {
					parity.readBlock(r5Disk, pos, i);
				} catch (IOException e) {
					parity.repairBlock(r5Disk, pos, i);
				}
			}
		}
	}
	
	/**
	 * Ecrit sur le systeme RAID 5 le contenu du buffer a partir de la position pos.
	 * 
	 * @param bufLen Taille du buffer en octet
	 * @param buffer Buffer a ecrire
	 * @param pos    Position de depart pour l'ecriture sur le RAID (en octet)
	 * 
	 * @return int Premier octet libre apres l'ecriture
	 * @throws IOException
	 */
	public static int writeChunk(VirtualDisk r5Disk, int bufLen, byte[] buffer, int pos) throws IOException {
		pos /= (nBlocks * RaidDefine.BLOCK_SIZE);
		
		for (int iBuf = 0; iBuf < bufLen;) {
			/*	Construction de la stripe */
			for (int i = 0; i < nBlocks - 1; datas[i++] = new Block());
			int iBlock;
			for (iBlock = 0; iBlock < nBlocks - 1; iBlock++) {
				for (int iByte = 0; iByte < RaidDefine.BLOCK_SIZE; iByte ++) {
					if (iBuf < bufLen) {
						datas[iBlock].setDataI(iByte, buffer[iBuf++]);
					} else {
						datas[iBlock].setDataI(iByte, (byte) 0);
					}
				}
			}
		
			/*	Calcul de la parite */
			computeParity();
			
			/*	Ecriture de la Stripe sur le RAID */
			writeStripe(r5Disk, pos++);
		}
		
		return (pos * nBlocks * RaidDefine.BLOCK_SIZE);
	}
	
	/**
	 * Lit sur le syst�me RAID 5 un nombre d'octets definis par bufLen et les stocke
	 * dans le buffer � partir de la position pos.
	 * 
	 * @param bufLen Taille du buffer en octet (et nombre d'octets a lire)
	 * @param buffer Buffer de stockage
	 * @param pos    Position de depart pour la lecture sur le RAID (en octet)
	 * @throws IOException
	 */
	public static int readChunk(VirtualDisk r5Disk, int bufLen, byte[] buffer, int pos) throws IOException {
		pos /= (nBlocks * RaidDefine.BLOCK_SIZE);
		
		for (int iBuf = 0; iBuf < bufLen;) {
			/*	Lecture d'une Stripe */
			readStripe(r5Disk, pos++);
			
			/*	Ecriture de la stripe lue dans le buffer */
			for (int iBlock = 0; iBlock < nBlocks - 1; iBlock ++) {
				for (int iByte = 0; iByte < RaidDefine.BLOCK_SIZE; iByte ++) {
					if (iBuf < bufLen) {
						buffer[iBuf ++] = datas[iBlock].getDataI(iByte);
					}
				}
			}
		}

		return (pos * nBlocks * RaidDefine.BLOCK_SIZE);
	}
}
