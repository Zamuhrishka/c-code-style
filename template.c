/**
* \file    		template.c
* \author  		Kovalchuk Alexander (roux@yandex.ru)
* \brief   		This file contains the prototypes functions which use for...
*/

/*
 * Copyright (c) year Alexander KOVALCHUK
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of library_name.
 *
 * Author:          Alexander KOVALCHUK <roux@yandex.ru>
 */
//_____ I N C L U D E S _______________________________________________________
//_____ C O N F I G S  ________________________________________________________
#if defined(TEMPLATE_DEBUG)
	#define DEBUG_PARAM(fmt, ...)       debug_info(fmt, __VA_ARGS__)
	#define DEBUG(fmt)                  debug_info(fmt)
#else
	#define DEBUG_PARAM(fmt, ...)
	#define DEBUG(fmt, ...)
#endif
//_____ D E F I N I T I O N ___________________________________________________
//_____ M A C R O S ___________________________________________________________
//_____ V A R I A B L E   D E F I N I T I O N  ________________________________
/**
 * \brief		Example of struct typedef definition
 */
typedef struct _fifo
{
	uint32_t	example32;																													/*!< example32 elemet */
	uint16_t	example16;																													/*!< example16 elemet */
	uint8_t		example8;																														/*!< example8 elemet */
} template_definition_t;
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________
//_____ S T A T I C  F U N C T I O N   D E F I N I T I O N   __________________
//_____ F U N C T I O N   D E F I N I T I O N   _______________________________
/**
* This function use as template.
*
* Public function defined in template.h
*/
bool template_init(uint32_t *param1, uint8_t param2)
{
	assert((NULL != receiver) && "Is validated by the caller");
	
	//SIZEOF TO VARIABLES Idiom
	HelloTelegram* telegram = malloc(sizeof *telegram);
	
	//SIZEOF TO VARIABLES Idiom
	uint32_t telegramSize = 0;
	memcpy(&telegramSize, binaryDatastream, sizeof telegramSize);
	
	if(0 == x)
	{
	/* We'll get here if x is zero -- correct! */
	}
}
