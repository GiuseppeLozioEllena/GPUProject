#include "Configuration.h"

using namespace std;

Configuration::Configuration(string boardConfiguration) 
{
	Configuration::SetupBoard(boardConfiguration);

	mLastmove = lastMove(-1, -1, '0',0);
	for each (char c in boardConfiguration)
	{
		if (c == 'X' || c == '0')
			NumberOfMoves++;
	}
	NumberOfStartMoves = NumberOfMoves;
}

Configuration::Configuration(char** _board, lastMove _move, int numMoves,int startMoves) {
	_board[_move.row][_move.column] = _move.player;
	mLastmove.row = _move.row;
	mLastmove.column = _move.column;
	mLastmove.player = _move.player;
	NumberOfStartMoves = startMoves;
	NumberOfMoves = numMoves + 1;
	board = new char*[ROWS];
	for (int i = 0; i < ROWS; i++) {
		board[i] = new char[COLUMNS];
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			board[i][j] = _board[i][j];
		}

	}
}

void Configuration::SetupBoard(string boardConfiguration) {
	board = new char*[ROWS];
	for (int i = 0; i < ROWS; i++) {
		board[i] = new char[COLUMNS];
	}
	for (int i = 0; i < (boardConfiguration.length()/7); i++) {
		int muliply = i * 7;
		for (int j = 0; j < 7; j++) {
			board[i%6][j] = boardConfiguration[muliply+j];
		}
	}
}

bool Configuration::isWinningMove() {
	//cout << mLastmove.row << "   " << mLastmove.column << endl;
	if (mLastmove.row == -1)
		return false;
	int counter = 0;
	//check the column
	for (int j = 0; j < COLUMNS; j++) {
		if (board[mLastmove.row][j] == mLastmove.player) {
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
		if (board[i][mLastmove.column] == mLastmove.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	counter = 0;
	//check right diagonal
	for (int k= 0; (k+ mLastmove.row < ROWS && k+ mLastmove.column<COLUMNS ); k++) {
		if (board[mLastmove.row +k][mLastmove.column+k] == mLastmove.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	counter = 0;
	for (int k= 0; (mLastmove.row-k >= 0 && mLastmove.column -k >= 0 ); k++) {
		if (board[mLastmove.row -k][mLastmove.column-k] == mLastmove.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	//check left diagonal
	counter = 0;
	for (int k = 0; (k + mLastmove.row < ROWS && mLastmove.column-k >= 0); k++) {
		if (board[mLastmove.row + k][mLastmove.column - k] == mLastmove.player) {
			counter++;
			
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	counter = 0;
	for (int k = 0; (mLastmove.row - k >= 0 && k + mLastmove.column < COLUMNS); k++) {
		if (board[mLastmove.row - k][mLastmove.column + k] == mLastmove.player) {
			counter++;
			
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	return false;
}

int Configuration::ValutateMove(lastMove mLastmove,int pawnInARow) {
	int value = 0;
	if (mLastmove.row == -1)
		return value;

	int counter = 0;
	//check the column
	for (int j = (mLastmove.column - pawnInARow > 0 ? mLastmove.column - pawnInARow : 0); j < (mLastmove.column + pawnInARow < COLUMNS ? mLastmove.column + pawnInARow : COLUMNS); j++) {
		if (board[mLastmove.row][j] == mLastmove.player) {
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
		if (board[i][mLastmove.column] == mLastmove.player) {
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
	for (int k = 0; (k + mLastmove.row < ROWS && k + mLastmove.column<COLUMNS); k++) {
		if (board[mLastmove.row + k][mLastmove.column + k] == mLastmove.player) {
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
		if (board[mLastmove.row - k][mLastmove.column - k] == mLastmove.player) {
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
		if (board[mLastmove.row + k][mLastmove.column - k] == mLastmove.player) {
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
		if (board[mLastmove.row - k][mLastmove.column + k] == mLastmove.player) {
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
			if (board[i][j] != mLastmove.player &&board[i][j] != '-') {
				counter++;
				if (counter >= pawnInARow)
				{
					if (j - counter >= 1)
					{
						if (board[i][j-counter] == '-')
							value -= pawnInARow;

					}

					if (j  <COLUMNS - 1)
					{
						if (board[i][j+1] == '-')
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
			if (board[i][j] != mLastmove.player &&board[i][j] != '-') {
				counter++;
				if (counter >= pawnInARow) 
				{
					if (i - counter >= 1)
					{
						if(board[i - counter][j] == '-')
							value -= pawnInARow;
						
					}

					if (i  <ROWS-1)
					{
						if (board[i+1][j] == '-')
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
	
	vector<lastMove> moves=vector<lastMove>();
	for (int j = 0; j < COLUMNS; j++) {
		for (int i = ROWS -1; i >= 0; i--) {
			if (board[i][j] == '-') {
				moves.push_back(lastMove(i, j, player,0));
				break;
			}
		}
	}
	return SortNextMoves(moves);

}

vector<lastMove> Configuration::SortNextMoves(vector<lastMove> moves) {
	bool bDone = false;
	for (int i = 0; i < moves.size(); ++i) {
		board[moves[i].row][moves[i].column] = moves[i].player;
		moves[i].value = ValutateMove(moves[i],2) + ValutateMove(moves[i], 3);
		board[moves[i].row][moves[i].column] = '-';
	}

	while (!bDone) {
		bDone = true;
		for (int i = 0; i < moves.size()-1; ++i) {
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
	
	for (int i = 0; i < Configuration::ROWS; i++) {
		for (int j = 0; j < Configuration::COLUMNS; j++) {
			os << confg.board[i][j];
		}
		os << endl;
	}

	return os;
}

char** Configuration::getBoard() {
	char ** _board=new char*[ROWS];
	for (int i = 0; i < ROWS; i++) 
	{
		_board[i] = new char[COLUMNS];
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			_board[i][j] = board[i][j];
		}
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
	for (int i = 0; i < ROWS; i++) {
		delete[] board[i];
	}
	delete[] board;
}

Configuration::~Configuration() {
}
