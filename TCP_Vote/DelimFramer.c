/*******************************************************************************
 * @file			DelimFramer.c
 * @brief			Delimiter protocol for framing.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.23	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "Practical.h"

/* Private Variables ---------------------------------------------------------*/
static const char DELIMITER = '\n';

/* APIs ----------------------------------------------------------------------*/
int GetNextMsg(FILE* in, uint8_t* buf, size_t buf_size) {
	int count = 0;
	int next_char;
	while (count < buf_size) {
		next_char = getc(in);
		if (next_char == EOF) {
			if (count > 0)
				DieWithUserMessage("GetNextMsg()", "Stream ended prematurely");
			else
				return -1;
		}
		if (next_char == DELIMITER)
			break;
		buf[count++] = next_char;
	}
	if (next_char != DELIMITER) {
		return -count;
	}
	else {
		return count;
	}
}

int PutMsg(uint8_t buf[], size_t msg_size, FILE* out) {
	int i;
	for (i = 0; i < msg_size; i++)
		if (buf[i] == DELIMITER)
			return -1;
	if (fwrite(buf, 1, msg_size, out) != msg_size)
		return -1;
	fputc(DELIMITER, out);
	fflush(out);
	return msg_size;
}
