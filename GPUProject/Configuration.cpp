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
	int _value = 0;
	bool yourMove = false;
	if (mLastmove.row == -1)
		return value;

	int counter = 0;
	//check the rows
	for (int j = 0; j < COLUMNS; j++) {
		if (board[mLastmove.row*COLUMNS + j] == mLastmove.player) {
			counter++;
			if (j==mLastmove.column) {
				yourMove = true;
			}
			if (counter >= pawnInARow && yourMove) {
				if (counter == 4) {
					_value = counter+1;
					break;
				}
				_value = counter;
			}
		}
		else {
			counter = 0;
			yourMove = false;
		}
	}
	value += _value;
	_value = 0;
	counter = 0;
	//check the columns
	for (int i = mLastmove.row ; i < ROWS; i++) {
		if (board[i*COLUMNS + mLastmove.column] == mLastmove.player) {
			counter++;

			if (counter >= pawnInARow) {
				if (counter == 4) {
					_value = counter + 1;
					break;
				}
				_value = counter;
			}
		}
		else
			break;
	}
	
	value += _value;
	_value = 0;
	value += (mLastmove.row<4)?mLastmove.row:3;
	counter = 0;
	yourMove = false;
	//check right diagonal
	int ki = mLastmove.row;
	int ky = mLastmove.column;
	for (; (ki >= 0 && ky >= 0); ki--,ky--) {
	}
	if (!(ki >= 3 || ky >= 3)) {
		for (int k = 0; (k + mLastmove.row < ROWS && k + mLastmove.column < COLUMNS); k++) {
			if (board[(ki + k)*COLUMNS + (ky + k)] == mLastmove.player) {
				counter++;
				if ((ki + k) == mLastmove.row && (ky + k) == mLastmove.column) {
					yourMove = true;
				}
				if (counter >= pawnInARow && yourMove) {
					if (counter == 4) {
						_value = counter + 1;
						break;
					}
					_value = counter;
				}
			}
			else {
				counter = 0;
				yourMove = false;
			}
		}
	}
	value += _value;
	_value = 0;
	counter = 0;
	yourMove = false;
	//check left diagonal
	ki = mLastmove.row;
	ky = mLastmove.column;
	for (; (ki < ROWS && ky >= 0); ki++, ky--) {
	}
	if (!(ki < 3 || ky > 3)) {
		for (int k = 0; (mLastmove.row - k >= 0 && k + mLastmove.column < COLUMNS); k++) {
			if (board[(ki - k)*COLUMNS + (ky + k)] == mLastmove.player) {
				counter++;
				if ((ki - k) == mLastmove.row && (ky + k) == mLastmove.column) {
					yourMove = true;
				}
				if (counter >= pawnInARow && yourMove) {
					if (counter == 4) {
						_value = counter + 1;
						break;
					}
					_value = counter;
				}
			}
			else {
				counter = 0;
				yourMove = false;
			}
		}
	}
	value += _value;
	
	return value;
}

int Configuration::ValutateEnemyPositions(lastMove mLastmove, int pawnInARow) {
	int value = 0;
	if (mLastmove.row == -1)
		return value;

	int counter = 0;
	bool blocked = false;
	//check the rows
	for (int j = 0; j < COLUMNS; j++) {
		if ((board[mLastmove.row*COLUMNS + j] != mLastmove.player && board[mLastmove.row*COLUMNS + j] != '-') || j==mLastmove.column) {
			counter++;
			if (j == mLastmove.column)
				blocked = true;
			if (counter >= pawnInARow) {
				if (blocked) {
					//printf("%d, %d\n",mLastmove.row,mLastmove.column);
					value += pawnInARow;
					break;
				}
			}
		}
		else
			counter = 0;
	}

	//check the Columns
	counter = 0;
	blocked = false;
	for (int i = 0; i < ROWS; i++) {
		if ((board[i*COLUMNS + mLastmove.column] != mLastmove.player && board[i*COLUMNS + mLastmove.column] != '-') || i==mLastmove.row) {
			counter++;
			if (i == mLastmove.row)
				blocked = true;
			if (counter >= pawnInARow) {
				if (blocked) {
					value += pawnInARow;
					break;
				}
			}
		}
		else
			counter = 0;
	}

	//check right diagonal
	int ki = mLastmove.row;
	int ky = mLastmove.column;
	counter = 0;
	blocked = false;
	for (; (ki >= 0 && ky >= 0); ki--, ky--) {
	}
	if (!(ki >= 3 || ky >= 3)) {
		for (int k = 0; (k + mLastmove.row < ROWS && k + mLastmove.column < COLUMNS); k++) {
			if ((board[(ki + k)*COLUMNS + (ky + k)] != mLastmove.player && board[(ki + k)*COLUMNS + (ky + k)] != '-') || ((ki+k)==mLastmove.row && (ky+k)==mLastmove.column)) {
				counter++;
				if ((ki + k) == mLastmove.row && (ky + k) == mLastmove.column)
					blocked = true;
				if (counter >= pawnInARow) {
					if (blocked) {
						value += pawnInARow;
						break;
					}
				}
			}
			else
				counter = 0;
		}
	}

	//check left diagonal
	counter = 0;
	blocked = false;
	ki = mLastmove.row;
	ky = mLastmove.column;
	for (; (ki < ROWS && ky >= 0); ki++, ky--) {
	}
	if (!(ki < 3 || ky > 3)) {
		for (int k = 0; (mLastmove.row - k >= 0 && k + mLastmove.column < COLUMNS); k++) {
			if ((board[(ki - k)*COLUMNS + (ky + k)] != mLastmove.player && board[(ki - k)*COLUMNS + (ky + k)] != '-') || ((ki - k) == mLastmove.row && (ky + k) == mLastmove.column)) {
				counter++;
				if ((ki - k) == mLastmove.row && (ky + k) == mLastmove.column)
					blocked = true;
				if (counter >= pawnInARow) {
					if (blocked) {
						value += pawnInARow;
						break;
					}
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

	for (int i = 0; i < moves.size(); i++) {
		lastMove tmp = moves[i];
		moves[i] = moves[moves.size() / 2 + (1 - 2 * (i % 2))*(i + 1) / 2];
		moves[moves.size() / 2 + (1 - 2 * (i % 2))*(i + 1) / 2] = tmp;
	}


	for (int i = 0; i < moves.size(); ++i) {
		board[moves[i].row*COLUMNS + moves[i].column] = moves[i].player;
		moves[i].value = ValutateMove(moves[i], 2) + ValutateEnemyPositions(moves[i], 4);
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

	for (int i = 0; i < Configuration::ROWS; i++) {
		for (int j = 0; j < Configuration::COLUMNS; j++) {
			int idx = i*Configuration::COLUMNS + j;
			os << confg.board[idx];
		}
		os << endl;
	}
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
