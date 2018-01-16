/*******************************************************************************
 * @file			TCPEchoClient.c
 * @brief			This is an echo client using TCPv4/TCPv6.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.13	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
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
	char* service = (argc == 4) ? argv[3] : "echo";

	int sock = SetupTCPClientSocket(server, service);
	if (sock < 0)
		DieWithUserMessage("SetupTCPClientSocket() failed", "unable to connect");

	size_t echoStrLen = strlen(echoStr);
	ssize_t numBytes = send(sock, echoStr, echoStrLen, 0);
	if (numBytes < 0)
		DieWithSystemMessage("send() failed");
	else if (numBytes != echoStrLen)
		DieWithUserMessage("send()", "sent unexpected number of bytes");

	unsigned int totalBytesRecv = 0;
	fputs("Received: ", stdout);
	while (totalBytesRecv < echoStrLen) {
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
