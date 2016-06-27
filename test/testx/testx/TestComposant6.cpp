// TestComposant6.cpp : définit le point d'entrée pour l'application console.
//

#include <windows.h>
#include "Composant6.h"
#include <string>
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	string keys = generateKeys();
	string publicKey = "";// A completer
	string privateKey = ""; // A completer
	string hash = ""; // A completer
	string signature = signData(hash, privateKey);
	cout << "Signature ==> " << signature << endl;
	cout << "Retour du valideur ==> " << checkSign(publicKey, signature, hash) << endl;

	Sleep(5000);
    return 0;
}

