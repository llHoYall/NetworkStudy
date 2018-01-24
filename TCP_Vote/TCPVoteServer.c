/*******************************************************************************
 * @file			TCPVoteServer.c
 * @brief			This is an vote server using TCP.
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
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>
#include "Practical.h"
#include "VoteProtocol.h"
#include "VoteEncoding.h"
#include "Framer.h"

/* Private Variables ---------------------------------------------------------*/
static uint64_t counts[MAX_CANDIDATE + 1];

/* Main Function -------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	if (argc != 2)
		DieWithUserMessage("Parameter(s)", "<Server Port/Service>");

	int server_sock = SetupTCPServerSocket(argv[1]);

	for (;;) {
		int client_sock = AcceptTCPConnection(server_sock);

		FILE* channel = fdopen(client_sock, "r+");
		if (channel == NULL)
			DieWithSystemMessage("fdopen() failed");

		int size;
		uint8_t inbuf[MAX_WIRE_SIZE];
		tVoteInfo vi;
		while ((size = GetNextMsg(channel, inbuf, MAX_WIRE_SIZE)) > 0) {
			memset(&vi, 0, sizeof(vi));
			printf("Received message (%d bytes)\n", size);
			if (Decode(inbuf, size, &vi)) {
				if (!vi.isResponse) {
					vi.isResponse = true;
					if (vi.candidate >= 0 && vi.candidate <= MAX_CANDIDATE) {
						if (!vi.isInquiry)
							counts[vi.candidate] += 1;
						vi.count = counts[vi.candidate];
					}
				}
				uint8_t outbuf[MAX_WIRE_SIZE];
				size = Encode(&vi, outbuf, MAX_WIRE_SIZE);
				if (PutMsg(outbuf, size, channel) < 0) {
					fputs("Error framing/outputting message\n", stderr);
					break;
				}
				else {
					printf("Processed %s for candidate %d; current count is %lu\n", (vi.isInquiry ? "inquiry" : "vote"), vi.candidate, vi.count);
				}
				fflush(channel);
			}
			else {
				fputs("Parse error, closing connection.\n", stderr);
				break;
			}
		}
		puts("Client finished");
		fclose(channel);
	}
}
