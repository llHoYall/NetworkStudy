/*******************************************************************************
 * @file			TCPv4ServerUtility.c
 * @brief			This is a utility of TCPv4 server.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.07	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "Practical.h"

/* APIs ----------------------------------------------------------------------*/
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
