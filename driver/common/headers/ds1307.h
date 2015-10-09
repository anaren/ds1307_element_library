// Copyright (c) 2014, Anaren Inc.
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer. 
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// The views and conclusions contained in the software and documentation are those
// of the authors and should not be interpreted as representing official policies, 
// either expressed or implied, of the FreeBSD Project.

#ifndef DS1307_H
#define DS1307_H

#include "../i2c/i2c.h"
#include "ds1307_config.h"


//------------------------------------------------------------------------------
/**
 *  Defines, enumerations, and structure definitions
 */
#ifndef bool
#define bool unsigned char
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

//------------------------------------------------------------------------------
/**
 *  Defines, enumerations, and structure definitions
 */

#define DS1307_SLAVE_BASE_ADDR	0x68
#define DS1307_SECONDS_ADDR	0x00
#define DS1307_MINUTES_ADDR	0x01
#define DS1307_HOURS_ADDR	0x02
#define DS1307_DAY_ADDR		0x03
#define DS1307_DATE_ADDR	0x04
#define DS1307_MONTH_ADDR	0x05
#define DS1307_YEAR_ADDR	0x06
#define DS1307_CONTROL_ADDR	0x07
//This is the first address of general purpose ram on the device
#define DS1307_LOW_RAM_ADDR	0x08
//There is no more memory at this address and beyond on the chip
#define DS1307_HIGH_RAM_ADDR	0x40
#define DS1307_EPOCH_YEAR	2000

typedef enum
{
	DS1307_SQW_OUT_PIN_FREQUENCY_1Hz = 		0x10,
	DS1307_SQW_OUT_PIN_FREQUENCY_4_096kHz = 	0x11,
	DS1307_SQW_OUT_PIN_FREQUENCY_8_192kHz = 	0x12,
	DS1307_SQW_OUT_PIN_FREQUENCY_32_768kHz = 	0x13,
	DS1307_SQW_OUT_PIN_FREQUENCY_Low = 		0x0,
	DS1307_SQW_OUT_PIN_FREQUENCY_High = 		0x80
} DS1307_SQW_Setting;

void DS1307_Init();

/**
* 
*
* @param
* @return
*/
void DS1307_WriteRegister(unsigned char addr, unsigned char value);

/**
* 
*
* @param
* @return
*/
// void DS1307_WriteRegisters(unsigned char addr, unsigned char *buffer, unsigned char length);

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_ReadRegister(unsigned char addr);

/**
* 
*
* @param
* @return
*/
// unsigned char DS1307_ReadRegisters(unsigned char addr, unsigned char *buffer, unsigned char length);

/**
* 
*
* @param
* @return
*/
void DS1307_SetSQWOutput(DS1307_SQW_Setting value);

/**
* 
*
* @param
* @return
*/
void DS1307_StopClock();

/**
* 
*
* @param
* @return
*/
void DS1307_StartClock();

/**
* 
*
* @param
* @return
*/
void DS1307_ResetClock();

/**
* 
*
* @param
* @return
*/
void DS1307_SetSeconds(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetMinutes(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetHour(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetDay(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetDate(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetMonth(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetYear(unsigned int value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetControl(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetSQWOutput(DS1307_SQW_Setting value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetSeconds(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetMinutes(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetHours(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetDay(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetDate(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetMonth(unsigned char value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetYear(unsigned int value);

/**
* 
*
* @param
* @return
*/
void DS1307_SetControl(unsigned char value);

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetSQWOutput();

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetSeconds();

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetMinutes();

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetHour();

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetDay();

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetDate();

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetMonth();

/**
* 
*
* @param
* @return
*/
unsigned int DS1307_GetYear();

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetControl();

/**
* 
*
* @param
* @return
*/
char *DS1307_GetISO8601Time();


#endif  /* DS1307_H */
