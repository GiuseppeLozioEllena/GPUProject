#include "Configuration.h"

using namespace std;

Configuration::Configuration(string boardConfiguration)
{
	Configuration::SetupBoard(boardConfiguration);

	mLastmove = lastMove(-1, -1, '0', 0);
	for each (char c in boardConfiguration)
	{
		if (c == 'X' || c == '0')
			NumberOfMoves++;
	}
	NumberOfStartMoves = NumberOfMoves;
}

Configuration::Configuration(char* _board, lastMove _move, int numMoves, int startMoves) {
	_board[_move.row*COLUMNS+_move.column] = _move.player;
	mLastmove.row = _move.row;
	mLastmove.column = _move.column;
	mLastmove.player = _move.player;
	NumberOfStartMoves = startMoves;
	NumberOfMoves = numMoves + 1;
	board = new char[ROWS*COLUMNS];
	for (int i = 0; i < ROWS*COLUMNS; i++) {
			board[i] = _board[i];
	}
}

void Configuration::SetupBoard(string boardConfiguration) {
	board = new char[ROWS*COLUMNS];
	for (int i = 0; i <boardConfiguration.length(); i++) {
			board[i] = boardConfiguration[i];
	}
}

bool Configuration::isWinningMove() {
	//cout << mLastmove.row << "   " << mLastmove.column << endl;
	if (mLastmove.row == -1)
		return false;
	int counter = 0;
	//check the column
	for (int j = 0; j < COLUMNS; j++) {
		if (board[mLastmove.row*COLUMNS+j] == mLastmove.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	counter = 0;
	//check the row
	for (int i = 0; i < ROWS; i++) {
		if (board[i*COLUMNS+mLastmove.column] == mLastmove.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	counter = 0;
	//check right diagonal
	for (int k = 0; (k + mLastmove.row < ROWS && k + mLastmove.column < COLUMNS); k++) {
		if (board[(mLastmove.row + k)*COLUMNS + (mLastmove.column + k)] == mLastmove.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	counter = 0;
	for (int k = 0; (mLastmove.row - k >= 0 && mLastmove.column - k >= 0); k++) {
		if (board[(mLastmove.row - k)*COLUMNS + (mLastmove.column - k)] == mLastmove.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	//check left diagonal
	counter = 0;
	for (int k = 0; (k + mLastmove.row < ROWS && mLastmove.column - k >= 0); k++) {
		if (board[(mLastmove.row + k)*COLUMNS + (mLastmove.column - k)] == mLastmove.player) {
			counter++;

			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	counter = 0;
	for (int k = 0; (mLastmove.row - k >= 0 && k + mLastmove.column < COLUMNS); k++) {
		if (board[(mLastmove.row - k)*COLUMNS + (mLastmove.column + k)] == mLastmove.player) {
			counter++;

			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	return false;
}

int Configuration::ValutateMove(lastMove mLastmove, int pawnInARow) {
	int value = 0;
	if (mLastmove.row == -1)
		return value;

	int counter = 0;
	//check the column
	for (int j = (mLastmove.column - pawnInARow > 0 ? mLastmove.column - pawnInARow : 0); j < (mLastmove.column + pawnInARow < COLUMNS ? mLastmove.column + pawnInARow : COLUMNS); j++) {
		if (board[mLastmove.row*COLUMNS + j] == mLastmove.player) {
			counter++;
			if (counter >= pawnInARow) {
				value += pawnInARow;
				break;
			}
		}
		else
			counter = 0;
	}
	counter = 0;
	//check the row
	for (int i = (mLastmove.row - pawnInARow > 0 ? mLastmove.row - pawnInARow : 0); i < (mLastmove.row + pawnInARow < ROWS ? mLastmove.row + pawnInARow : ROWS); i++) {
		if (board[i*COLUMNS + mLastmove.column] == mLastmove.player) {
			counter++;
			if (counter >= pawnInARow) {
				value += pawnInARow;
				break;
			}
		}
		else
			counter = 0;
	}
	counter = 0;
	//check right diagonal
	for (int k = 0; (k + mLastmove.row < ROWS && k + mLastmove.column < COLUMNS); k++) {
		if (board[(mLastmove.row + k)*COLUMNS + (mLastmove.column + k)] == mLastmove.player) {
			counter++;
			if (counter >= pawnInARow) {
				value += pawnInARow;
				break;
			}
		}
		else
			counter = 0;
	}
	counter = 0;
	for (int k = 0; (mLastmove.row - k >= 0 && mLastmove.column - k >= 0); k++) {
		if (board[(mLastmove.row - k)*COLUMNS + (mLastmove.column - k)] == mLastmove.player) {
			counter++;
			if (counter >= pawnInARow) {
				value += pawnInARow;
				break;
			}
		}
		else
			counter = 0;
	}
	//check left diagonal
	counter = 0;
	for (int k = 0; (k + mLastmove.row < ROWS && mLastmove.column - k >= 0); k++) {
		if (board[(mLastmove.row + k)*COLUMNS + (mLastmove.column - k)] == mLastmove.player) {
			counter++;
			if (counter >= pawnInARow) {
				value += pawnInARow;
				break;
			}
		}
		else
			counter = 0;
	}
	counter = 0;
	for (int k = 0; (mLastmove.row - k >= 0 && k + mLastmove.column < COLUMNS); k++) {
		if (board[(mLastmove.row - k)*COLUMNS + (mLastmove.column + k)] == mLastmove.player) {
			counter++;
			if (counter >= pawnInARow) {
				value += pawnInARow;
				break;
			}
		}
		else
			counter = 0;
	}

	for (int i = 0; i < ROWS; i++) {
		counter = 0;
		for (int j = 0; j < COLUMNS; j++) {
			if (board[i*COLUMNS + j] != mLastmove.player &&board[i*COLUMNS + j] != '-') {
				counter++;
				if (counter >= pawnInARow) {
					if (j - counter >= 1) {
						if (board[i*COLUMNS + (j - counter)] == '-')
							value -= pawnInARow;
					}
					break;
				}
			}
			else
				counter = 0;
		}
	}

	for (int j = 0; j < COLUMNS; j++) {
		counter = 0;
		for (int i = 0; i < ROWS; i++) {
			if (board[i*COLUMNS + j] != mLastmove.player &&board[i*COLUMNS + j] != '-') {
				counter++;
				if (counter >= pawnInARow) {
					if (i - counter >= 1) {
						if (board[(i - counter)*COLUMNS + j] == '-')
							value -= pawnInARow;
					}
					if (i < ROWS - 1) {
						if (board[(i + 1)*COLUMNS + j] == '-')
							value -= pawnInARow;
					}
					break;
				}
			}
			else
				counter = 0;
		}
	}
	return value;
}

//genera le sette mosse successive
vector<lastMove> Configuration::GenerateNextMoves(char player) {

	vector<lastMove> moves = vector<lastMove>();
	int idx = 0;
	for (int j = 0; j < COLUMNS; j++) {
		for (int i = ROWS - 1; i >= 0; i--) {
			idx = i*COLUMNS+j;
			if (board[idx] == '-') {
				moves.push_back(lastMove(i, j, player, 0));
				break;
			}
		}
	}
	return SortNextMoves(moves);

}

vector<lastMove> Configuration::SortNextMoves(vector<lastMove> moves) {
	bool bDone = false;
	for (int i = 0; i < moves.size(); ++i) {
		board[moves[i].row*COLUMNS + moves[i].column] = moves[i].player;
		moves[i].value = ValutateMove(moves[i], 2) + ValutateMove(moves[i], 3);
		board[moves[i].row*COLUMNS + moves[i].column] = '-';
	}

	while (!bDone) {
		bDone = true;
		for (int i = 0; i < moves.size() - 1; ++i) {
			if (moves[i].value < moves[i + 1].value) {
				lastMove tmp = moves[i];
				moves[i] = moves[i + 1];
				moves[i + 1] = tmp;
				bDone = false;
			}
		}
	}
	return moves;
}

ostream& operator<<(ostream& os, const Configuration& confg) {

	for (int i = 0; i < Configuration::ROWS*Configuration::COLUMNS; i++) {
		os << confg.board[i];
		if(i%7==0 && i!=0)
			os << endl;
	}
	os << endl;
	return os;
}

char* Configuration::getBoard() {
	char * _board = new char[ROWS*COLUMNS];

	for (int i = 0; i < ROWS*COLUMNS; i++) {
		_board[i] = board[i];
	}
	return _board;
}

int Configuration::getNMoves() {
	return NumberOfMoves;
}

void Configuration::setNMoves(int moves) {
	NumberOfMoves = moves;
}

int Configuration::NumberStartMoves()
{
	return NumberOfStartMoves;
}


void Configuration::deleteBoard()
{

	delete[] board;
}

Configuration::~Configuration() {
}
