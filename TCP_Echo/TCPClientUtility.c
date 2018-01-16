/*******************************************************************************
 * @file			TCPClientUtility.c
 * @brief			This is a utility of TCP client.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.13	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include "Practical.h"

/* APIs ----------------------------------------------------------------------*/
int SetupTCPClientSocket(const char* host, const char* service) {
	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(addrCriteria));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_socktype = SOCK_STREAM;
	addrCriteria.ai_protocol = IPPROTO_TCP;

	struct addrinfo* serverAddr;
	int retval = getaddrinfo(host, service, &addrCriteria, &serverAddr);
	if (retval != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(retval));

	int sock = -1;
	for (struct addrinfo* addr = serverAddr; addr != NULL; addr = addr->ai_next) {
		sock = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
		if (sock < 0)
			continue;
		if (connect(sock, addr->ai_addr, addr->ai_addrlen) == 0)
			break;
		close(sock);
		sock = -1;
	}

	freeaddrinfo(serverAddr);
	return sock;
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
