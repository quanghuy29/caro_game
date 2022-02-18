#include "Room.h"
#include <iostream>

/* function createMatrix: create a matrix to save chess coordinates

Returns a mattrix with CHESS_WIDTH row and CHESS_HEIGHT column
*/

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

/* function Room: create new room

@param clientFirst, clientSecond: socket of two client

Returns new room
*/

Room::Room(SOCKET clientFirst, SOCKET clientSecond) {
	client1 = clientFirst;
	client2 = clientSecond;
	matrixRoom = createMatrix();
}

/* function updateMatrix: update chess coordinates with value 

@param coordinates: chess coordinates
@param value: value of chess coordinates
*/

void Room::updateMatrix(Coordinates coordinates, int value) {
	matrixRoom[coordinates.y][coordinates.x] = value;
	printf("\n");
	for (int i = 0; i < CHESS_HEIGHT; i++) {
		for (int j = 0; j < CHESS_WIDTH; j++) {
			printf("%d ", matrixRoom[i][j]);
		}
		printf("\n");
	}
}

/* function isEndGame: check if the game is over at chess coordinates

@param coordinates: chess coordinates
@param value: value of chess coordinates

Return 1 if win, 2 if draw and 0 if the game is not over
*/

int Room::isEndGame(Coordinates coordinates) {
	if (isEndByHorizontal(coordinates) ||
		isEndByVertical(coordinates) ||
		isEndByRightDiagonal(coordinates) ||
		isEndByLeftDiagonal(coordinates)) return 1;
	if (isEndByFullMatrix()) return 2;
	return 0;
}

/* function isEndByHorizontal: check if the game is over at chess coordinates by horizontal

@param coordinates: chess coordinates

Return true if the game is over and false if the game is not over
*/

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

/* function isEndByVertical: check if the game is over at chess coordinates by vertical

@param coordinates: chess coordinates

Return true if the game is over and false if the game is not over
*/

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

/* function isEndByRightDiagonal: check if the game is over at chess coordinates by right diagonal

@param coordinates: chess coordinates

Return true if the game is over and false if the game is not over
*/

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

/* function isEndByLeftDiagonal: check if the game is over at chess coordinates by left diagonal

@param coordinates: chess coordinates

Return true if the game is over and false if the game is not over
*/

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

/* function isEndByFullMatrix: check if the game is over at chess coordinates by full matrix

@param coordinates: chess coordinates

Return true if the game is over and false if the game is not over
*/

bool Room::isEndByFullMatrix() {
	for (int i = 0; i < CHESS_HEIGHT; i++) {
		for (int j = 0; j < CHESS_WIDTH; j++) {
			if (matrixRoom[i][j] == 0) return 0;
		}
	}
	return 1;
}