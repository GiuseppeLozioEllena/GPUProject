#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "Configuration.h"
#include "Solver.h"
#include <ctime>
#include <chrono>

using namespace std;

int main(int argc, char** argv) {

	clock_t total_start;
	string line;

	ifstream testFile("configurations.txt");
	ofstream writeInFileB;
	ofstream writeInFileT;
	writeInFileB.open("benchmarkerCpu.txt");
	writeInFileT.open("benchmarkerTimeCpu.txt");
	int solution = 0;
	Solver solver=Solver();

	if (testFile.is_open()) {
		int i = 0;
		total_start = clock();
		while (getline(testFile, line)) {
			/*if (i != 53) {
				i++;
				continue;
			}*/		
			Configuration c = Configuration(line);
			writeInFileB << c;
			auto s = chrono::steady_clock::now();
			solution = solver.FirstSevenMove(c);		
			if (solution == 0)
			{		
			solution = solver.Pvs(c, 10, numeric_limits<int>::min(), numeric_limits<int>::max());
			if (!(solution % 2 == 0))
				solution = -solution;
			}
			auto e = chrono::steady_clock::now();
			auto elapsed = chrono::duration_cast<std::chrono::milliseconds>(e - s);
			writeInFileT <<i<<" "<< elapsed.count()<<" ms"<< endl;
			writeInFileB << "Configuration Number: " << i << endl;
			writeInFileB << "Duration: " << elapsed.count()<<" ms"<< endl;
			writeInFileB << "Number Of Turn Until Some Win: " << solution << endl;
			//writeInFileB << "Number Of Nodes Calculated: " << solver.getNodeCount() << endl;
			writeInFileB << "________________________________" << endl;
			solver.ResetNodeCount();
			i++;
			if (i >250)
				break;
			c.deleteBoard();
		}
		testFile.close();
		writeInFileB.close();
		writeInFileT.close();
	}
	cout << ((clock() - total_start) / (double)CLOCKS_PER_SEC) << endl;
	system("pause");
	return 0;
}