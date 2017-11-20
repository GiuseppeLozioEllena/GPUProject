#include "Configuration.h"

using namespace std;


Configuration::Configuration(string boardConfiguration) {
	Configuration::SetupBoard(boardConfiguration);

}

void Configuration::SetupBoard(string boardConfiguration) {
	int row = 0;
	int column = 0;
	for (int i = 0; i < boardConfiguration.length()/7; i++) {
		int muliply = i * 7;
		for (int j = 0; j < 7; j++) {
			board[i%6][j] = boardConfiguration[muliply+j];
		}
	}

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			cout << board[i][j];
		}
		cout << endl;
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
	int counter,i,j = 0;
	//check the column
	for (j = 0; j < COLUMNS; j++) {
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
	for (i = 0; i < ROWS; i++) {
		if (board[i][move.column] == move.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	//check right diagonal
	int edge;
	if (move.row == move.column) {
		i, j = 0;
		edge = ROWS;
	}
	else if (move.row > move.column) {
		i = 0;
		j = move.row - move.column;
		edge = COLUMNS;
	}
	else {
		i = move.column - move.row;
		j = 0;
		edge = ROWS;
	}
	if (fmaxf(i, j) < 4) {
		for (int k= 0; i < edge-(fmaxf(i, j)); i++) {
			if (board[i+k][j+k] == move.player) {
				counter++;
				if (counter >= 4)
					return true;
			}
			else
				counter = 0;
		}
	}
	//check left diagonal
	for (int i = 0; i < edge; i++) {
		if (board[i][move.column] == move.player) {
			counter++;
			if (counter >= 4)
				return true;
		}
		else
			counter = 0;
	}
	return false;
}

Configuration::~Configuration() {
}
