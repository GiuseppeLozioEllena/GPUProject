#include <iostream>
#include <fstream>
#include <string>
#include "Configuration.h"

using namespace std;

int main(int argc, char** argv) {

	/*Configuration confg = Configuration("----x-----x--0--x---x-x-x--0-----------oox");
	cout << confg;
	cout << confg.isWinningMove(Configuration::lastMove(3, 1, 'x'))<< endl;*/

	string line;
	ifstream testFile("configurations.txt");
	if (testFile.is_open()) {
		/*getline(testFile, line);
		Configuration configuration(line);
		cout << configuration << endl;
		vector<Configuration::lastMove> moves = configuration.GenerateNextMoves('X');
		for each (Configuration::lastMove var in moves)
		{

			Configuration c = Configuration(configuration.getBoard(), var);
			cout << c << endl;
			cout << c.isWinningMove(var) << endl;
		}*/
		int i = 0;
		while (getline(testFile, line)) {
			Configuration configuration(line);
			vector<Configuration::lastMove> moves = configuration.GenerateNextMoves('0');
			for each (Configuration::lastMove var in moves) {
				
				Configuration c = Configuration(configuration.getBoard(), var);
				cout << c << endl;
				cout << c.isWinningMove(var) << endl;
			}
			cout << "________________________________"<< endl;
			i++;
			if (i > 100)
				break;
		}
		testFile.close();
	}

	system("pause");
	return 0;
}