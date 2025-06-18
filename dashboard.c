/*
 * File:   dashboard.c
 * Author: jahna
 *
 * Created on 21 September, 2024, 2:51 PM
 */

#include <xc.h>
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"
#include "i2c.h"
#include "rtc.h"
#include "external_eeprom.h"

unsigned char clock_reg[3];
unsigned char time[9];
unsigned short reg_val;
int index = 0, flag = 1,speed = 0;;
char *gear[9] = {"ON","GR","GN","G1","G2","G3","G4","G5","C_","VL","DL","CL","ST","SP"};
unsigned char key;
static unsigned char add = 4;


static void get_time(void)
{
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40) //12hrs format
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else // 24hrs format
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F);
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
}

void dashboard(void)
{
        clcd_print("Time",LINE1(0));
        clcd_print("EV",LINE1(9));
        clcd_print("SP",LINE1(12));
        get_time();
        clcd_print(time,LINE2(0));
        clcd_print(gear[index],LINE2(9));
        clcd_putch('0' + speed / 10,LINE2(12));
        clcd_putch('0' + speed % 10,LINE2(13));
 
        //gear change
        
        key = read_switches(STATE_CHANGE);
        if(key == MK_SW1)
        {
            index = 8;
            
            store_event();
        }
        else if(key == MK_SW2)
        {
            prekey = 0;
            if(index < 7)
               index++;
             store_event();
        }
        else if(key == MK_SW3)
        {
            prekey = 0;
            if(index > 1)
                index--;
            store_event();
        }
        
        //speed
        reg_val = read_adc(CHANNEL4);
        speed = reg_val / 10.33;
       
}

void store_event(void)
{
    if(event_count < 10)
        event_count++;
    get_time();
     if(main_flag == VIEWLOG)
            index = 9;
        else if(main_flag == DOWNLOADLOG)
            index = 10;
        else if(main_flag == CLEARLOG)
            index = 11;
        else if(main_flag == SETTIME)
            index = 12;
        else if(main_flag == SETPASSWORD)
            index = 13;      
    write_eeprom(add + 0,time[0]);
    write_eeprom(add + 1,time[1]);
    write_eeprom(add + 2,time[2]);
    write_eeprom(add + 3,time[3]);
    write_eeprom(add + 4,time[4]);
    write_eeprom(add + 5,time[5]);
    write_eeprom(add + 6,time[6]);
    write_eeprom(add + 7,time[7]);
    write_eeprom(add + 8,' ');
    write_eeprom(add + 9,' ');
    write_eeprom(add + 10,gear[index][0]);
    write_eeprom(add + 11,gear[index][1]);
    write_eeprom(add + 12,' ');
    write_eeprom(add + 13,' ');
    write_eeprom(add + 14,'0' + speed / 10);
    write_eeprom(add + 15,'0' + speed % 10);
    add += 16;
}
