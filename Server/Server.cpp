#include "server.h"

SOCKET			listenSock;
sockaddr_in		serverAddr;

int main() {
	if (!init(listenSock, serverAddr, SERVER_ADDR, SERVER_PORT)) return 0;
	_getch();
}

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
