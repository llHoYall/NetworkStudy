/*******************************************************************************
 * @file			DieWithMessage.c
 * @brief			This is a printing message utility.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.06	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

/* APIs ----------------------------------------------------------------------*/
void DieWithUserMessage(const char* msg, const char* detail) {
	fputs(msg, stderr);
	fputs(": ", stderr);
	fputs(detail, stderr);
	fputc('\n', stderr);
	exit(1);
}

void DieWithSystemMessage(const char* msg) {
	perror(msg);
	exit(1);
}
