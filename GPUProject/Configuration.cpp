#include "Configuration.h"

using namespace std;

Configuration::Configuration(string boardConfiguration) {
	Configuration::SetupBoard(boardConfiguration);

	mLastmove = lastMove(-1, -1, 'X');
	for each (char c in boardConfiguration)
	{
		if (c == 'X' || c == '0')
			NumberOfMoves++;
	}
}

Configuration::Configuration(char** _board, lastMove _move, int numMoves) {
	_board[_move.row][_move.column] = _move.player;
	mLastmove.row = _move.row;
	mLastmove.column = _move.column;
	mLastmove.player = _move.player;
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
//questo deve essere il negamax(o minmax)
/*char** Configuration::GenerateConfiguration(char board[ROWS][COLUMNS], bool player) {

	for (int i = 0; i <ROWS; i++) {
		if (board[i][COLUMNS - 1] == '-') {

			for (int j = 0; j < COLUMNS; j++) {
				if (board[j][i] == '-') {
					if (player)
						board[i][j] = 'x';
					else
						board[i][j] = 'o';
					//minmax(board,i,j,move)
					break;
				}
			}
		}
	}
	return board;
}*/

bool Configuration::isWinningMove(/*lastMove move*/) {
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
//genera le sette mosse successive
vector<lastMove> Configuration::GenerateNextMoves(char player) {
	
	vector<lastMove> moves=vector<lastMove>();
	for (int j = 0; j < COLUMNS; j++) {
		for (int i = ROWS -1; i >= 0; i--) {
			if (board[i][j] == '-') {
				moves.push_back(lastMove(i, j, player));
				break;
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


void Configuration::deleteBoard()
{
	for (int i = 0; i < ROWS; i++) {
		delete[] board[i];
	}
	delete[] board;
	board = NULL;
}

Configuration::~Configuration() {
}
