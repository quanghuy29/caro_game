#include "server.h"
#include "database.h"
#include "Room.h"

void convertIntToChar(int value, char des[]) {
	for (int i = 3; i > -1; i--) {
		des[i] = value % 10 + 48;
		value = value / 10;
	}
	des[4] = 0;
}

/* function Receive: receive data of length lenData

@param s: socket use to receive data
@param dataIn: A pointer to a string to save data
@param dataOut: A pointer to a string to a complete message

Returns
0 on error
1 if message not process out of
2 if the message has been processed

*/

int Receive(Player s, char *dataIn, char *dataOut) {

	char dataRecv[BUFF_SIZE], buff[BUFF_MAX], buffReturn[BUFF_MAX], dataRight[BUFF_MAX];
	long ret = 0;
	long location = 0;

	strcpy(buff, dataIn);
	long idx = strlen(buff);

	if (idx > 0) {
		for (long i = 0; i < idx - 1; i++) {
			if ((buff[i] == '\r') && (buff[i + 1] == '\n')) {
				strncpy_s(buffReturn, buff + 0, i);
				i += 2;
				if (idx > i) {
					strncpy_s(dataRight, buff + i, idx - i);
					dataIn[0] = 0;
					strcat(dataIn, dataRight);
					idx = strlen(buff);
				}
				else
				{
					dataIn[0] = 0;
				}
				dataOut[0] = 0;
				strcpy(dataOut, buffReturn);
				return 1;
			}
		}
		location = idx;
	}

	while (1) {
		//receive data
		ret = recv(s.s, dataRecv, BUFF_SIZE, 0);
		if (ret == SOCKET_ERROR)
		{
			printf("Error: %d! Cannot receive message.", WSAGetLastError);
			return 0;
		}
		else if (ret == 0) {
			printf("Client disconnects.\n");
			return 0;
		}
		else {
			dataRecv[ret] = 0;
			for (long i = 0; i < ret; i++) {
				buff[idx++] = dataRecv[i];
			}
		}
		for (long i = location; i < idx - 1; i++) {
			if ((buff[i] == '\r') && (buff[i + 1] == '\n')) {
				dataOut[0] = 0;
				for (long j = 0; j < i; j++) {
					dataOut[j] = buff[j];
				}
				i += 2;
				if (idx > i) {
					dataIn[0] = 0;
					for (long j = 0; j < idx - i; j++) {
						dataIn[j] = buff[j + i];
					}
					return 1;
				}
				else
				{
					dataIn[0] = 0;
					return 2;
				}
			}
		}
	}

	return 0;
}

/* function Send: send data

@param s: a struct clientConnect have socket use to send data
@param dataIn: A pointer to a string to send data

Returns 0 on error and 1 on success

*/

int Send(Player s, char *opcode, char *dataIn) {
	long ret = 0, idx, lenData;
	char dataSend[BUFF_SIZE], lengthPay[5];

	lenData = strlen(dataIn);
	convertIntToChar(lenData, lengthPay);

	strcpy(dataSend, opcode);
	strcat(dataSend, lengthPay);
	strcat(dataSend, dataIn);
	strcat(dataSend, ENDING_DELIMITER);

	lenData = strlen(dataSend);
	long leftBytes = lenData;
	idx = 0;
	while (leftBytes > 0) {
		ret = send(s.s, &dataSend[idx], leftBytes, 0);
		if (ret == SOCKET_ERROR)
		{
			printf("Error: %d! Cannot send message.\n", WSAGetLastError);
			_getch();
			return 0;
		}
		idx += ret;
		leftBytes -= ret;
	}
	return 1;
}

/* function processDataReceive: process received data

@param dataIn: A pointer to a string to received data
@param filePath: A pointer to a string to file path

*/

void splitReceiveData(Player *player, char *dataIn) {
	char opcode[2], lengthPay[5], payload[BUFF_MAX];
	package mess;
	int lenData = 0;
	mess.opcode = dataIn[0];
	strncpy_s(mess.length, dataIn + 1, 4);
	lenData = atoi(mess.length);
	strncpy_s(mess.payload, dataIn + 5, lenData);
	handleDataReceive(player, mess);
}

void handleDataReceive(Player *player, package mess) {
	switch (mess.opcode)
	{
	case '1':
		login(player, mess);
		break;
	case '2':
		break;
	case '3':
		break;
	case '4':
		break;
	case '5':
		break;
	case '6':
		break;
	case '9':
		logout(player, mess);
		break;
	default:
		break;
	}
}

int login(Player *player, package mess) {
	if (player->isLogin == 1) return 13;
	char *username, *password;
	username = strtok(mess.payload, " ");
	password = strtok(NULL, "\n");
	int ret = userLogin(username, password);
	if (ret == 10) {
		player->isLogin = 1;
		getUser(username, &(player->playerinfo));
	}
	return 1;
	//return userLogin(username, password);
}

int logout(Player *player, package mess) {
	if (player->isLogin == 1) {
		player->isLogin = 0;
		updateUserIsFree(player, 1);
		updateUserStatus(player->playerinfo.username, 0);
		return 90;
	}
	else return 91;
}
