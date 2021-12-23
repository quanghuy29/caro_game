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
#include <iostream>
#pragma comment (lib,"ws2_32.lib")

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5500
#define MAX_CLIENT 1024
#define BUFF_SIZE 2048
#define BUFF_MAX 100000
#define SIZE 100
#define NAME_SIZE 20
#define LENGTH 3
#define LENGTHDATA 2
#define CHALLENGE '1'
#define ACCEPT '2'
#define REFUSE '3'
#define STEP '4'
#define RESULT '5'
#define ERR '6'
#define ENDING_DELIMITER "\r\n"

struct playerInfo {
	char username[NAME_SIZE];
	char password[NAME_SIZE];
	int score;
	int rank;
	bool isFree;
};

struct Player {
	SOCKET s;
	char IPAddress[INET_ADDRSTRLEN];
	int portAddress;
	playerInfo playerinfo;
};

struct room{
	Player player1;
	Player player2;
	int a[LENGTH][LENGTH] = { 0 };
};

/* Function Prototype */
int init(SOCKET listenSock, sockaddr_in serverAddr, char serverIP[], int serverPort);
int testWin(int x, int y, int a[LENGTH][LENGTH]);
int Receive(Player, char *, char *);
int Send(Player, char *, char *);
int processDataReceive(Player, char *);
void convertIntToChar(int value, char des[]);

#endif