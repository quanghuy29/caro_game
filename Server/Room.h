#pragma once
#ifndef _ROOM_
#define _ROOM_

#pragma once
#include "server.h"
#define CHESS_WIDTH 8
#define CHESS_HEIGHT 10
#define CHESS_WIN 3

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

	int roomId;
	SOCKET client1;
	SOCKET client2;
	int** matrixRoom;

	Room(int idRoom, SOCKET clientFirst, SOCKET clientSecond);
	//Room(int idRoom);
	int ** createMatrix();
	void addClient(SOCKET clientFirst, SOCKET clientSecond);
	void updateMatrix(Coordinates coordinates, int value);
	int isEndGame(Coordinates coordinates);
	bool isEndByHorizontal(Coordinates coordinates);
	bool isEndByVertical(Coordinates coordinates);
	bool isEndByRightDiagonal(Coordinates coordinates);
	bool isEndByLeftDiagonal(Coordinates coordinates);
	bool isEndByFullMatrix();
	void exitRoom();

};

#endif