// Composant1.cpp : définit les fonctions exportées pour l'application DLL.
//

#include "Composant1.h"
#include <string>
#include <cstdio>
#include <fcntl.h>
#include <stdlib.h>
#include <process.h>
#include <fstream>
#include <iostream>
#include <iomanip>

namespace cp1 {

	Composant1::Composant1() {}

	string charToString(char tab[], unsigned int size) {
		std::stringstream ss;
		ss << std::hex;
		for (int i = 0; i<size; ++i)
			ss << std::setw(2) << std::setfill('0') << (int)tab[i];
		return ss.str();
	}
	string charToString(unsigned char* tab, unsigned int size) {
		std::stringstream ss;
		ss << std::hex;
		for (int i = 0; i<size; ++i)
			ss << std::setw(2) << std::setfill('0') << (int)tab[i];
		return ss.str();
	}

	void StringToChar(char* dest, string source, int size) {
		std::stringstream ss;
		ss << std::hex << source;

		string s = ss.str();
		for (int i = 0; i < size; i++) {
			dest[i] = s[i];
		}
	}

	void StringToChar(unsigned char* dest, string source, int size) {
		std::stringstream ss;
		ss << std::hex << source;

		string s = ss.str();
		for (int i = 0; i < size; i++) {
			dest[i] = s[i];
		}
	}

	bool Composant1::openFile(string path, string fileName) {
		if (this->fichier != nullptr) fclose(this->fichier);
		fopen_s(&this->fichier, (path + "/" + fileName).c_str(), "r+");

		string all = "";
		char line[2048];
		if (fichier) {
			while (fgets(line, 2048, fichier))
				all += line;
			
			vector<string> blocsString;
			split(all, this->delimiter.c_str(), blocsString);
			for (unsigned int i = 0; i< blocsString.size(); i++)
				this->blocs.push_back(stringToBloc(blocsString[i]));

			return true;
		}
		return false;
	}

	bool Composant1::closeFile() {
		if (fclose(this->fichier) == 0)
			return true;
		else
			return false;
	}

	// fonction qui remplie le vecteur donnee en parametre par la chaine en fonction du delimiteur
	void Composant1::split(const string &s, const char* delim, vector<string> & v) {
		char * next_token = NULL;
		char * dup = _strdup(s.c_str());
		char * token = strtok_s(dup, delim, &next_token);
		while (token != NULL) {
			v.push_back(string(token));
			token = strtok_s(NULL, delim, &next_token);
		}
		free(dup);
	}

	string Composant1::blocToString(Bloc bloc) {
		return "{hash:" + charToString(bloc.hash, 64) + "," +
			"previous_hash:" + charToString(bloc.previous_hash, 64) + "," +
			"nonce:" + to_string(bloc.nonce) + "," +
			"num:" + to_string(bloc.num) + "," +
			"tx1:{" +
			"txi[0]:{" +
			"nBloc:" + to_string(bloc.tx1.txi[0].nBloc) + "," +
			"nTx:" + to_string(bloc.tx1.txi[0].nTx) + "," +
			"nUtxo:" + to_string(bloc.tx1.txi[0].nUtxo) + "," +
			"signature:" + charToString(bloc.tx1.txi[0].signature, 64) + "}," +
			"txi[1]:{" +
			"nBloc:" + to_string(bloc.tx1.txi[1].nBloc) + "," +
			"nTx:" + to_string(bloc.tx1.txi[1].nTx) + "," +
			"nUtxo:" + to_string(bloc.tx1.txi[1].nUtxo) + "," +
			"signature:" + charToString(bloc.tx1.txi[1].signature, 64) + "}," +
			"txi[2]:{" +
			"nBloc:" + to_string(bloc.tx1.txi[2].nBloc) + "," +
			"nTx:" + to_string(bloc.tx1.txi[2].nTx) + "," +
			"nUtxo:" + to_string(bloc.tx1.txi[2].nUtxo) + "," +
			"signature:" + charToString(bloc.tx1.txi[2].signature, 64) + "}," +
			"txi[3]:{" +
			"nBloc:" + to_string(bloc.tx1.txi[3].nBloc) + "," +
			"nTx:" + to_string(bloc.tx1.txi[3].nTx) + "," +
			"nUtxo:" + to_string(bloc.tx1.txi[3].nUtxo) + "," +
			"signature:" + charToString(bloc.tx1.txi[3].signature, 64) + "}," +
			"utxo[0]:{" +
			"montant:" + to_string(bloc.tx1.utxo[0].montant) + "," +
			"dest:" + charToString(bloc.tx1.utxo[0].dest, 4) + "," +
			"hash:" + charToString(bloc.tx1.utxo[0].hash, 64) + "}," +
			"utxo[1]:{" +
			"montant:" + to_string(bloc.tx1.utxo[1].montant) + "," +
			"dest:" + charToString(bloc.tx1.utxo[1].dest, 4) + "," +
			"hash:" + charToString(bloc.tx1.utxo[1].hash, 64) + "}" +
			"}," +
			"tx0:{" +
			"utxo[0]:{" +
			"montant:" + to_string(bloc.tx0.utxo[0].montant) + "," +
			"dest:" + charToString(bloc.tx0.utxo[0].dest, 4) + "," +
			"hash:" + charToString(bloc.tx0.utxo[0].hash, 64) + "}" +
			"}" +
			"}";
	}

	Bloc Composant1::stringToBloc(string stringBloc) {
		int nbTXi = 4;
		int nbUTXo = 2;
		Bloc bloc = *new Bloc();
		map<string, string> mapBloc;
		parser(mapBloc, "", stringBloc);

		StringToChar(bloc.hash, mapBloc["hash"], 64);
		StringToChar(bloc.previous_hash, mapBloc["previous_hash"], 64);
		bloc.nonce = stoi(mapBloc["nonce"]);
		bloc.num = stoi(mapBloc["num"]);

		// ** TX1 **
		// -- TXi --
		for (int k = 0; k < nbTXi; k++) {
			bloc.tx1.txi[k].nBloc = stoi(mapBloc[("tx1.txi[" + to_string(k) + "].nBloc")]);
			bloc.tx1.txi[k].nTx = stoi(mapBloc["tx1.txi[" + to_string(k) + "].nTx"]);
			bloc.tx1.txi[k].nUtxo = stoi(mapBloc["tx1.txi[" + to_string(k) + "].nUtxo"]);
			StringToChar(bloc.tx1.txi[k].signature, mapBloc["tx1.txi[" + to_string(k) + "].signature"], 64);
		}

		// -- UTXo --
		for (int k = 0; k < nbUTXo; k++) {
			bloc.tx1.utxo[k].montant = stof(mapBloc["tx1.utxo[" + to_string(k) + "].montant"]);
			StringToChar(bloc.tx1.utxo[k].dest, mapBloc["tx1.utxo[" + to_string(k) + "].dest"], 4);
			StringToChar(bloc.tx1.utxo[k].hash, mapBloc["tx1.utxo[" + to_string(k) + "].hash"], 64);
		}

		// ** TXM **
		bloc.tx0.utxo[0].montant = stof(mapBloc["tx0.utxo[0].montant"]);
		StringToChar(bloc.tx0.utxo[0].dest, mapBloc["tx0.utxo[0].dest"], 4);
		StringToChar(bloc.tx0.utxo[0].hash, mapBloc["tx0.utxo[0].hash"], 64);

		return bloc;
	}

	void Composant1::parser(map<string, string> &mapBloc, string prec, string chaine) {
		chaine.erase(0, 1);
		chaine.erase(chaine.length() - 1, chaine.length());
		bool readAtt = true;
		bool rec = false;
		int cpt_open = 0;
		int cpt_close = 0;
		string attribut = "";
		string valeur = "";
		for (unsigned int i = 0; i<chaine.length(); i++) {
			if (readAtt) {
				if (chaine[i] == '{') cpt_open++;
				if (chaine[i] == ':') readAtt = false;
				else attribut += chaine[i];
			}
			else {
				if (chaine[i] == '}') cpt_close++;
				if (chaine[i] == '{') {
					cpt_open++;
					rec = true;
				}
				if ((chaine[i] == ',' && cpt_open == cpt_close)) {
					readAtt = true;
					if (rec) {
						mapBloc[prec + attribut] = valeur;
						parser(mapBloc, prec + attribut + ".", valeur);
					}
					else mapBloc[prec + attribut] = valeur;
					attribut = "";
					valeur = "";
					rec = false;
				}
				else valeur += chaine[i];
				if (i == chaine.length() - 1) {
					readAtt = true;
					if (rec) {
						mapBloc[prec + attribut] = valeur;
						parser(mapBloc, prec + attribut + ".", valeur);
					}
					else mapBloc[prec + attribut] = valeur;
					attribut = "";
					valeur = "";
					rec = false;
				}
			}
		}
	}

	bool Composant1::controlBlocks() {
		for (unsigned int i = 0; i<blocs.size(); i++) {
			if (!cp5::Composant5::nomFonctionComposant5(blocs[i])) {
				return false;
			}
		}
		return true;
	}

	bool Composant1::addBlocs(Bloc baseBloc, vector<Bloc> Blocs) {
		for (unsigned int i = 0; i< Blocs.size(); i++) {
			if (!cp5::Composant5::nomFonctionComposant5(Blocs[i]))
				return false;
		}
		for (unsigned int i = 0; i<Blocs.size(); i++) {
			blocs.push_back(Blocs[i]);
			fputs((blocToString(Blocs[i]) + '\n' + this->delimiter).c_str(), this->fichier);
		}
		return true;
	}

	Bloc Composant1::getBloc(int numero) {
		for (unsigned int i = 0; i<blocs.size(); i++) {
			if (blocs[i].num == numero)
				return blocs[i];
		}
		return *new Bloc();
	}
}