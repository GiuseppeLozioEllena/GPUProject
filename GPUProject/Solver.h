#pragma once

#include "Configuration.h"
#include <algorithm>;

class Solver
{
public:
	Solver();
	~Solver();

	int MinMax(Configuration board, int alpha, int beta);
	unsigned long long getNodeCount();
	void ResetNodeCount();

private:
	unsigned long long nodeCount;
};

