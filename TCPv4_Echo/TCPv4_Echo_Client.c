/*******************************************************************************
 * @file			TCPv4_Echo_Client.c
 * @brief			This is an echo client using TCPv4.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.05	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <sys/types.h>
//#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Practical.h"

/* Main Function -------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	if (argc < 3 || argc > 4)
		DieWithUserMessage("Parameter(s)",
				"<Server Address> <Echo word> [<Server Port>]");

	char* serverIP = argv[1];
	char* echoString = argv[2];
	in_port_t serverPort = (argc == 4) ? atoi(argv[3]) : 7;

	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0)
		DieWithSystemMessage("socket() failed");

	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	int retval = inet_pton(AF_INET, serverIP, &serverAddr.sin_addr.s_addr);
	if (retval == 0)
		DieWithUserMessage("inet_pton() failed", "invalid address string");
	else if (retval < 0)
		DieWithSystemMessage("inet_pton() failed");
	serverAddr.sin_port = htons(serverPort);

	if (connect(sock, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
		DieWithSystemMessage("connect() failed");

	size_t echoStringLen = strlen(echoString);
	ssize_t numBytes = send(sock, echoString, echoStringLen, 0);
	if (numBytes < 0)
		DieWithSystemMessage("send() failed");
	else if (numBytes != echoStringLen)
		DieWithUserMessage("send()", "sent unexpected number of bytes");

	unsigned int totalBytesRecv = 0;
	fputs("Received: ", stdout);
	while (totalBytesRecv < echoStringLen) {
		char buffer[BUFSIZE];
		numBytes = recv(sock, buffer, BUFSIZE - 1, 0);
		if (numBytes < 0)
			DieWithSystemMessage("recv() failed");
		else if (numBytes == 0)
			DieWithUserMessage("recv()", "connection closed prematurely");
		totalBytesRecv += numBytes;
		buffer[numBytes] = '\0';
		fputs(buffer, stdout);
	}

	fputc('\n', stdout);
	close(sock);
	exit(0);
}
