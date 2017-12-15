#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "Configuration.h"
#include "Solver.h"
#include <ctime>

using namespace std;

int main(int argc, char** argv) {

	string line;
	clock_t start;
	double duration;
	ifstream testFile("configurations.txt");
	ofstream writeInFile;
	writeInFile.open("benchmarker.txt");

	Solver solver=Solver();

	if (testFile.is_open()) {
		int i = 0;
		while (getline(testFile, line)) {
			/*if (i != 53) {
				i++;
				continue;
			}*/
			start = clock();
			Configuration c = Configuration(line);
			writeInFile << c;
			int solution = solver.Pvs(c, 8, numeric_limits<int>::min(), numeric_limits<int>::max());
			if (!(solution % 2 == 0))
				solution = -solution;
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			writeInFile << "Configuration Number: " << i << endl;
			writeInFile << "Duration: " << duration << endl;
			writeInFile << "Number Of Turn Until Some Win: " << solution << endl;
			writeInFile << "Number Of Nodes Calculated: " << solver.getNodeCount() << endl;
			writeInFile << "________________________________" << endl;
			solver.ResetNodeCount();
			i++;
			if (i >250)
				break;
			c.deleteBoard();
		}
		testFile.close();
		writeInFile.close();
	}

	system("pause");
	return 0;
}