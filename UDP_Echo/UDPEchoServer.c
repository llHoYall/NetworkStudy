/*******************************************************************************
 * @file			UDPEchoServer.c
 * @brief			This is an echo server using UDP.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.17	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "Practical.h"

/* Main Function -------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	if (argc != 2)
		DieWithUserMessage("Parameter(s)", "<Server Port/Service>");

	char* service = argv[1];

	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(addrCriteria));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_flags = AI_PASSIVE;
	addrCriteria.ai_socktype = SOCK_DGRAM;
	addrCriteria.ai_protocol = IPPROTO_UDP;

	struct addrinfo* serverAddr;
	int retval = getaddrinfo(NULL, service, &addrCriteria, &serverAddr);
	if (retval != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(retval));

	int sock = socket(serverAddr->ai_family, serverAddr->ai_socktype, serverAddr->ai_protocol);
	if (sock < 0)
		DieWithSystemMessage("socket() failed");

	if (bind(sock, serverAddr->ai_addr, serverAddr->ai_addrlen) < 0)
		DieWithSystemMessage("bind() failed");

	freeaddrinfo(serverAddr);

	for (;;) {
		struct sockaddr_storage clientAddr;
		socklen_t clientAddrLen = sizeof(clientAddr);

		char buffer[MAXSTRINGLENGTH];
		ssize_t numBytesRecv = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0, (struct sockaddr*)&clientAddr, &clientAddrLen);
		if (numBytesRecv < 0)
			DieWithSystemMessage("recvfrom() failed");

		fputs("Handling client ", stdout);
		PrintSocketAddress((struct sockaddr*)&clientAddr, stdout);
		fputc('\n', stdout);

		ssize_t numBytesSent = sendto(sock, buffer, numBytesRecv, 0, (struct sockaddr*)&clientAddr, sizeof(clientAddr));
		if (numBytesSent < 0)
			DieWithSystemMessage("sendto() failed");
		else if (numBytesSent != numBytesRecv)
			DieWithUserMessage("sendto()", "sent unexpected number of bytes");
	}
}
