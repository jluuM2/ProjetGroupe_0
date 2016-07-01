#pragma once
#ifndef COMPOSANT1_H
#define COMPOSANT1_H

#ifdef COMPOSANT1_EXPORTS
	#define COMPOSANT1_INTERFACE __declspec(dllexport)
#else
	#define COMPOSANT1_INTERFACE __declspec(dllimport)
#endif // COMPOSANT1_EXPORTS

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include "Composant5.h"
#include "Bloc.h"

using namespace std;
namespace cp1 {
	class Composant1 {
	private:
		FILE* fichier = nullptr;
		vector<Bloc> blocs;
		void parser(map<string, string> &hash, string prec, string chaine);
		string delimiter = "************************\n";
		string blocToString(Bloc bloc);
		Bloc stringToBloc(string chaine);
		void split(const string & s, const char * delim, vector<string>& v);

	public:
		// interface du composant1
		COMPOSANT1_INTERFACE Composant1();
		COMPOSANT1_INTERFACE bool openFile(string path, string fileName);
		COMPOSANT1_INTERFACE bool closeFile();
		COMPOSANT1_INTERFACE bool controlBlocks();
		COMPOSANT1_INTERFACE Bloc getBloc(int numeroBloc);
		COMPOSANT1_INTERFACE bool addBlocs(Bloc baseBloc, vector<Bloc> Blocs);
	};
}
#endif