#include "server.h"
#include "database.h"
#include "Room.h"

vector<Room> listRooms;
vector<UserLogin> listUserLogin;

/* function convertIntToChar: convert int to array char

@param value: number want to convert
@param des: array char contains results
*/

void convertIntToChar(int value, char des[]) {
	for (int i = 3; i > -1; i--) {
		des[i] = value % 10 + 48;
		value = value / 10;
	}
	des[4] = 0;
}

/* function Receive: receive data from player

@param s: a truct player have socket use to receive data
@param dataIn: A pointer to a string to save data
@param mess: A pointer to a struct package to a complete message

Returns
0 on error
1 if message not process out of
2 if the message has been processed
*/

int Receive(Player s, char *dataIn, package *mess) {

	char dataRecv[BUFF_SIZE], buff[BUFF_MAX], buffReturn[BUFF_MAX], length[5];
	long ret = 0;
	long lenData = 0;

	strcpy(buff, dataIn);
	long idx = strlen(buff);
	//return 0;
	if (idx > 4) {
		strncpy_s(length, dataIn + 1, 4);
		lenData = atoi(length);
		if (idx - 5 >= lenData) {
			mess->opcode = buff[0];
			strcat_s(mess->length, length);
			strncpy_s(mess->payload, buff + 5, lenData);
			if (idx - 5 == lenData) {
				dataIn[0] = 0;
				return 2;
			}
			else
			{
				dataIn[0] = 0;
				long location = lenData + 5;
				for (long j = 0; j < idx - location; j++) {
					dataIn[j] = buff[j + location];
				}
				return 1;
			}
		}
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
			strcat_s(buff, dataRecv);
		}
		idx = strlen(buff);
		strncpy_s(length, buff + 1, 4);
		lenData = atoi(length);
		if (idx - 5 >= lenData) {
			mess->opcode = buff[0];
			strcat_s(mess->length, length);
			strncpy_s(mess->payload, buff + 5, lenData);
			if (idx - 5 == lenData) {
				dataIn[0] = 0;
				return 2;
			}
			else
			{
				dataIn[0] = 0;
				long location = lenData + 5;
				for (long j = 0; j < idx - location; j++) {
					dataIn[j] = buff[j + location];
				}
				return 1;
			}
		}
	}
	return 0;
}

/* function Send: send data

@param s: socket use to send data
@param opcode: A pointer to a string opcode
@param dataIn: A pointer to a string data to send 

Returns 0 on error and 1 on success
*/

int Send(SOCKET s, char *opcode, char *dataIn) {
	long ret = 0, idx, lenData;
	char dataSend[BUFF_SIZE], lengthPay[5];

	lenData = strlen(dataIn);
	convertIntToChar(lenData, lengthPay);

	strcpy(dataSend, opcode);
	strcat(dataSend, lengthPay);
	strcat(dataSend, dataIn);

	lenData = strlen(dataSend);
	long leftBytes = lenData;
	idx = 0;
	while (leftBytes > 0) {
		ret = send(s, &dataSend[idx], leftBytes, 0);
		if (ret == SOCKET_ERROR)
		{
			printf("Error: %d! Cannot send message.\n", WSAGetLastError);
			return 0;
		}
		idx += ret;
		leftBytes -= ret;
	}
	return 1;
}

/* function handleDataReceive: handle data receive

@param player: A pointer to a struct player
@param mess: A pointer to a struct package constain data 
*/

void handleDataReceive(Player *player, package mess) {
	char payload[BUFF_SIZE];
	char opcode[2];
	opcode[0] = mess.opcode;
	opcode[1] = 0;
	switch (mess.opcode)
	{
	case '0':
		cancelChallenge(player);
		break;
	case '1':
		login(player, mess);
		break;
	case '2':
		Send(player->s, "2", (char*)getAllPlayer(player->username).c_str());
		break;
	case '3':
		sendChallenge(player, mess.payload, opcode);
		break;
	case '4':
		receiveChallenge(player, mess.payload, opcode);
		break;
	case '5':
		refuseChallenge(player->username, mess.payload, opcode);
		break;
	case '6':
		sendCoordinates(player, opcode, mess.payload);
		break;
	case '9':
		_itoa(logout(player), payload, 10);
		Send(player->s, opcode, payload);
		break;
	default:
		break;
	}
}

/* function cancelChallenge: cancel challenge of user

@param player: A pointer to a struct player who want to cancel your challenge
*/

void cancelChallenge(Player *player) {
	updateUserChallenge(player->username, "");
}

/* function login: handle login request of user

@param player: A pointer to a struct player want to login
@param mess: A pointer to a struct package constain data
*/

void login(Player *player, package mess) {
	if (player->isLogin == 1) Send(player->s, "1", "1");
	char *username, *password;
	username = strtok(mess.payload, " ");
	password = strtok(NULL, "\n");
	int ret = userLogin(username, password);
	if (ret == 10) {
		player->isLogin = 1;
		strcpy_s(player->username, username);
		UserLogin user = UserLogin(player->username, player->s);
		listUserLogin.push_back(user);
		Send(player->s, "1", "0");
		Send(player->s, "2", (char*)getAllPlayer(player->username).c_str());
	}
	else {
		Send(player->s, "1", "1");
	}
}

/* function logout: handle logout request of user

@param player: A pointer to a struct player want to login
@param mess: A pointer to a struct package constain data

Returns 0 on success and 1 on fail
*/

int logout(Player *player) {
	if (player->isLogin == 1) {
		player->isLogin = 0;
		updateUserIsFree(player->username, 1);
		updateUserStatus(player->username, 0);
		//remove in listUserLogin
		removeUser(player->s);
		return 0;
	}
	else return 1;
}

/* function getListUser: handle request get list user in free 

@param username: A pointer to a string user want to get list user in free
@param payload: A pointer to a string data result
*/

void getListUser(char *username, char *payload) {
	payload = (char*)getAllPlayer(username).c_str();
}

/* function getRoom: get room in list by socket

@param s: socket use to get room in list room

Returns a struct room 
*/

Room getRoom(SOCKET client) {
	for (int i = 0; i < listRooms.size(); i++)
	{
		if (listRooms[i].client1 == client || listRooms[i].client2 == client)
			return listRooms[i];
	}
}

/* function getUserLoginBySocket: get struct UserLogin by socket

@param s: socket use to get struct UserLogin

Returns a struct UserLogin
*/

UserLogin getUserLoginBySocket(SOCKET client) {
	for (int i = 0; i < listUserLogin.size(); i++) {
		if (listUserLogin[i].s == client) {
			return listUserLogin[i];
		}
	}
}

/* function getUserLoginByName: get index user in list user login by username

@param username: A pointer to username

Returns -1 on not found and index of user on found
*/

int getUserLoginByName(char *username) {
	for (int i = 0; i < listUserLogin.size(); i++) {
		if (strcmp(listUserLogin[i].username, username) == 0) {
			return i;
		}
	}
	return -1;
}

/* function getSocket: get socket of user by name

@param username: A pointer to username

Returns socket found
*/

SOCKET getSocket(char *username) {
	for (int i = 0; i < listUserLogin.size(); i++) {
		if (strcmp(listUserLogin[i].username, username) == 0) {
			return listUserLogin[i].s;
		}
	}
}

/* function getCoordinates: get coordinates from data

@param data: A pointer to a string data

Returns a struct Coordinates
*/

Coordinates getCoordinates(char *data) {
	char x[3], y[3];
	strncpy(y, data + 0, 2);
	strncpy(x, data + 2, 2);
	Coordinates coordinates(atoi(x), atoi(y));
	return coordinates;
}

/* function sendChallenge: send challenge from player to challenged person

@param player: A pointer to a struct player
@param usernameRecv: A pointer to username receive
@param opcode: A pointer to a message code
*/

void sendChallenge(Player *player, char *usernameRecv, char *opcode) {
	int index;
	index = getUserLoginByName(usernameRecv);
	if (index > -1) {
		if (getStatusFree(usernameRecv) == 1) {
			if (abs(getRank(player->username) - getRank(usernameRecv)) <= 10) {
				updateUserChallenge(player->username, usernameRecv);
				Send(listUserLogin[index].s, opcode, player->username);
			}
			else
			{
				Send(player->s, ERR, "1");
			}
		}
		else
		{
			Send(player->s, ERR, "2");
		}
	}
	else
	{
		Send(player->s, ERR, "1");
	}
	
}

/* function receiveChallenge: receive challenge

@param player: A pointer to a struct player
@param usernameRecv: A pointer to username receive
@param opcode: A pointer to a message code
*/

void receiveChallenge(Player *player, char *usernameRecv, char *opcode) {
	SOCKET s = getSocket(usernameRecv);
	if (strcmp((char*)getUserChallenge(usernameRecv).c_str(), player->username) == 0) {
		updateUserChallenge(usernameRecv, "");
		Send(s, opcode, player->username);
		Send(player->s, opcode, "");
		//change isFree
		updateUserIsFree(player->username, 0);
		updateUserIsFree(usernameRecv, 0);
		//add room
		Room room = Room(s, player->s);
		listRooms.push_back(room);
	}
	else
	{
		Send(player->s, REFUSE, "");
	}
	
}

/* function refuseChallenge: refuse challenge

@param usernameSend: A pointer to username send
@param usernameRecv: A pointer to username receive
@param opcode: A pointer to a message code
*/

void refuseChallenge(char *usernameSend, char *usernameRecv, char *opcode) {
	char *userChall = (char*)getUserChallenge(usernameRecv).c_str();
	if (strcmp((char*)getUserChallenge(usernameRecv).c_str(), usernameSend) == 0) {
		updateUserChallenge(usernameRecv, "");
		SOCKET s1 = getSocket(usernameRecv);
		Send(s1, opcode, usernameSend);
	}
}

/* function sendCoordinates: send coordinates

@param player: A pointer to a struct player
@param opcode: A pointer to a message code
@param payload: A pointer to string data constain coordinates
*/

void sendCoordinates(Player *player, char *opcode, char *payload) {
	Room room = getRoom(player->s);
	SOCKET clientRecv;

	if (room.client1) {
		if (strlen(payload) > 1) {
			Coordinates coordinate = getCoordinates(payload);
			if (room.client1 == player->s) {
				clientRecv = room.client2;
				room.updateMatrix(coordinate, 1);
			}
			else
			{
				clientRecv = room.client1;
				room.updateMatrix(coordinate, 2);
			}
			Send(clientRecv, opcode, payload);
			UserLogin userRecv = getUserLoginBySocket(clientRecv);

			switch (room.isEndGame(coordinate))
			{
			case 0:
				break;
			case 1:
				Send(clientRecv, RESULT, player->username);
				Send(player->s, "h", player->username);
				Send(player->s, RESULT, player->username);
				updateScoreOfPlayer(player->username, 1);
				updateScoreOfPlayer(userRecv.username, 0);
				updateUserIsFree(player->username, 1);
				updateUserIsFree(userRecv.username, 1);
				removeRoom(player->s);
				updateRank();
				break;
			case 2:
				Send(player->s, RESULT, "");
				Send(clientRecv, RESULT, "");
				break;
			default:
				break;
			}
		}
		if (strlen(payload) == 1)
		{
			if (room.client1 == player->s) {
				clientRecv = room.client2;
			}
			else
			{
				clientRecv = room.client1;
			}
			UserLogin playerWin = getUserLoginBySocket(clientRecv);
			Send(clientRecv, RESULT, playerWin.username);
			updateScoreOfPlayer(playerWin.username, 1);
			updateScoreOfPlayer(player->username, 0);
			updateUserIsFree(player->username, 1);
			updateUserIsFree(playerWin.username, 1);
			removeRoom(player->s);
			updateRank();
		}
		else if (strlen(payload) == 0)
		{
			if (room.client1 == player->s) {
				clientRecv = room.client2;
			}
			else
			{
				clientRecv = room.client1;
			}
			UserLogin playerWin = getUserLoginBySocket(clientRecv);
			Send(clientRecv, RESULT, playerWin.username);
			Send(player->s, RESULT, playerWin.username);
			updateScoreOfPlayer(playerWin.username, 1);
			updateScoreOfPlayer(player->username, 0);
			updateUserIsFree(player->username, 1);
			updateUserIsFree(playerWin.username, 1);
			removeRoom(player->s);
			updateRank();
		}
	}
}

/* function removeRoom: remove room from list room

@param s: socket in the room want to delete
*/

void removeRoom(SOCKET s) {
	int index = -1;
	for (int i = 0; i < listRooms.size(); i++) {
		if (listRooms[i].client1 == s || listRooms[i].client2 == s) {
			index = i;
		}
	}
	//remove in listRooms
	if (index > -1) {
		listRooms.erase(listRooms.begin() + index);
	}
}

/* function removeUser: remove user from list user login when user logout

@param s: socket of the user want to delete
*/

void removeUser(SOCKET s) {
	int index = -1;
	for (int i = 0; i < listUserLogin.size(); i++) {
		if (listUserLogin[i].s == s) {
			index = i;
		}
	}
	//remove in listRooms
	if (index > -1) {
		listUserLogin.erase(listUserLogin.begin() + index);
	}
}


