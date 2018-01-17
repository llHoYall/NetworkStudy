/*******************************************************************************
 * @file			AddressUtility.c
 * @brief			This is a utility of socket address..
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.13	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>

/* APIs ----------------------------------------------------------------------*/
void PrintSocketAddress(const struct sockaddr* addr, FILE* fp) {
	if (addr == NULL || fp == NULL)
		return;

	void* numericAddr;
	char addrBuf[INET6_ADDRSTRLEN];
	in_port_t port;

	switch (addr->sa_family) {
		case AF_INET:
			numericAddr = &((struct sockaddr_in*)addr)->sin_addr;
			port = ntohs(((struct sockaddr_in*)addr)->sin_port);
			break;

		case AF_INET6:
			numericAddr = &((struct sockaddr_in6*)addr)->sin6_addr;
			port = ntohs(((struct sockaddr_in6*)addr)->sin6_port);
			break;

		default:
			fputs(" [unknown type]", fp);
			return;
	}

	if (inet_ntop(addr->sa_family, numericAddr, addrBuf, sizeof(addrBuf)) == NULL)
		fputs(" [invalid address]", fp);
	else {
		fprintf(fp, "%s", addrBuf);
		if (port != 0)
			fprintf(fp, "-%u", port);
	}
}
