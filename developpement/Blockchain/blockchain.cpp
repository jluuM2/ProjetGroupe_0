//// Blockchain.cpp : définit le point d'entrée pour l'application console.
////

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "Composant1.h"

using namespace cp1;
using namespace std;

int main(int argc, const char * argv[]) {
	Composant1 c;
	
	unsigned char tab[64] = { 's','o','s','h','h','a','s','h','h','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','h','a','s','h','h','a','s','h','h','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','f','9','0','1','s' };
	TXI txi[4];
	txi[0] = *new TXI(3, 5, 7, tab);
	txi[1] = *new TXI(4, 6, 8, tab);
	txi[2] = *new TXI(5, 7, 9, tab);
	txi[3] = *new TXI(6, 8, 0, tab);

	unsigned char tab3[64] = { 's','o','s','h','h','a','s','h','h','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','h','a','s','h','h','a','s','h','h','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','f','9','0','1','s' };
	unsigned char tab2[4] = { 'a','b','c','d' };
	UTXO utxo[2];
	utxo[0] = *new UTXO(100, tab2, tab3);
	utxo[1] = *new UTXO(230, tab2, tab3);
	TX tx = *new TX(txi, utxo);
	UTXO utxo2[1];
	utxo2[0] = *new UTXO(1000, tab2, tab3);
	TXM txm = *new TXM(utxo2);
	char tab4[64] = { 's','o','s','h','h','a','s','h','h','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','h','a','s','h','h','a','s','h','h','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','f','9','0','1','s' };

	char tab5[64] = { 'z','o','s','h','h','a','s','h','h','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','h','a','s','h','h','a','s','h','h','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','f','9','0','1','z' };

	Bloc bloc = *new Bloc(tab4, tab5, 2, 1, tx, txm);

	vector<Bloc> b;
	b.push_back(bloc);
	b.push_back(bloc);

	if (c.openFile("C:/Users/Melkus/Desktop", "myfile.txt")) {
		c.addBlocs(bloc, b);
		c.closeFile();
	}

	return 0;
}
