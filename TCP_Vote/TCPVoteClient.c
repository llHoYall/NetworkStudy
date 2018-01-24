/*******************************************************************************
 * @file			TCPVoteClient.c
 * @brief			This is an vote client using TCP.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.22	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include "Practical.h"
#include "VoteProtocol.h"
#include "Framer.h"
#include "VoteEncoding.h"

/* Main Function -------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	if (argc < 4 || argc > 5)
		DieWithUserMessage("Parameter(s)",
				"<Server> <Port>/<Service> <Candidate> [I]");

	char* server = argv[1];
	char* service = argv[2];
	char* candi = atoi(argv[3]);
	if (candi < 0 || candi > MAX_CANDIDATE)
		DieWithUserMessage("Candidate # not valid", argv[3]);
	bool inq = argc > 4 && strcmp(argv[4], "I") == 0;

	int sock = SetupTCPClientSocket(server, service);
	if (sock < 0)
		DieWithUserMessage("SetupTCPClientSocket() failed", "unable to connect");

	FILE* str = fdopen(sock, "r+");
	if (str == NULL)
		DieWithSystemMessage("fdopen() failed");

	tVoteInfo vi;
	memset(&vi, 0, sizeof(vi));
	vi.isInquiry = inq;
	vi.candidate = candi;

	uint8_t outbuf[MAX_WIRE_SIZE];
	size_t req_size = Encode(&vi, outbuf, MAX_WIRE_SIZE);

	printf("Sending %d-byte %s for candidate %d...\n", req_size, (inq ? "inquiry" : "vote"), candi);

	if (PutMsg(outbuf, req_size, str) < 0)
		DieWithSystemMessage("PutMsg() failed");

	uint8_t inbuf[MAX_WIRE_SIZE];
	size_t rsp_size = GetNextMsg(str, inbuf, MAX_WIRE_SIZE);
	if (Decode(inbuf, rsp_size, &vi)) {
		printf("Received:\n");
		if (vi.isResponse)
			printf(" Response to ");
		if (vi.isInquiry)
			printf("inquiry ");
		else
			printf("vote ");
		printf("for candidate %d\n", vi.candidate);
		if (vi.isResponse)
			printf(" count = %lu\n", vi.count);
	}

	fclose(str);
	exit(0);
}
