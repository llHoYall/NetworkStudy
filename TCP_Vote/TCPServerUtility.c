/*******************************************************************************
 * @file			TCPServerUtility.c
 * @brief			This is a utility of TCP server.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.07	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "Practical.h"

/* Private Variables ---------------------------------------------------------*/
static const int MAXPENDING = 5;

/* APIs ----------------------------------------------------------------------*/
int SetupTCPServerSocket(const char* service) {
	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(addrCriteria));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_flags = AI_PASSIVE;
	addrCriteria.ai_socktype = SOCK_STREAM;
	addrCriteria.ai_protocol = IPPROTO_TCP;

	struct addrinfo* serverAddr;
	int retval = getaddrinfo(NULL, service, &addrCriteria, &serverAddr);
	if (retval != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(retval));

	int serverSock = -1;
	for (struct addrinfo* addr = serverAddr; addr != NULL; addr = addr->ai_next) {
		serverSock = socket(serverAddr->ai_family, serverAddr->ai_socktype,	\
												serverAddr->ai_protocol);
		if (serverSock < 0)
			continue;
		if ((bind(serverSock, serverAddr->ai_addr, serverAddr->ai_addrlen) == 0)	\
				&& (listen(serverSock, MAXPENDING) == 0)) {
			struct sockaddr_storage localAddr;
			socklen_t addrSize = sizeof(localAddr);
			if (getsockname(serverSock, (struct sockaddr*)&localAddr, &addrSize) < 0)
				DieWithSystemMessage("getsockname() failed");
			fputs("Binding to ", stdout);
			PrintSocketAddress((struct sockaddr*)&localAddr, stdout);
			fputc('\n', stdout);
			break;
		}


		close(serverSock);
		serverSock = -1;
	}

	freeaddrinfo(serverAddr);
	return serverSock;
}

int AcceptTCPConnection(int serverSock) {
	struct sockaddr_storage clientAddr;
	socklen_t clientAddrLen = sizeof(clientAddr);

	int clientSock = accept(serverSock, (struct sockaddr*)&clientAddr,	\
													&clientAddrLen);
	if (clientSock < 0)
		DieWithSystemMessage("accept() failed");

	fputs("Handling client ", stdout);
	PrintSocketAddress((struct sockaddr*)&clientAddr, stdout);
	fputc('\n', stdout);

	return clientSock;
}

void HandleTCPClient(int clientSocket) {
	char buffer[BUFSIZE];

	ssize_t numBytesRecv = recv(clientSocket, buffer, BUFSIZE, 0);
	if (numBytesRecv < 0)
		DieWithSystemMessage("recv() failed");

	while (numBytesRecv > 0) {
		ssize_t numBytesSent = send(clientSocket, buffer, numBytesRecv, 0);
		if (numBytesSent < 0)
			DieWithSystemMessage("send() failed");
		else if (numBytesSent != numBytesRecv)
			DieWithUserMessage("send()", "sent unexpected number of bytes");

		numBytesRecv = recv(clientSocket, buffer, BUFSIZE, 0);
		if (numBytesRecv < 0)
			DieWithSystemMessage("recv() failed");
	}

	close(clientSocket);
}
