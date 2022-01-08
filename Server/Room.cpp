#include "Room.h"
#include <iostream>

int** Room::createMatrix() {
	int** matrixChess = new int*[CHESS_HEIGHT];
	for (int i = 0; i <CHESS_HEIGHT; i++)
		matrixChess[i] = new int[CHESS_WIDTH];

	for (int i = 0; i < CHESS_HEIGHT; i++) {
		for (int j = 0; j < CHESS_WIDTH; j++) {
			matrixChess[i][j] = 0;
		}
	}
	return matrixChess;
}

Room::Room(int idRoom, SOCKET clientFirst, SOCKET clientSecond) {
	roomId = idRoom;
	client1 = clientFirst;
	client2 = clientSecond;
	matrixRoom = createMatrix();
}

void Room::addClient(SOCKET clientFirst, SOCKET clientSecond) {
	client1 = clientFirst;
	client2 = clientSecond;
}

void Room::updateMatrix(Coordinates coordinates, int value) {
	matrixRoom[coordinates.y][coordinates.x] = value;
	printf("%d ", 0);
	for (int j = 0; j < CHESS_WIDTH; j++) {
		printf("%d ", j);
	}
	printf("\n");
	for (int i = 0; i < CHESS_HEIGHT; i++) {
		printf("%d ", i);
		for (int j = 0; j < CHESS_WIDTH; j++) {
			printf("%d ", matrixRoom[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

bool Room::isEndGame(Coordinates coordinates) {
	return (isEndByHorizontal(coordinates) ||
		isEndByVertical(coordinates) ||
		isEndByRightDiagonal(coordinates) ||
		isEndByLeftDiagonal(coordinates));
}

bool Room::isEndByHorizontal(Coordinates coordinates) {
	int countLeft = 0;
	for (int i = coordinates.x; i >= 0; i--)
	{
		if (matrixRoom[coordinates.y][i] == matrixRoom[coordinates.y][coordinates.x])
		{
			countLeft++;
		}
		else
			break;
	}

	int countRight = 0;
	for (int i = coordinates.x + 1; i < CHESS_WIDTH ; i++)
	{
		if (matrixRoom[coordinates.y][i] == matrixRoom[coordinates.y][coordinates.x])
		{
			countRight++;
		}
		else
			break;
	}

	return countLeft + countRight == CHESS_WIN;
}

bool Room::isEndByVertical(Coordinates coordinates) {
	int countTop = 0;
	for (int i = coordinates.y; i >= 0; i--)
	{
		if (matrixRoom[i][coordinates.x] == matrixRoom[coordinates.y][coordinates.x])
		{
			countTop++;
		}
		else
			break;
	}

	int countBottom = 0;
	for (int i = coordinates.y + 1; i < CHESS_HEIGHT; i++)
	{
		if (matrixRoom[i][coordinates.x] == matrixRoom[coordinates.y][coordinates.x])
		{
			countBottom++;
		}
		else
			break;
	}

	return countTop + countBottom == CHESS_WIN;
}

bool Room::isEndByRightDiagonal(Coordinates coordinates) {
	int countTopRight = 0;
	for (int i = 0; i < CHESS_WIDTH - coordinates.x; i++)
	{
		if (coordinates.y - i < 0) break;
		if (matrixRoom[coordinates.y - i][coordinates.x + i] == matrixRoom[coordinates.y][coordinates.x])
		{
			countTopRight++;
		}
		else
			break;
	}

	int countBottomLeft = 0;
	for (int i = 1; i < CHESS_HEIGHT - coordinates.y; i++)
	{
		if (coordinates.x - i < 0) break;
		if (matrixRoom[coordinates.y + i][coordinates.x - i] == matrixRoom[coordinates.y][coordinates.x])
		{
			countBottomLeft++;
		}
		else
			break;
	}

	return countTopRight + countBottomLeft == CHESS_WIN;
}

bool Room::isEndByLeftDiagonal(Coordinates coordinates) {
	int countTopLeft = 0;
	for (int i = 0; i <= coordinates.y; i++)
	{
		if (coordinates.x - i < 0) break;
		if (matrixRoom[coordinates.y - i][coordinates.x - i] == matrixRoom[coordinates.y][coordinates.x])
		{
			countTopLeft++;
		}
		else
			break;
	}

	int countBottomRight = 0;
	for (int i = 1; i < CHESS_HEIGHT - coordinates.x; i++)
	{
		if (coordinates.y + i >= CHESS_WIDTH) break;
		if (matrixRoom[coordinates.y + i][coordinates.x + i] == matrixRoom[coordinates.y][coordinates.x])
		{
			countBottomRight++;
		}
		else
			break;
	}

	return countTopLeft + countBottomRight == CHESS_WIN;
}

void Room::exitRoom() {
	client1 = 0;
	client2 = 0;
	matrixRoom = createMatrix();
}