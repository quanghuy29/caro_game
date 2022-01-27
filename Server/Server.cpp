
#define FD_SETSIZE 1024
#include "server.h"
#include "database.h"
#include "Room.h"

int main() {
	DWORD		nEvents = 0;
	DWORD		index;
	Player listClientConnect[WSA_MAXIMUM_WAIT_EVENTS];
	WSAEVENT	events[WSA_MAXIMUM_WAIT_EVENTS];
	WSANETWORKEVENTS sockEvent;

	//Step 1: Inittiate WinSock
	WSADATA wsaData;
	WORD wVersion = MAKEWORD(2, 2);
	if (WSAStartup(wVersion, &wsaData)) {
		printf("Winsock 2.2 is not supported\n");
		return 0;
	}

	//Step 2: Construct LISTEN socket
	SOCKET listenSock;
	listenSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (listenSock == INVALID_SOCKET) {
		printf("Error %d: Cannot create server socket.", WSAGetLastError());
		return 0;
	}

	//Step 3: Bind address to socket
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr);

	listClientConnect[0].s = listenSock;
	events[0] = WSACreateEvent(); //create new events
	nEvents++;

	// Associate event types FD_ACCEPT and FD_CLOSE
	// with the listening socket and newEvent   
	WSAEventSelect(listClientConnect[0].s, events[0], FD_ACCEPT | FD_CLOSE);
	if (bind(listenSock, (sockaddr *)&serverAddr, sizeof(serverAddr)))
	{
		printf("Error %d: Cannot associate a local address with server socket.", WSAGetLastError());
		return 0;
	}

	//Step 4: Listen request from client
	if (listen(listenSock, 10)) {
		printf("Error %d: Cannot place server socket in state LISTEN.", WSAGetLastError());
		return 0;
	}

	printf("Server started!\n");

	/*test function
	Player playerTest;
	while (1) {
		char testUser[20] = "meobeo123";
		char pass[20] = "1234567";
		int meoTest = userLogin(testUser, pass);
	}

	*/

	char mainBuff[BUFF_MAX];
	package messReceive;
	SOCKET connSock;
	sockaddr_in clientAddr;
	int clientAddrLen = sizeof(clientAddr);
	int ret, i;

	for (i = 1; i < WSA_MAXIMUM_WAIT_EVENTS; i++) {
		listClientConnect[i].s = 0;
	}

	while (1) {
		//wait for network events on all socket
		index = WSAWaitForMultipleEvents(nEvents, events, FALSE, WSA_INFINITE, FALSE);
		if (index == WSA_WAIT_FAILED) {
			printf("Error %d: WSAWaitForMultipleEvents() failed\n", WSAGetLastError());
			break;
		}

		index = index - WSA_WAIT_EVENT_0;
		WSAEnumNetworkEvents(listClientConnect[index].s, events[index], &sockEvent);

		if (sockEvent.lNetworkEvents & FD_ACCEPT) {
			if (sockEvent.iErrorCode[FD_ACCEPT_BIT] != 0) {
				printf("FD_ACCEPT failed with error %d\n", sockEvent.iErrorCode[FD_READ_BIT]);
				break;
			}

			if ((connSock = accept(listClientConnect[index].s, (sockaddr *)&clientAddr, &clientAddrLen)) == SOCKET_ERROR) {
				printf("Error %d: Cannot permit incoming connection.\n", WSAGetLastError());
				break;
			}

			//Add new socket into socks array
			if (nEvents == WSA_MAXIMUM_WAIT_EVENTS) {
				printf("\nToo many clients.");
				closesocket(connSock);
			}
			else {
				listClientConnect[nEvents].s = connSock;
				inet_ntop(AF_INET, &clientAddr.sin_addr, listClientConnect[nEvents].IPAddress, sizeof(listClientConnect[nEvents].IPAddress));
				listClientConnect[nEvents].portAddress = ntohs(clientAddr.sin_port);
				events[nEvents] = WSACreateEvent();
				WSAEventSelect(listClientConnect[nEvents].s, events[nEvents], FD_READ | FD_CLOSE);
				nEvents++;
			}

			//reset event
			WSAResetEvent(events[index]);
		}

		if (sockEvent.lNetworkEvents & FD_READ) {
			//Receive message from client
			if (sockEvent.iErrorCode[FD_READ_BIT] != 0) {
				printf("FD_READ failed with error %d\n", sockEvent.iErrorCode[FD_READ_BIT]);
				break;
			}

			ZeroMemory(&messReceive, sizeof(messReceive));
			mainBuff[0] = 0;
			ret = Receive(listClientConnect[index], mainBuff, &messReceive);
			while (ret) {
				if (ret == 2) {
					handleDataReceive(&listClientConnect[index], messReceive);
					break;
				}
				else {
					handleDataReceive(&listClientConnect[index], messReceive);
					ZeroMemory(&messReceive, sizeof(messReceive));
					ret = Receive(listClientConnect[index], mainBuff, &messReceive);
				}
			}

			//Release socket and event if an error occurs
			if (ret <= 0) {
				//ret = Send(listClientConnect[index], serverPackage);
				closesocket(listClientConnect[index].s);
				WSAResetEvent(events[index]);
				listClientConnect[index].s = listClientConnect[nEvents - 1].s;
				events[index] = events[nEvents - 1];
				listClientConnect[nEvents - 1].s = 0;
				events[nEvents - 1] = 0;
				nEvents--;
			}
			else {
				//reset event
				WSAResetEvent(events[index]);
			}
		}

		if (sockEvent.lNetworkEvents & FD_CLOSE) {
			if (sockEvent.iErrorCode[FD_CLOSE_BIT] != 0) {
				printf("FD_CLOSE failed with error %d\n", sockEvent.iErrorCode[FD_CLOSE_BIT]);
			}
			//Release socket and event
			closesocket(listClientConnect[index].s);
			WSAResetEvent(events[index]);
			listClientConnect[index].s = listClientConnect[nEvents - 1].s;
			events[index] = events[nEvents - 1];
			listClientConnect[nEvents - 1].s = 0;
			events[nEvents - 1] = 0;
			nEvents--;
		}
	}

	return 0;
}
