/*******************************************************************************
 * @file			UDPEchoClient.c
 * @brief			This is an echo client using UDP.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.17	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include "Practical.h"

/* Main Function -------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	if (argc < 3 || argc > 4)
		DieWithUserMessage("Parameter(s)",
				"<Server Address/Name> <Echo word> [<Server Port>/<Service>]");

	char* server = argv[1];
	char* echoStr = argv[2];
	size_t echoStrLen = strlen(echoStr);
	if (echoStrLen > MAXSTRINGLENGTH)
		DieWithUserMessage(echoStr, "string too long");
	char* serverPort = (argc == 4) ? argv[3] : "echo";

	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(addrCriteria));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_socktype = SOCK_DGRAM;
	addrCriteria.ai_protocol = IPPROTO_UDP;

	struct addrinfo* serverAddr;
	int retval = getaddrinfo(server, serverPort, &addrCriteria, &serverAddr);
	if (retval != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(retval));


	int sock = socket(serverAddr->ai_family, serverAddr->ai_socktype,	serverAddr->ai_protocol);
	if (sock < 0)
		DieWithSystemMessage("socket() failed");

	ssize_t numBytes = sendto(sock, echoStr, echoStrLen, 0, serverAddr->ai_addr, serverAddr->ai_addrlen);
	if (numBytes < 0)
		DieWithSystemMessage("sendto() failed");
	else if (numBytes != echoStrLen)
		DieWithUserMessage("sendro() error", "sent unexpected number of bytes");

	struct sockaddr_storage fromAddr;
	socklen_t fromAddrLen = sizeof(fromAddr);
	char buffer[MAXSTRINGLENGTH + 1];
	numBytes = recvfrom(sock, buffer, MAXSTRINGLENGTH, 0, (struct sockaddr*)&fromAddr, &fromAddrLen);
	if (numBytes < 0)
		DieWithSystemMessage("recvfrom() failed");
	else if (numBytes != echoStrLen)
		DieWithUserMessage("recvfrom() error", "received unexpected number of bytes");

	//if (!SockAddrsEqual(serverAddr->ai_addr, (struct sockaddr*)&fromAddr))
		//DieWithUserMessage("recvfrom()", "received a packet from unknown source");

	freeaddrinfo(serverAddr);

	buffer[echoStrLen] = '\0';
	printf("Received: %s\n", buffer);

	close(sock);
	exit(0);
}
