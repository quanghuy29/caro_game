#pragma once
#ifndef _ROOM_
#define _ROOM_
#include "server.h"
#define CHESS_WIDTH 18
#define CHESS_HEIGHT 18
#define CHESS_WIN 5

struct Coordinates {
	int x;
	int y;
	Coordinates(int i, int j) {
		x = i;
		y = j;
	}
};

class Room {

public:

	SOCKET client1;
	SOCKET client2;
	int** matrixRoom;

	Room(SOCKET clientFirst, SOCKET clientSecond);
	int ** createMatrix();
	void updateMatrix(Coordinates coordinates, int value);
	int isEndGame(Coordinates coordinates);
	bool isEndByHorizontal(Coordinates coordinates);
	bool isEndByVertical(Coordinates coordinates);
	bool isEndByRightDiagonal(Coordinates coordinates);
	bool isEndByLeftDiagonal(Coordinates coordinates);
	bool isEndByFullMatrix();
};

#endif