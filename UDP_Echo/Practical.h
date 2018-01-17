/*******************************************************************************
 * @file			Practical.c
 * @brief			This is a header file of utility.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.06	Created.
 ******************************************************************************/

#ifndef __PRACTICAL_H__
#define __PRACTICAL_H__

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>

/* Definitions ---------------------------------------------------------------*/
#define BUFSIZE						256
#define MAXSTRINGLENGTH		64

/* APIs ----------------------------------------------------------------------*/
// DieWithMessage
void DieWithUserMessage(const char* msg, const char* detail);
void DieWithSystemMessage(const char* msg);

// TCPServerUtility
int SetupTCPServerSocket(const char* service);
int AcceptTCPConnection(int serverSock);
void HandleTCPClient(int clientSocket);

// TCPClientUtility
int SetupTCPClientSocket(const char* host, const char* service);

// AddressUtility
void PrintSocketAddress(const struct sockaddr* addr, FILE* fp);

#endif
