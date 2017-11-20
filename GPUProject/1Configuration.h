#pragma once

#include <string>
#include <cstdint>
#include <cassert>

class 1Configuration {
public:
	Configuration ();
	~Configuration ();

	static const int WIDTH = 7;  // width of the board
	static const int HEIGHT = 6; // height of the board
	static const int MIN_SCORE = -(WIDTH*HEIGHT) / 2 + 3;
	static const int MAX_SCORE = (WIDTH*HEIGHT + 1) / 2 - 3;

	int board[HEIGHT][WIDTH];


private:

};

Configuration ::Configuration () {
}

Configuration ::~Configuration () {
}