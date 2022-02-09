#ifndef _SERVER_H_
#define _SERVER_H_

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string>
#include <process.h>
#include <windows.h>
#include <conio.h>
#include "Room.h"
#include <vector>
#include <iostream>
#pragma comment (lib,"ws2_32.lib")

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5500
#define MAX_CLIENT 1024
#define BUFF_SIZE 2048
#define BUFF_MAX 100000
#define SIZE 100
#define NAME_SIZE 20
#define LENGTHDATA 4
#define CHALLENGE "3"
#define ACCEPT "4"
#define REFUSE "5"
#define STEP "6"
#define RESULT "7"
#define ERR "8"

struct Player {
	SOCKET s;
	char IPAddress[INET_ADDRSTRLEN];
	int portAddress;
	int isLogin = 0;
	char username[30];
};

struct package {
	char opcode;
	char length[5];
	char payload[BUFF_MAX];
};

struct UserLogin {
	char *username;
	SOCKET s;

	UserLogin(char *name, SOCKET S) {
		username = name;
		s = S;
	}
};

/* Function Prototype */
int Receive(Player, char *, package *);
int Send(SOCKET, char *, char *);
void handleDataReceive(Player *, package);
void convertIntToChar(int value, char des[]);

void login(Player *, package);
int logout(Player *);
void giveUp(Player *);
void getListUser(char *, char *);
SOCKET getSocket(char *);
void removeRoom(SOCKET);
void removeUser(SOCKET);

//challenge
void sendChallenge(Player *, char *, char *);
void receiveChallenge(Player *, char *, char *);
void refuseChallenge(char *, char *, char *);
void sendCoordinates(Player *, char *, char *);
#endif