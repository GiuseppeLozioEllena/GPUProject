#include "Configuration.h"

using namespace std;


Configuration::Configuration(string boardConfiguration) {
	Configuration::SetupBoard(boardConfiguration);

}

Configuration::Configuration(char** _board, lastMove _move) {
	_board[_move.row][_move.column] = _move.player;

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

bool Configuration::isWinningMove(lastMove move) {
	int counter = 0;
	//check the column
	for (int j = 0; j < COLUMNS; j++) {
		if (board[move.row][j] == move.player) {
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
		if (board[i][move.column] == move.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	counter = 0;
	//check right diagonal
	for (int k= 0; (k+move.row < ROWS && k+move.column<COLUMNS ); k++) {
		if (board[move.row +k][move.column+k] == move.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	counter = 0;
	for (int k= 0; (move.row-k >= 0 && move.column -k >= 0 ); k++) {
		if (board[move.row -k][move.column-k] == move.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	//check left diagonal
	counter = 0;
	for (int k = 0; (k + move.row < ROWS && move.column-k >= 0); k++) {
		if (board[move.row + k][move.column - k] == move.player) {
			counter++;
			
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	counter = 0;
	for (int k = 0; (move.row - k >= 0 && k + move.column < COLUMNS); k++) {
		if (board[move.row - k][move.column + k] == move.player) {
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
vector<Configuration::lastMove> Configuration::GenerateNextMoves(char player) {
	
	vector<Configuration::lastMove> moves=vector<Configuration::lastMove>();
	for (int j = 0; j < COLUMNS; j++) {
		for (int i = ROWS -1; i >= 0; i--) {
			if (board[i][j] == '-') {
				moves.push_back(Configuration::lastMove(i, j, player));
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
	for (int i = 0; i < ROWS; i++) {
		_board[i] = new char[COLUMNS];
	}

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLUMNS; j++) {
			_board[i][j] = board[i][j];
		}
	}
	return _board;
}

Configuration::~Configuration() {
}
