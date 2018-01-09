#pragma once

#include "Configuration.h"
#include <algorithm>;

class Solver
{
public:
	Solver();
	~Solver();

	int Pvs(Configuration board, int depth, int alpha, int beta);
	//check for a winning condition in the first move of the start configuration
	int FirstSevenMove(Configuration configuration);
};

