#include "ds1307.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "spar_utils.h"

char isoRetBuffer[32];

void DS1307_Init()
{
	DS1307_SetSQWOutput(DS1307_SQW_OUT_PIN_FREQUENCY);
}

/**
* 
*
* @param
* @return
*/
void DS1307_WriteRegister(unsigned char addr, unsigned char value)
{
	
	if(addr >= DS1307_HIGH_RAM_ADDR)
	{
		return;
	}
	
	unsigned char writeBytes[2];
	writeBytes[0] = addr;
	writeBytes[1] = value;
	
	AIR_I2C_Write(DS1307_SLAVE_BASE_ADDR, writeBytes, 2);
}

/**
* 
*
* @param
* @return
*/
void DS1307_WriteRegisters(unsigned char addr, unsigned char *buffer, unsigned char length)
{
}

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_ReadRegister(unsigned char addr)
{
	if(addr >= DS1307_HIGH_RAM_ADDR)
	{
		return;
	}
	
	unsigned char writeBytes[1];
	unsigned char readBytes[1];
	
	writeBytes[0] = addr;
	
	AIR_I2C_ComboRead(DS1307_SLAVE_BASE_ADDR, writeBytes, 1, readBytes, 1);
	
	return readBytes[0];
}

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_ReadRegisters(unsigned char addr, unsigned char *buffer, unsigned char length)
{
}

/**
* 
*
* @param
* @return
*/
void DS1307_SetSQWOutput(DS1307_SQW_Setting value)
{
	DS1307_WriteRegister(DS1307_CONTROL_ADDR, value);
}

void DS1307_StopClock()
{
	DS1307_WriteRegister(DS1307_SECONDS_ADDR, DS1307_ReadRegister(DS1307_SECONDS_ADDR) | 0x80);
}

void DS1307_StartClock()
{
	DS1307_WriteRegister(DS1307_SECONDS_ADDR, DS1307_ReadRegister(DS1307_SECONDS_ADDR) & 0x7F);
}

void DS1307_ResetClock()
{
	DS1307_WriteRegister(DS1307_SECONDS_ADDR, 0x80);
	DS1307_WriteRegister(DS1307_MINUTES_ADDR, 0x00);
	DS1307_WriteRegister(DS1307_HOURS_ADDR, 0x00);
	DS1307_WriteRegister(DS1307_DAY_ADDR, 0x00);
	DS1307_WriteRegister(DS1307_DATE_ADDR, 0x00);
	DS1307_WriteRegister(DS1307_MONTH_ADDR, 0x00);
	DS1307_WriteRegister(DS1307_YEAR_ADDR, 0x00);
	DS1307_WriteRegister(DS1307_CONTROL_ADDR, 0x00);
}

/**
* 
*
* @param
* @return
*/
void DS1307_SetSeconds(unsigned char value)
{
	unsigned char chBit = DS1307_ReadRegister(DS1307_SECONDS_ADDR) & 0x80;
	
	value = value % 60;

	unsigned char tens = value / 10;
	unsigned char ones = value - (tens * 10);
	
	value = chBit | (tens << 4) | ones;
	
	DS1307_WriteRegister(DS1307_SECONDS_ADDR, value);
}

/**
* 
*
* @param
* @return
*/
void DS1307_SetMinutes(unsigned char value)
{
	value = value % 60;

	unsigned char tens = value / 10;
	unsigned char ones = value - (tens * 10);
	
	value = (tens << 4) | ones;
	
	DS1307_WriteRegister(DS1307_MINUTES_ADDR, value);
}

/**
* 
*
* @param
* @return
*/
void DS1307_SetHours(unsigned char value)
{
	bool ampm = false;
	
	if(value > 12)
	{
		ampm = true;
	}
	
	unsigned char tens = (value % 12) / 10;
	unsigned char ones = (value % 12) - (tens * 10);
	
	value = 0x40 | (ampm << 5) | (tens << 4) | (ones);
	
	DS1307_WriteRegister(DS1307_HOURS_ADDR, value);
}

/**
* 
*
* @param
* @return
*/
void DS1307_SetDay(unsigned char value)
{
	value = value % 7;
	
	DS1307_WriteRegister(DS1307_DAY_ADDR, value);
}

/**
* 
*
* @param
* @return
*/
void DS1307_SetDate(unsigned char value)
{
	//This is only a very very basic sanity check.
	value = value % 31;

	unsigned char tens = value / 10;
	unsigned char ones = value - (tens * 10);
	
	value = (tens << 4) | ones;
	
	DS1307_WriteRegister(DS1307_DATE_ADDR, value);
}

/**
* 
*
* @param
* @return
*/
void DS1307_SetMonth(unsigned char value)
{
	value = value % 12;

	unsigned char tens = value / 10;
	unsigned char ones = value - (tens * 10);
	
	value = (tens << 4) | ones;
	
	DS1307_WriteRegister(DS1307_MONTH_ADDR, value);
}

/**
* 
*
* @param
* @return
*/
void DS1307_SetYear(unsigned int value)
{
	//If the user wants to enter it in a complete form instead of just the last two digits then
	//this should do the trick.
	if(value >= DS1307_EPOCH_YEAR && value < DS1307_EPOCH_YEAR + 100)
	{
		value = value - DS1307_EPOCH_YEAR;
	}
	
	else
	{
		value = value % 99;
	}

	unsigned char tens = value / 10;
	unsigned char ones = value - (tens * 10);
	
	value = (tens << 4) | ones;
	
	DS1307_WriteRegister(DS1307_YEAR_ADDR, value);
}

/**
* 
*
* @param
* @return
*/
void DS1307_SetControl(unsigned char value)
{
	//Masking out the unsafe stuff
	value = value & 0x93;
	DS1307_WriteRegister(DS1307_CONTROL_ADDR, value);
}

/**
* 
*
* @param
* @return
*/
DS1307_SQW_Setting DS1307_GetSQWOutput()
{
	return (DS1307_SQW_Setting)DS1307_ReadRegister(DS1307_CONTROL_ADDR);
}

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetSeconds()
{
	unsigned char value = DS1307_ReadRegister(DS1307_SECONDS_ADDR);
	return (((value & 0x70) >> 4) * 10) + (value & 0x0F);
}

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetMinutes()
{
	unsigned char value = DS1307_ReadRegister(DS1307_MINUTES_ADDR);
	return (((value & 0x70) >> 4) * 10) + (value & 0x0F);
}

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetHours()
{
	unsigned char value = DS1307_ReadRegister(DS1307_HOURS_ADDR);
	
	bool ampm = (value & 0x20) >> 5;
	unsigned char tens = (value & 0x10) >> 4;
	unsigned char ones = (value & 0x0F);
	
	return (ampm * 12) + (tens * 10) + ones;
}

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetDay()
{
	return DS1307_ReadRegister(DS1307_DAY_ADDR);
}

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetDate()
{
	unsigned char value = DS1307_ReadRegister(DS1307_DATE_ADDR);
	return (((value & 0x30) >> 4) * 10) + (value & 0x0F);
}

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetMonth()
{
	unsigned char value = DS1307_ReadRegister(DS1307_MONTH_ADDR);
	
	unsigned char tens = (value & 0x10) >> 4;
	unsigned char ones = (value & 0x0F);
	
	return (tens * 10) + ones;
}

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetYear()
{
	unsigned char value = DS1307_ReadRegister(DS1307_YEAR_ADDR);
	
	unsigned char tens = value >> 4;
	unsigned char ones = (value & 0x0F);
	
	return (tens * 10) + ones + DS1307_EPOCH_YEAR;
}

/**
* 
*
* @param
* @return
*/
unsigned char DS1307_GetControl()
{
	return DS1307_ReadRegister(DS1307_CONTROL_ADDR);
}


/**
* 
*
* @param
* @return
*/
char *DS1307_GetISO8601Time()
{
	unsigned int year = DS1307_GetYear();
	unsigned char month = DS1307_GetMonth();
	unsigned char date = DS1307_GetDate();
	unsigned char hours = DS1307_GetHours();
	unsigned char minutes = DS1307_GetMinutes();
	unsigned char seconds = DS1307_GetSeconds();
	
	//P[YYYY]-[MM]-[DD]T[hh]:[mm]:[ss]
	sprintf(isoRetBuffer, "%04d-%02d-%02dT%02d:%02d:%02d", year, month, date, hours, minutes, seconds);
	
	return isoRetBuffer;
}

void DS1307_SetDateTime(unsigned int year, unsigned char month, unsigned char date, unsigned char hours, unsigned char minutes, unsigned char seconds)
{
	DS1307_SetYear(year);
	DS1307_SetMonth(month);
	DS1307_SetDate(date);
	DS1307_SetHours(hours);
	DS1307_SetMinutes(minutes);
	DS1307_SetSeconds(seconds);
	
	return;
}