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

/* Definitions ---------------------------------------------------------------*/
#define BUFSIZE		256

/* APIs ----------------------------------------------------------------------*/
// DieWithMessage
void DieWithUserMessage(const char* msg, const char* detail);
void DieWithSystemMessage(const char* msg);

// TCPServerUtility
void HandleTCPClient(int clientSocket);

#endif
