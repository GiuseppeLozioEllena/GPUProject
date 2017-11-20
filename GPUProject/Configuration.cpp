#include "Configuration.h"

using namespace std;


Configuration::Configuration() {


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

	/*for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			cout << board[i][j];
		}
		cout << endl;
	}*/
}
//questo deve essere il negamax(o minmax)
char** Configuration::GenerateConfiguration(char board[ROWS][COLUMNS], bool player) {

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

}

Configuration::~Configuration() {
}
