/**
* \file    		template.h
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

#pragma once

/* C++ detection */
#ifdef __cplusplus
	extern "C" {
#endif
//_____ I N C L U D E S _______________________________________________________
//_____ C O N F I G S  ________________________________________________________
#if !defined(OS_MAX_TASK)
	#error "Max. number of tasks in your application"
#else /* defined(XYZ) */
	#if OS_MAX_TASK < 2
		#error "OS_MAX_TASK must be >= 2"
	#endif /* !defined(OS_MAX_TASK < 2) */
	#if OS_MAX_TASKS > 63
		#error "OS_CFG.H, OS_MAX_TASKS must be <= 63"
	#endif	/* !defined(OS_MAX_TASKS > 63) */
#endif /* !defined(OS_MAX_TASK) */
//_____ D E F I N I T I O N ___________________________________________________
/**
 * \brief		Example of enum typedef definition
 */
typedef enum
{
	OW_UNLOCKED = 0x00U,																													/*!< example */
	OW_LOCKED   = 0x01U																														/*!< example */
} template_definition_t;
//_____ M A C R O S ___________________________________________________________
/**
 * \brief           Clear bit in register
 * \param[in]       reg: register address
 * \param[in]       bit: bit number
 * \return          none
 * \hideinitializer
 */
#define CLEAR_BIT(reg, bit)				(reg &= (~(1<<(bit))))
//_____ V A R I A B L E   D E C L A R A T I O N S _____________________________
typedef struct Template_Structure Private_Structure;
//_____ I N L I N E   F U N C T I O N   D E F I N I T I O N   _________________
//_____ S T A T I C  F U N C T I O N   D E F I N I T I O N   __________________
/**
 * \brief		Example of struct typedef definition
 */
#pragma pack(push,1)
typedef struct
{
	uint32_t	example32;																													/*!< example32 elemet */
	uint16_t	example16;																													/*!< example16 elemet */
	uint8_t		example8;																														/*!< example8 elemet */
} template_structure_t;
#pragma pack(pop)
//_____ F U N C T I O N   D E C L A R A T I O N S _____________________________
/**
* \brief 	This function used as template.
*
* \param[in] param1: input parametr.
* \param[out] param2: output parametr.
*
* \return 	true/false.
*/
bool template_init(uint32_t param1, uint8_t param2);

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* TEMPLATE_H_ */
