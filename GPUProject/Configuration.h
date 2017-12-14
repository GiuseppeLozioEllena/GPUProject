#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>
#include <vector>

using namespace std;

struct lastMove {
	int row; int column; char player; int value;
		lastMove(int _row, int _column, char _player, int _value) {
			row = _row;
			column = _column;
			player = _player;
			value = _value;
		}
	};

class Configuration{

public:

	Configuration(string boardConfiguration);
	Configuration(char* _board, lastMove _move, int numMoves,int startMoves);
	~Configuration();

	static const int ROWS = 6;  // width of the board
	static const int COLUMNS = 7; // height of the board
	static const int MIN_SCORE = -(ROWS*COLUMNS) / 2 + 3;
	static const int MAX_SCORE = (ROWS*COLUMNS + 1) / 2 - 3;

	lastMove mLastmove= lastMove(-1, -1, 'n',0);

	friend ostream& operator<<(ostream& os, const Configuration& confg);
	bool isWinningMove();
	vector<lastMove> GenerateNextMoves(char player);
	void deleteBoard();
	char* getBoard();
	int getNMoves();
	int NumberStartMoves();
	void setNMoves(int moves);
	
private:
	char* board;

	int NumberOfMoves;

	int NumberOfStartMoves;
	
	void SetupBoard(string boardConfiguration);
	int ValutateMove(lastMove mLastmove ,int pawnInARow);
	int ValutateEnemyPositions(lastMove mLastmove, int pawnInARow);
	vector<lastMove> Configuration::SortNextMoves(vector<lastMove> moves);

};