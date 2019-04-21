package raid;

/**
 * La classe Stripe permet de contruire la parite de la donnee, 
 * de l'ecrire et de la lire sur le systeme RAID 5
 * 
 * @author Dylan
 * 
 * @version 19.04.20
 */
public class Stripe {
	private int nBlocks;
	private Block[] datas;
	private Block parity;
	
	public Stripe(int nDisks) {
		nBlocks = nDisks;
		
		datas = new Block[nBlocks - 1];
		for (int i = 0; i < nBlocks - 1; datas[i++] = new Block());
		
		parity = new Block();		
	}
	
	/**
	 * Calcule le nombre de stripe necessaire pour stoquer un certains nombre de block.
	 * 
	 * @param nBlocks		Nombre de block
	 * 
	 * @return int			Nombre de Stripe necessaire
	 */
	public int computeNStripe(int nBlocks) {
		return nBlocks / (this.nBlocks - 1) + ((nBlocks % (this.nBlocks - 1) != 0) ? 1 : 0);
	}
	
	/**
	 * Calcule le block de parite de la Stripe et le met a jour.
	 */
	public void computeParity() {
		for (int i = 0; i < RaidDefine.BLOCK_SIZE; i++) {
			for (int j = 0; j < (nBlocks - 1); 
					parity.setDataI(i, parity.getDataI(i) ^ datas[j++].getDataI(i)));
		}
	}
	
	/**
	 * Calcule le numero du disque sur lequel doit etre stoque 
	 * le bloc de parite.
	 * 
	 * @param numStripe		Numero du stripe (/!\ demmare a 0 !)
	 * 
	 * @return int			Numero du disque (/!\ demmare a 0 !)
	 */
	public int parityIndex(int numStripe) {
		return ((- ((numStripe + 1) % nBlocks) + nBlocks) % nBlocks);
	}
	
	/**
	 * Ecrit une bande a une position donnee sur le systeme RAID 5.
	 * 
	 * @param pos			N* de la ligne ou ecrire la Stripe
	 */
	public void writeStripe(int pos) {
		/*	Calcul de l'indice du bloc de parite */
		int iParity = parityIndex(pos);
		
		for (int i = 0; i < nBlocks; i++) {
			if (i < iParity)			/*	Ecriture des blocs positionnees avant le bloc de parite */
				datas[i].writeBlock(pos, i);
			else if(i > iParity)		/*	Ecriture des blocs positionnees apres le bloc de parite */
				datas[i - 1].writeBlock(pos, i);
			else						/*	Ecriture du bloc de paritee */
				parity.writeBlock(pos, i);
		}	
	}
	
	/**
	 * Lit une bande a une position donnee sur le systeme RAID 5
	 * 
	 * @param pos           Nï¿½ de la ligne ou lire la Stripe
	 */
	public void readStripe(int pos) {
		/*	Calcul de l'indice du bloc de parite */
		int iParity = parityIndex(pos);
		
		for (int i = 0; i < nBlocks; i ++) {
			if (i < iParity) {			/*  Lecture des blocs positionnees avant le bloc de parite */
				if (!datas[i].readBlock(pos, i)) {
					datas[i].blockRepair(pos, i);
				}
			} else if (i > iParity)	{	/*  Lecture des blocs positionnees apres le bloc de parite */
				if (!datas[i - 1].readBlock(pos, i)) {
					datas[i - 1].blockRepair(pos, i);
				}
			} else {					/*  Lecture du bloc de parite */
				if (!parity.readBlock(pos, i)) {
					parity.blockRepair(pos, i);
				}
			}
		}
	}
	
	/**
	 * Ecrit sur le systeme RAID 5 le contenu du buffer
	 * a partir de la position pos.
	 * 
	 * @param bufLen		Taille du buffer en octet
	 * @param buffer		Buffer a ecrire
	 * @param pos			Position de depart pour l'ecriture sur le RAID (en octet)
	 * 
	 * @return int			Premier octet libre apres l'ecriture
	 */
	public static int writeChunk(int bufLen, byte[] buffer, int pos) {
		pos /= (nBlocks * RaidDefine.BLOCK_SIZE);
		
		for (int iBuf = 0; iBuf < bufLen;) {
			/*	Construction de la stripe */
			int iBlock;
			for (iBlock = 0; iBlock < nBlocks - 1; iBlock++) {
				for (int iByte = 0; iByte < RaidDefine.BLOCK_SIZE; iByte ++) {
					if (iBuf < bufLen) {
						datas[iBlock].setDataI(iByte, buffer[iBuf++]);
					} else {
						datas[iBlock].setDataI(iByte, '\0');
					}
				}
			}
		
			/*	Calcul de la parite */
			this.computeParity();
			
			/*	Ecriture de la Stripe sur le RAID */
			this.writeStripe(pos++);
		}
		
		return (pos * nBlocks * RaidDefine.BLOCK_SIZE);
	}
	
	/**
	 * Lit sur le système RAID 5 un nombre d'octets definis par bufLen
	 * et les stocke dans le buffer à partir de la position pos.
	 * 
	 * @param bufLen		Taille du buffer en octet (et nombre d'octets a lire)
	 * @param buffer		Buffer de stockage
	 * @param pos			Position de depart pour la lecture sur le RAID (en octet)
	 */
	public static void readChunk(int bufLen, byte[] buffer, int pos) {
		pos /= (nBlocks * RaidDefine.BLOCK_SIZE);
		
		for (int iBuf = 0; iBuf < bufLen;) {
			/*	Lecture d'une Stripe */
			this.readStripe(pos++);
			
			/*	Ecriture de la stripe lue dans le buffer */
			for (int iBlock = 0; iBlock < nBlocks - 1; iBlock ++) {
				for (int iByte = 0; iByte < RaidDefine.BLOCK_SIZE; iByte ++) {
					if (iBuf < bufLen) {
						buffer[iBuf] = datas[iBlock].getByteI(iByte);
					}
				}
			}
		}
	}
}
