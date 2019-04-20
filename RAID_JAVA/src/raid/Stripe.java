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
	
	public Stripe() {
		nBlocks = VirtualDisk.NDISK;
		
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
					parity.setDataI(i, parity.getDataI(i) ^ datas[j++].getDataI(i));
		}
	}
	
	/**
	 * Calcule le numero du disque sur lequel doit être stoque 
	 * le bloc de parite.
	 * 
	 * @param numStripe		Numéro du stripe (/!\ démmare à 0 !)
	 * 
	 * @return int			Numéro du disque (/!\ démmare à 0 !)
	 */
	public int parityIndex(int numStripe) {
		return ((- ((numStripe + 1) % nBlocks) + nBlocks) % nBlocks);
	}
	
	/**
	 * Ecrit une bande à une position donnee sur le systeme RAID 5.
	 * 
	 * @param pos			N° de la ligne ou ecrire la Stripe
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
	 * Lit une bande à une position donnee sur le systeme RAID 5
	 * 
	 * @param pos           N° de la ligne ou lire la Stripe
	 */
	public void readStripe(int pos) {
		/*	Calcul de l'indice du bloc de parite */
		int iParity = parityIndex(pos);
		
		for (int i = 0; i < nBlocks; i ++) {
			if (i < iParity) {			/*  Lecture des blocs positionnees avant le bloc de parite */
				if (!datas[i].readBlock(pos, i))
					datas[i].blockRepair(pos, i);
			} else if (i > iParity)	{	/*  Lecture des blocs positionnees apres le bloc de parite */
				if (!datas[i - 1].readBlock(pos, i))
					datas[i - 1].blockRepair(pos, i);
			} else {					/*  Lecture du bloc de paritee */
				if (!parity.readBlock(pos, i))
					parity.blockRepair(pos, i);
			}
		}
	}
}



















