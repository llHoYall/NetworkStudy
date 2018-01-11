/*******************************************************************************
 * @file			TCPv6_Echo_Server.c
 * @brief			This is an echo server using TCPv6.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.11	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"

/* Definitions ---------------------------------------------------------------*/
static const int MAXPENDING = 5;

/* Main Function -------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	if (argc != 2)
		DieWithUserMessage("Parameter(s)", "<Server Port>");

	in_port_t serverPort = atoi(argv[1]);

	int serverSock = socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
	if (serverSock < 0)
		DieWithSystemMessage("socket() failed");

	struct sockaddr_in6 serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin6_family = AF_INET6;
	serverAddr.sin6_addr = in6addr_any;
	serverAddr.sin6_port = htons(serverPort);

	if (bind(serverSock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
		DieWithSystemMessage("bind() failed");

	if (listen(serverSock, MAXPENDING) < 0)
		DieWithSystemMessage("listen() failed");

	for (;;) {
		struct sockaddr_in6 clientAddr;
		socklen_t clientAddrLen = sizeof(clientAddr);

		int clientSock = accept(serverSock, (struct sockaddr*)&clientAddr, &clientAddrLen);
		if (clientSock < 0)
			DieWithSystemMessage("accept() failed");

		char clientName[INET6_ADDRSTRLEN];
		if (inet_ntop(AF_INET6, &clientAddr.sin6_addr.s6_addr, clientName, sizeof(clientName)) != NULL)
			printf("Handling client %s/%d\n", clientName, ntohs(clientAddr.sin6_port));
		else
			puts("Unable to get client address");

		HandleTCPClient(clientSock);
	}
}
