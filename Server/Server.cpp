#include "server.h"

SOCKET			listenSock;
sockaddr_in		serverAddr;

int main() {
	if (!init(listenSock, serverAddr, SERVER_ADDR, SERVER_PORT)) return 0;
	_getch();
}