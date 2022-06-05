/*
 * PIC18F4550 interfacing with RTC DS1307
 * http://www.electronicwings.com
 */ 

#include <stdio.h>
#include "Configuration_Header_File.h"
#include <pic18f4550.h>
#include <string.h>
#include <math.h>
#include "I2C_Master_File.h"


void MSdelay(unsigned int);

#define device_id_write 0xD0
#define device_id_read 0xD1
#define hour_12_PM 0x60
#define hour_12_AM 0x40
void RTC_Clock_Write(char sec, char min, char hour, char AM_PM)					/* function for clock */
{
    hour = (hour | AM_PM);        /* whether it is AM or PM */
	I2C_Start(device_id_write);	  /* start I2C communication with device slave address */	
	I2C_Write(0);			      /* write on 0 location for second value */
	I2C_Write(sec);			      /* write second value on 00 location */
	I2C_Write(min);			      /* write min value on 01 location */
	I2C_Write(hour);		      /* write hour value on 02 location */
	I2C_Stop();				      /* stop I2C communication */
}

void RTC_Calendar_Write(char day, char date, char month, char year)	/* function for calendar */
{
	I2C_Start(device_id_write);	  /* start I2C communication with device slave address */
	I2C_Write(3);			      /* write on 3 location for day value */
	I2C_Write(day);			      /* write day value on 03 location */
	I2C_Write(date);		      /* write date value on 04 location */
	I2C_Write(month);		      /* write month value on 05 location */
	I2C_Write(year);		      /* write year value on 06 location */
	I2C_Stop();
}
void main()
{    
    OSCCON=0x72;            /*Use internal oscillator and 
                             *set frequency to 8 MHz*/
    MSdelay(50);
    I2C_Init();             /*initialize I2C protocol*/
    MSdelay(10);   
    RTC_Clock_Write(0x00, 0x58, 0x11, hour_12_PM);        /* seconds, minute and hour send as parameter*/
    RTC_Calendar_Write(0x1,0x20,0x02,0x17);/* send day,date,month and year*/
    while(1);
}

void MSdelay(unsigned int val)
{
 unsigned int i,j;
 for(i=0;i<val;i++)
     for(j=0;j<165;j++);             /*This count Provide delay of 1 ms for 8MHz Frequency */
}