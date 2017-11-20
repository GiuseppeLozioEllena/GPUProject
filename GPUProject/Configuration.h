#pragma once

#include <iostream>
#include <string>
#include <cstdint>
#include <cassert>

using namespace std;


class Configuration{
public:
	Configuration();
	~Configuration();

	static const int ROWS = 7;  // width of the board
	static const int COLUMNS = 6; // height of the board
	static const int MIN_SCORE = -(ROWS*COLUMNS) / 2 + 3;
	static const int MAX_SCORE = (ROWS*COLUMNS + 1) / 2 - 3;

	char board[COLUMNS][ROWS];

	void SetupBoard(string boardConfiguration);


private:
	char** GenerateConfiguration(char board[ROWS][COLUMNS], bool player);

};