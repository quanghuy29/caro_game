#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <stdio.h>
#include <math.h>
#include <ctime>
#include <string>
#include <process.h>
#include <windows.h>
#include <conio.h>
#pragma comment (lib,"ws2_32.lib")

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5500
#define MAX_CLIENT 1024
#define BUFF_SIZE 2048
#define NAME_SIZE 20
#define LENGTH 3
#define CHALLENGE '1'
#define ACCEPT '2'
#define REFUSE '3'
#define STEP '4'
#define RESULT '5'
#define ERR '6'

typedef struct {
	char username[NAME_SIZE];
	int score;
	int rank;
} playerInfo;

typedef struct {
	SOCKET s;
	char IPAddress[INET_ADDRSTRLEN];
	char portAddress[7];
	playerInfo playerinfo;
	bool isFree;
} Player;

typedef struct {
	Player player1;
	Player player2;
	int a[LENGTH][LENGTH] = { 0 };
};
int init(SOCKET listenSock, sockaddr_in serverAddr, char serverIP[], int serverPort);
