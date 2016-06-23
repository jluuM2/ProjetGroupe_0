#pragma once
#ifndef _BLOC_H

//
// bloc.h  version 1.0
//
// projet blockchain M2IF 2016
//

#define KEY_SIZE 4 // taille en byte des cle (publique, privee)

class TXI
{
public:
	unsigned int nBloc;
	unsigned int nTx;
	unsigned int nUtxo;
	unsigned char signature[64];

	TXI(unsigned int nBloc, unsigned int nTx, unsigned int nUtxo, unsigned char signature[]) {
		this->nBloc = nBloc;
		this->nTx = nTx;
		this->nUtxo = nUtxo;
		for (int i = 0; i<64; i++) {
			this->signature[i] = signature[i];
		}
	}

	TXI() {};
};

class UTXO
{
public:
	float montant;
	unsigned char dest[KEY_SIZE];  //compte destinataire
	unsigned char hash[64];    // hash(nBloc,nTx,nUTXO,montant,destinataire) pour securisation de l'UTXO

	UTXO(float montant, unsigned char dest[], unsigned char hash[]) {
		this->montant = montant;

		for (int i = 0; i<KEY_SIZE; i++) {
			this->dest[i] = dest[i];
		}
		for (int i = 0; i<64; i++) {
			this->hash[i] = hash[i];
		}
	}

	UTXO() {};
};

class TX { // transaction standard
public:
	TXI txi[4];
	UTXO utxo[2];

	TX(TXI txi[], UTXO utxo[]) {
		for (int i = 0; i<4; i++) {
			this->txi[i] = txi[i];
		}
		for (int i = 0; i<2; i++) {
			this->utxo[i] = utxo[i];
		}
	}

	TX() {};
};

class TXM { // transaction du mineur
public:
	UTXO utxo[1];

	TXM(UTXO utxo[]) {
		this->utxo[0] = utxo[0];
	}

	TXM() {};
};

class Bloc
{
public:
	char hash[64]; // hash des autres champs
	char previous_hash[64];
	unsigned int nonce;
	int num; // numero du bloc, commence a zero
	TX tx1; //  transaction du bloc
	TXM tx0; // transaction du mineur (coinbase)
	Bloc() {}
	Bloc(char* hash, char* previous_hash, unsigned int nonce, int num, TX tx1, TXM tx0) {
		for (int i = 0; i<64; i++) {
			this->hash[i] = hash[i];
			this->previous_hash[i] = previous_hash[i];
		}
		this->nonce = nonce;
		this->num = num;
		this->tx1 = tx1;
		this->tx0 = tx0;
	}
};

#endif
