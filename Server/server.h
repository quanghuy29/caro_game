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

int init(SOCKET listenSock, sockaddr_in serverAddr, char serverIP[], int serverPort) {
	WSADATA wsaData;
	WORD ver = MAKEWORD(2, 2);
	WSAStartup(ver, &wsaData);

	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listenSock == INVALID_SOCKET) {
		printf("Error cannot create server socket\n");
		return 0;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(serverPort);
	inet_pton(AF_INET, serverIP, &serverAddr.sin_addr);

	if (bind(listenSock, (sockaddr*)&serverAddr, sizeof serverAddr)) {
		printf("Error cannot bind address to server\n");
		return 0;
	}

	if (listen(listenSock, MAX_CLIENT)) {
		printf("Error cannor place server in state LISTEN\n");
		return 0;
	}

	printf("Server started!\n");
	return 1;
}
