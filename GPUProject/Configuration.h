#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>
#include <vector>

using namespace std;

struct lastMove {
		int row; int column; char player;
		lastMove(int _row, int _column, char _player) {
			row = _row;
			column = _column;
			player = _player;
		}
	};

class Configuration{

public:

	Configuration(string boardConfiguration);
	Configuration(char** _board, lastMove _move, int numMoves);
	~Configuration();

	static const int ROWS = 6;  // width of the board
	static const int COLUMNS = 7; // height of the board
	static const int MIN_SCORE = -(ROWS*COLUMNS) / 2 + 3;
	static const int MAX_SCORE = (ROWS*COLUMNS + 1) / 2 - 3;

	lastMove mLastmove= lastMove(-1, -1, 'n');

	friend ostream& operator<<(ostream& os, const Configuration& confg);
	bool isWinningMove(/*lastMove move*/);
	vector<lastMove> GenerateNextMoves(char player);
	void deleteBoard();
	char** getBoard();
	int getNMoves();
	void setNMoves(int moves);
	
private:
	char** board;

	int NumberOfMoves;
	
	void SetupBoard(string boardConfiguration);
	

};