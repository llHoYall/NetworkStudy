/*******************************************************************************
 * @file			VoteEncoding.c
 * @brief			This is a header file of vote encoding.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.22	Created.
 ******************************************************************************/

#ifndef __VOTE_ENCODING_H__
#define __VOTE_ENCODING_H__

/* API Prototypes ------------------------------------------------------------*/
bool Decode(uint8_t* in_buf, size_t size, tVoteInfo* vi);
size_t Encode(tVoteInfo* vi, uint8_t* out_buf, size_t size);

#endif
