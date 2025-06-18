/*
 * File:   loginscreen.c
 * Author: jahna
 *
 * Created on 21 September, 2024, 2:52 PM
 */

#include <xc.h>
#include <string.h>
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"
#include "external_eeprom.h"

char org_pass[5],user_pass[5];
int flag = 0,delay = 0,key_count = 0,attempts = 3,delay1 = 0;
unsigned char key;

void loginscreen(void)
{
    for(int k = 0;k < 4;k++)
        org_pass[k] = read_eeprom(k);
    org_pass[4] = '\0';
    if(attempts != 0)
    {
        if(key_count < 4)
        {
            clcd_print("Enter Password  ",LINE1(0));     
            if(delay++ == 100 && !flag)
            {
                clcd_putch('_',LINE2(key_count));
            }
            else if(delay++ == 200 && !flag)
            {
                delay = 0;
                clcd_putch(' ',LINE2(key_count));
            }
            if(time1 == 0)
                TMR0ON = 1;
            if(time1 <= 5)
            {
                TMR0ON = 0;
                key = read_switches(STATE_CHANGE);
                time1 = 0;
                if(key == MK_SW5)
                {
                    clcd_putch('*',LINE2(key_count));
                    user_pass[key_count] = '0';
                    key_count++;
                }
                else if(key == MK_SW6)
                {
                    clcd_putch('*',LINE2(key_count));
                    user_pass[key_count] = '1';
                    key_count++;   
                }
            }
            else 
            {
                TMR0ON = 0;
                main_flag = DASHBOARD;
                return;
            }
        }
        else if(key_count == 4)
        {
            user_pass[key_count] = '\0';
            int result = strcmp(org_pass,user_pass);
            if(!result)
            {
                key_count = 0;
                main_flag = MENUSCREEN;
                CLEAR_DISP_SCREEN;
                return;
            }
            else
            {
                flag = 1;
                clcd_print("Wrong Password  ",LINE1(0));
                clcd_print("Att left ",LINE2(0));
                clcd_putch('0' + ((attempts-1) / 10), LINE2(10));
                clcd_putch('0' + ((attempts-1) % 10), LINE2(11));
                if(delay1++ == 1000)
                {
                    CLEAR_DISP_SCREEN;
                    delay1 = 0;
                    key_count = 0;
                    --attempts;
                }
            }
        }
    }
    else
    {
        TMR0ON = 1;
        if(seconds != 0)
        {
            clcd_print("No attempts left",LINE1(0));
            clcd_print("Wait for",LINE2(0));
            clcd_putch('0' + seconds / 10,LINE2(10));
            clcd_putch('0' + seconds % 10,LINE2(11));
        }
        else if(seconds == 0)
        {
            time1 = key_count = 0;
            TMR0ON = 0; 
            seconds = 59;
            attempts = 3;
            CLEAR_DISP_SCREEN;
        }
    }  
}