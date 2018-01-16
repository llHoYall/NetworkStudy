/*******************************************************************************
 * @file			TCPEchoServer.c
 * @brief			This is an echo server using TCPv4/TCPv6.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.14	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <unistd.h>
#include "Practical.h"

/* Main Function -------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	if (argc != 2)
		DieWithUserMessage("Parameter(s)", "<Server Port>/<Service>");

	char* service = argv[1];

	int serverSock = SetupTCPServerSocket(service);
	if (serverSock < 0)
		DieWithUserMessage("SetupTCPServerSocket() failed", service);

	for (;;) {
		int clientSock = AcceptTCPConnection(serverSock);

		HandleTCPClient(clientSock);
		close(clientSock);
	}
}
