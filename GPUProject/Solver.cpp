#include "Solver.h"



Solver::Solver() {}
int Solver::FirstSevenMove(Configuration configuration)
{
	char nextPlayer = configuration.mLastmove.player == 'X' ? '0' : 'X';
	vector<lastMove> moves = configuration.GenerateNextMoves(nextPlayer);
	for (int i = 0; i < moves.size(); i++) 
	{
		
		Configuration c = Configuration(configuration.getBoard(), moves[i], configuration.getNMoves(), configuration.NumberStartMoves());
		bool isWinningMove = c.isWinningMove();
		if ((isWinningMove && c.mLastmove.player == '0')) {
			return -1;
		}

		if ((isWinningMove && c.mLastmove.player == 'X')) {
			return 1;
		}
	}
	return 0;
}

int Solver::Pvs(Configuration configuration,int depth, int alpha, int beta) 
{
	bool isWinningMove = configuration.isWinningMove();
	if ((isWinningMove && configuration.mLastmove.player == '0') || depth == 0) {
		return -(configuration.getNMoves() - configuration.NumberStartMoves());
	}

	if ((isWinningMove && configuration.mLastmove.player == 'X') || depth == 0) {
		return (configuration.getNMoves() - configuration.NumberStartMoves());
	}
	
	if (configuration.getNMoves() > Configuration::ROWS*Configuration::COLUMNS-1)
		return 0;

	char nextPlayer = configuration.mLastmove.player == 'X' ? '0' : 'X';
	vector<lastMove> moves = configuration.GenerateNextMoves(nextPlayer);
	
	for (int i = 0;i<moves.size();i++) {
		int	score;
		Configuration c = Configuration(configuration.getBoard(), moves[i], configuration.getNMoves(),configuration.NumberStartMoves());
		if (i == 0) {
			score = -Pvs(c, depth - 1, -beta, -alpha);
		}
		else
		{
			score = -Pvs(c, depth - 1, (-alpha - 1), -alpha);
			if (alpha < score < beta)
				score = -Pvs(c, depth - 1, -beta, -score);
		}

		alpha = max(alpha, score);
		if (alpha >= beta) {
			c.deleteBoard();
			break;
		}
		c.deleteBoard();
	}
	moves.clear();
	moves.shrink_to_fit();

	return alpha;
}

Solver::~Solver()
{
}
