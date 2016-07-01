#include "stdafx.h"
#include "CppUnitTest.h"
#include "Composant1.h"

using namespace cp1;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Composant1Test
{		
	TEST_CLASS(Composant1Test)
	{
	private:
		Composant1 c;
		string path = "C:/Users/Melkus/Desktop";
		string filename = "myfile.txt";

	public:

		TEST_METHOD(Should_open_and_close_file_when_method_openFile_and_closeFile_are_called)
		{
			Assert assert;
			assert.IsTrue(c.openFile(path, filename));
			assert.IsTrue(c.closeFile());
		}

		TEST_METHOD(Should_verify_blocks_when_method_control_is_called)
		{
			Assert assert;
			if (c.openFile(path, filename)) {
				assert.IsTrue(c.controlBlocks());
				c.closeFile();
			}
			
		}

		TEST_METHOD(Should_add_block_when_method_addBlock_is_called)
		{
			Assert assert;

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
			char tab4[64] = { 's','o','s','h','h','a','s','h','h','\0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','h','a','s','h','h','a','s','h','h','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','f','9','0','1','s' };

			char tab5[64] = { 'z','o','s','h','h','a','s','h','h','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0','1','2','h','a','s','h','h','a','s','h','h','0','1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','f','9','0','1','z' };

			Bloc bloc = *new Bloc(tab4, tab5, 2, 10, tx, txm);

			vector<Bloc> listeBloc;
			listeBloc.push_back(bloc);

			Bloc bloc2;

			if (c.openFile(path, filename)) {
				c.addBlocs(bloc, listeBloc);

				bloc2 = c.getBloc(1);

				for (int i = 0; i < 64; i++)
					assert.IsTrue(bloc2.hash[i] == bloc.hash[i]);

				for (int i = 0; i < 64; i++)
					assert.IsTrue(bloc2.previous_hash[i] == bloc.previous_hash[i]);

				assert.IsTrue(bloc2.num == bloc.num);
				assert.IsTrue(bloc2.nonce == bloc.nonce);

				c.closeFile();
			}

		}

	};
}