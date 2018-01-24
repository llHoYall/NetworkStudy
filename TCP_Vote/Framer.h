/*******************************************************************************
 * @file			Framer.c
 * @brief			This is a header file of framer.
 * @author		llHoYall <hoya128@gmail.com>
 *******************************************************************************
 * @version		v1.0
 * @note
 *	- 2018.01.22	Created.
 ******************************************************************************/

#ifndef __FRAMER_H__
#define __FRAMER_H__

/* API Prototypes ------------------------------------------------------------*/
int GetNextMsg(FILE* in, uint8_t* buf, size_t buf_size);
int PutMsg(uint8_t buf[], size_t msg_size, FILE* out);

#endif
