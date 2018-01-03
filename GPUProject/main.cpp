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
	ofstream writeInFileB;
	ofstream writeInFileT;
	writeInFileB.open("benchmarkerCpu.txt");
	writeInFileT.open("benchmarkerTimeCpu.txt");
	int solution = 0;
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
			writeInFileB << c;
			solution = solver.FirstSevenMove(c);
		
			if (solution == 0)
			{		
			solution = solver.Pvs(c, 6, numeric_limits<int>::min(), numeric_limits<int>::max());
			if (!(solution % 2 == 0))
				solution = -solution;
			}
			duration = (clock() - start) / (double)CLOCKS_PER_SEC;
			writeInFileT <<i<<" "<<duration << endl;
			writeInFileB << "Configuration Number: " << i << endl;
			writeInFileB << "Duration: " << duration << endl;
			writeInFileB << "Number Of Turn Until Some Win: " << solution << endl;
			writeInFileB << "Number Of Nodes Calculated: " << solver.getNodeCount() << endl;
			writeInFileB << "________________________________" << endl;
			solver.ResetNodeCount();
			i++;
			if (i >500)
				break;
			c.deleteBoard();
		}
		testFile.close();
		writeInFileB.close();
		writeInFileT.close();
	}

	system("pause");
	return 0;
}