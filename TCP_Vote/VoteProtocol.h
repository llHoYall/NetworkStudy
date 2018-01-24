/*******************************************************************************
 * @file			VoteProtocol.c
 * @brief			This is a header file of vote protocol.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.22	Created.
 ******************************************************************************/

#ifndef __VOTE_PROTOCOL_H__
#define __VOTE_PROTOCOL_H__

/* Include Headers -----------------------------------------------------------*/
#include <stdio.h>

/* Enumerations --------------------------------------------------------------*/
enum {
	MAX_CANDIDATE	= 1000,
	MAX_WIRE_SIZE	= 500
};

/* Structures ----------------------------------------------------------------*/
struct tVoteInfo {
	uint64_t count;
	int candidate;
	bool isInquiry;
	bool isResponse;
};
typedef struct tVoteInfo tVoteInfo;

#endif
