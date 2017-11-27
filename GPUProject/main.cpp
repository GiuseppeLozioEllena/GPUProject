#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include "Configuration.h"
#include "Solver.h"

using namespace std;

int main(int argc, char** argv) {

	string line;
	ifstream testFile("configurations.txt");

	Solver solver=Solver();

	if (testFile.is_open()) {
		int i = 0;
		while (getline(testFile, line)) {
				Configuration c = Configuration(line);
				cout << c << endl;
				int solution = solver.MinMax(c, 12, numeric_limits<int>::min(), numeric_limits<int>::max());
				cout << solution << endl;
				cout << solver.getNodeCount() << endl;
				solver.ResetNodeCount();
			cout << "________________________________"<< endl;
			i++;
			if (i > 20)
				break;
		}
		testFile.close();
	}

	system("pause");
	return 0;
}