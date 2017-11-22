#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>
#include <vector>

using namespace std;


class Configuration{

public:
	struct lastMove {
		int row; int column; char player;
		lastMove(int _row, int _column, char _player) {
			row = _row;
			column = _column;
			player = _player;
		}
	};

	Configuration(string boardConfiguration);
	Configuration(char** _board, lastMove _move);
	~Configuration();

	static const int ROWS = 6;  // width of the board
	static const int COLUMNS = 7; // height of the board
	static const int MIN_SCORE = -(ROWS*COLUMNS) / 2 + 3;
	static const int MAX_SCORE = (ROWS*COLUMNS + 1) / 2 - 3;

	

	friend ostream& operator<<(ostream& os, const Configuration& confg);
	bool isWinningMove(lastMove move);
	vector<lastMove> GenerateNextMoves(char player);

	char** getBoard();
	
private:
	char** board;
	void SetupBoard(string boardConfiguration);
	

};