#include "Solver.h"



Solver::Solver()
{
	nodeCount=0;
}

int Solver::MinMax(Configuration configuration, int alpha, int beta) {
	//cout << configuration << endl;
	nodeCount++;
	if (configuration.isWinningMove() && configuration.mLastmove.player == '0')
		return -(Configuration::ROWS*Configuration::COLUMNS - configuration.getNMoves()) / 2;

	if (configuration.isWinningMove() && configuration.mLastmove.player == 'X') {
		cout <<"Winner   "<< (Configuration::ROWS*Configuration::COLUMNS - configuration.getNMoves()) / 2 <<  endl;
		return (Configuration::ROWS*Configuration::COLUMNS - configuration.getNMoves()) / 2;
		
	}

	if (configuration.getNMoves() > Configuration::ROWS*Configuration::COLUMNS-1) // check for draw game
		return 0;

	//cout << "Before Pruning" << endl;
	/*int min = -(Configuration::ROWS*Configuration::COLUMNS - 2 - configuration.getNMoves()) / 2;	// lower bound of score as opponent cannot win next move
	
	if (alpha < min) {
		alpha = min;                     // there is no need to keep beta above our max possible score.
		if (alpha >= beta) 
			return alpha;  // prune the exploration if the [alpha;beta] window is empty.
	}

	int max = (Configuration::ROWS*Configuration::COLUMNS - 1 - configuration.getNMoves()) / 2;	// upper bound of our score as we cannot win immediately
	if (beta > max) {
		beta = max;                     // there is no need to keep beta above our max possible score.
		if (alpha >= beta) 
			return beta;  // prune the exploration if the [alpha;beta] window is empty.
	}*/

	char nextPlayer = configuration.mLastmove.player == 'X' ? '0' : 'X';
	vector<lastMove> moves = configuration.GenerateNextMoves(nextPlayer);

	if (nodeCount==1 || configuration.mLastmove.player=='X') {
		int	score = numeric_limits<int>::min();
		for each (lastMove move in moves) {
			Configuration c = Configuration(configuration.getBoard(), move, configuration.getNMoves());
			score = max(score,MinMax(c, alpha, beta));

			if (score > alpha)
				alpha = score;  // prune the exploration if we find a possible move better than what we were looking for.
			if (beta <= alpha)
				break;
		}
		return score;
	}
	if (configuration.mLastmove.player == '0') {
		int	score = numeric_limits<int>::max();
		for each (lastMove move in moves) {
			Configuration c = Configuration(configuration.getBoard(), move, configuration.getNMoves());
			score = min(score, MinMax(c, alpha, beta));
			cout << "score" << score << endl;
			if (score <= beta)
				beta = score;  // prune the exploration if we find a possible move better than what we were looking for.
			if (beta <= alpha)
				break;
		}
		return score;
	}
}

unsigned long long Solver::getNodeCount()
{
	return nodeCount;
}

void Solver::ResetNodeCount()
{
	nodeCount=0;
}

Solver::~Solver()
{
}
