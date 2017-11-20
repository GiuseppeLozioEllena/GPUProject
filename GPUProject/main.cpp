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

	Configuration confg = Configuration();
	confg.SetupBoard("0--0---0-X000X0X0X0X0X00XX00XXX0000XXXXXXX");


	system("pause");
	return 0;
}