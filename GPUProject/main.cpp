#include <iostream>
#include <fstream>
#include <string>
#include "Configuration.h"

using namespace std;

int main(int argc, char** argv) {
	
	/*Solver solver;
	string line;

	ifstream testFile("haha.txt");
	if (testFile.is_open()) {
		while (getline(testFile, line)) {
			Configuration configuration;
			if(configuration)
		}
		testFile.close();
	}*/

	//Configuration confg = Configuration("-------------0------X------0-----XX----00X");
	Configuration confg = Configuration("----x-----x--0--x---x-x-x--0-----------oox");
	cout << confg.isWinningMove(Configuration::lastMove(3, 1, 'x'))<< endl;

	system("pause");
	return 0;
}