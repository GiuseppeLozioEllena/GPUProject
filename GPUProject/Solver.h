#pragma once

#include "Configuration.h"
#include <algorithm>;

class Solver
{
public:
	Solver();
	~Solver();

	int Pvs(Configuration board, int depth, int alpha, int beta);
	unsigned long long getNodeCount();
	void ResetNodeCount();
	int FirstSevenMove(Configuration configuration);

private:
	unsigned long long nodeCount;
};

