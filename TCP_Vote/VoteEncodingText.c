/*******************************************************************************
 * @file			VoteEncoding.c
 * @brief			Encoding/Decoding protocol..
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.24	Created.
 ******************************************************************************/

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "Practical.h"
#include "VoteProtocol.h"

/* Enumerations --------------------------------------------------------------*/
enum {
	BASE = 10
};

/* Private Variables ---------------------------------------------------------*/
static const char* MAGIC = "Voting";
static const char* VOTESTR = "v";
static const char* INQSTR = "i";
static const char* RESPONSESTR = "R";
static const char* DELIMSTR = " ";

/* APIs ----------------------------------------------------------------------*/
size_t Encode(const tVoteInfo* vi, uint8_t* outbuf, const size_t buf_size) {
	uint8_t* pbuf = outbuf;
	long size = (size_t)buf_size;
	int rv = snprintf((char*)pbuf, size, "%s %c %s %d", MAGIC,
			(vi->isInquiry ? 'i' : 'v'), (vi->isResponse ? "R" : ""), vi->candidate);
	pbuf += rv;
	size -= rv;
	if (vi->isResponse) {
		rv = snprintf((char*)pbuf, size, "%lu", vi->count);
		pbuf += rv;
	}
	return (size_t)(pbuf - outbuf);
}

bool Decode(uint8_t* inbuf, const size_t size, tVoteInfo* vi) {
	char* token;
	token = strtok((char*)inbuf, DELIMSTR);
	if (token == NULL || strcmp(token, MAGIC) != 0)
		return false;

	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
		return false;

	if (strcmp(token, VOTESTR) == 0)
		vi->isInquiry = false;
	else if (strcmp(token, INQSTR) == 0)
		vi->isInquiry = true;
	else
		return false;

	token = strtok(NULL, DELIMSTR);
	if (token == NULL)
		return false;

	if (strcmp(token, RESPONSESTR) == 0) {
		vi->isResponse = true;
		token = strtok(NULL, DELIMSTR);
		if (token == NULL)
			return false;
	}
	else {
		vi->isResponse = false;
	}

	vi->candidate = atoi(token);
	if (vi->isResponse) {
		token = strtok(NULL, DELIMSTR);
		if (token == NULL)
			return false;
		vi->count = strtoll(token, NULL, BASE);
	}
	else {
		vi->count = 0L;
	}
	return true;
}
