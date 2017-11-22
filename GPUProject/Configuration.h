#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>

using namespace std;


class Configuration{
public:
	Configuration(string boardConfiguration);
	~Configuration();

	static const int ROWS = 7;  // width of the board
	static const int COLUMNS = 6; // height of the board
	static const int MIN_SCORE = -(ROWS*COLUMNS) / 2 + 3;
	static const int MAX_SCORE = (ROWS*COLUMNS + 1) / 2 - 3;

	char board[COLUMNS][ROWS];

	

	struct lastMove {
		int row; int column; char player;
		lastMove(int _row,int _column,char _player) {
			row = _row;
			column = _column;
			player = _player;
		}
		 };
	bool isWinningMove(lastMove move);

private:
	//char** GenerateConfiguration(char board[ROWS][COLUMNS], bool player);
	void SetupBoard(string boardConfiguration);
	

};