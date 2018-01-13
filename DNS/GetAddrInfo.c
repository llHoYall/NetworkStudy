/*******************************************************************************
 * @file			GetAddrInfo.c
 * @brief			This is n dns example.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.12	Created.
 *******************************************************************************
 *	Usage
 *		$ GetAddrInfo localhost whois
 *		$ GetAddrInfo www.uky.edu whois
 *		$ GetAddrInfo 169.1.1.100 time
 *		$ GetAddrInfo FE80::0:ABCD:1:2:3 12345
 *		$ GetAddrInfo google.com 0
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include "Practical.h"

/* Main Function -------------------------------------------------------------*/
int main(int argc, char* argv[]) {
	if (argc != 3)
		DieWithUserMessage("Parameter(s)", "<Address/Name> <Port/Service>");

	char* addrString = argv[1];
	char* portString = argv[2];

	struct addrinfo addrCriteria;
	memset(&addrCriteria, 0, sizeof(addrCriteria));
	addrCriteria.ai_family = AF_UNSPEC;
	addrCriteria.ai_socktype = SOCK_STREAM;
	addrCriteria.ai_protocol = IPPROTO_TCP;

	struct addrinfo* addrList;
	int retval = getaddrinfo(addrString, portString, &addrCriteria, &addrList);
	if (retval != 0)
		DieWithUserMessage("getaddrinfo() failed", gai_strerror(retval));

	for (struct addrinfo* addr = addrList; addr != NULL; addr = addr->ai_next) {
		PrintSocketAddress(addr->ai_addr, stdout);
		fputc('\n', stdout);
	}

	freeaddrinfo(addrList);

	exit(0);
}
