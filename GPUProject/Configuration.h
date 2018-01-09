#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>
#include <vector>

using namespace std;
//saves the last move of the current player
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

	static const int ROWS = 6;
	static const int COLUMNS = 7;
	static const int MIN_SCORE = -(ROWS*COLUMNS) / 2 + 3;
	static const int MAX_SCORE = (ROWS*COLUMNS + 1) / 2 - 3;

	lastMove mLastmove= lastMove(-1, -1, 'n',0);

	friend ostream& operator<<(ostream& os, const Configuration& confg);
	//Check if the last move is a winning move for the current player
	bool isWinningMove();
	//Return an ordered array with all the possible moves of the next turn of the game
	vector<lastMove> GenerateNextMoves(char player);
	void deleteBoard();
	char* getBoard();
	//return the number of moves played from the start configuration
	int getNMoves();
	void setNMoves(int moves);
	int NumberStartMoves();
	
private:
	char* board;

	int NumberOfMoves;

	int NumberOfStartMoves;
	
	void SetupBoard(string boardConfiguration);
	//assing a numeric value to valutate the goodness of a move checking the adjacent player paws
	int ValutateMove(lastMove mLastmove ,int pawnInARow);
	//assing a numeric value to valutate the goodness of a move checking the adjacent enemy paws
	int ValutateEnemyPositions(lastMove mLastmove, int pawnInARow);
	//sort the moves in non crescent order based on the value of the moves
	vector<lastMove> Configuration::SortNextMoves(vector<lastMove> moves);

};