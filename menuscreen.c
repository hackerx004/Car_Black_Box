/*
 * File:   menuscreen.c
 * Author: jahna
 *
 * Created on 21 September, 2024, 2:52 PM
 */


#include <xc.h>
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"
#include "external_eeprom.h"
#include "rtc.h"
#include "uart.h"

int delay = 0,index = 0,flag = 1,result;
unsigned char *menu[6] = {"View log","Download log","Clear log","Set time","Set password"},prekey;
static unsigned char add = 4,add1 = 4;
static int i;

int press(unsigned char key)
{
    if(key != ALL_RELEASED)
    {
        prekey = key;
        if(delay++ == 250)
        {
            //delay = 0;
            return LONGPRESS;
        }
    }
    else if(delay > 0 && delay < 250)
    {
        delay = 0;
        return SHORTPRESS;
    }
    else delay = 0; 
}

void menuscreen(unsigned char key)
{   
    if(flag)
        clcd_putch(0x7E,LINE1(0));
    else
        clcd_putch(0x7E,LINE2(0));
    clcd_print(menu[index],LINE1(3));
    clcd_print(menu[index + 1],LINE2(3));

    int result = press(key);
    if(prekey == MK_SW5 && result == SHORTPRESS) /*scroll up*/
    {
        prekey = 0;
        CLEAR_DISP_SCREEN;
        if(flag && index > 0)
            index--;
        else
            flag = 1;
    }
    else if(prekey == MK_SW6 && result == SHORTPRESS)  /*scroll down*/
    {
        prekey = 0;
        CLEAR_DISP_SCREEN;
        if(!flag && index < 3)
            index++;
        else 
            flag = 0;
    }    
    else if(prekey == MK_SW5 && result == LONGPRESS) /*log in*/
    {
        prekey = 0;
        CLEAR_DISP_SCREEN; 
        
        if(index == 0 && flag)  
            main_flag = VIEWLOG;
        else if(index == 0 && flag == 0 || index == 1 && flag)
            main_flag = DOWNLOADLOG;
        else if(index == 1 && flag == 0 || index == 2 && flag)
            main_flag = CLEARLOG;
        else if(index == 2 && flag == 0 || index == 3 && flag)
            main_flag = SETTIME;
        else if(index == 3 && flag == 0)
            main_flag = SETPASSWORD;
    } 
    else if(prekey == MK_SW6 && main_flag == MENUSCREEN && result == LONGPRESS)
    {
        prekey = 0;
        CLEAR_DISP_SCREEN; 
        main_flag = DASHBOARD;
    }
}

void viewlog(unsigned char key)
{
    int result = press(key);
    clcd_print("#  view log",LINE1(0));
    unsigned char data;
    
    data = read_eeprom(add + 0);
    clcd_putch(data,LINE2(0));
    
    data = read_eeprom(add + 1);
    clcd_putch(data,LINE2(1));
    
    data = read_eeprom(add + 2);
    clcd_putch(data,LINE2(2));
    
    data = read_eeprom(add + 3);
    clcd_putch(data,LINE2(3));
    
    data = read_eeprom(add + 4);
    clcd_putch(data,LINE2(4));
    
    data = read_eeprom(add + 5);
    clcd_putch(data,LINE2(5));
    
    data = read_eeprom(add + 6);
    clcd_putch(data,LINE2(6));
    
    data = read_eeprom(add + 7);
    clcd_putch(data,LINE2(7));
    
    data = read_eeprom(add + 8);
    clcd_putch(data,LINE2(8));
    
    data = read_eeprom(add + 9);
    clcd_putch(data,LINE2(9));
     
    data = read_eeprom(add + 10);
    clcd_putch(data,LINE2(10));
    
    data = read_eeprom(add + 11);
    clcd_putch(data,LINE2(11));
    
    data = read_eeprom(add + 12);
    clcd_putch(data,LINE2(12));
    
    data = read_eeprom(add + 13);
    clcd_putch(data,LINE2(13));
    
    data = read_eeprom(add + 14);
    clcd_putch(data,LINE2(14));
    
    data = read_eeprom(add + 15);
    clcd_putch(data,LINE2(15));
    
       if(prekey == MK_SW5 && add != 4 && result == SHORTPRESS) // scroll up
       {
           prekey = 0;
           add -= 16;
       }
        if(prekey == MK_SW6 && add < 164 && result == SHORTPRESS) // scroll down 
        {
            prekey = 0;
            add += 16;
        }
        else if(prekey == MK_SW6 && result == LONGPRESS)
        {
            prekey = 0;
            CLEAR_DISP_SCREEN;
            main_flag = MENUSCREEN;
        }
        
}

void downloadlog(unsigned char key)
{
    int store = 0;
    if(!store && key == ALL_RELEASED)
    {
        store_event();
        store = 1;
    }
    int result = press(key);
    unsigned char data;
    clcd_print("Downloading...",LINE1(0));
    if(i++ < event_count)
    {
        data = read_eeprom(add + 0);
        putch(data);

        data = read_eeprom(add + 1);
        putch(data);

        data = read_eeprom(add + 2);
        putch(data);

        data = read_eeprom(add + 3);
        putch(data);

        data = read_eeprom(add + 4);
        putch(data);

        data = read_eeprom(add + 5);
        putch(data);

        data = read_eeprom(add + 6);
        putch(data);

        data = read_eeprom(add + 7);
        putch(data);

        data = read_eeprom(add + 8);
        putch(data);

        data = read_eeprom(add + 9);
        putch(data);

        data = read_eeprom(add + 10);
        putch(data);

        data = read_eeprom(add + 11);
        putch(data);

        data = read_eeprom(add + 12);
        putch(data);

        data = read_eeprom(add + 13);
        putch(data);

        data = read_eeprom(add + 14);
        putch(data);

        data = read_eeprom(add + 15);
        putch(data);
        
        puts("\n\r");
        add += 16;
    } 
    
//    if(prekey == MK_SW6 && result == LONGPRESS)
//    {
//        prekey = 0;
//        CLEAR_DISP_SCREEN;
//        main_flag = MENUSCREEN;
//    }
}

void clearlog(unsigned char key)
{
    int store = 0;
    if(!store)
    {
        store_event();
        store = 1;
    }
    clcd_print("Clearing...",LINE1(0));
    event_count = 0;
    if(time1 == 0)
    TMR0ON = 1;
    if(time1 == 5)
    {
        TMR0ON = 0;
        time1 = 0;
         CLEAR_DISP_SCREEN;
        main_flag = MENUSCREEN;
    }
//    int result = press(key);
//    if(prekey == MK_SW6 && result == LONGPRESS)
//    {
//        prekey = 0;
//        main_flag = MENUSCREEN;
//    }
}

int count = 0,hour_blink = 0,min_blink = 0,sec_blink = 1,wait = 0,flag2 = 0,flag3 = 0;
unsigned char hour,second,minute;

void settime(unsigned char key)
{
    int store = 0;
    if(!store)
    {
        store_event();
        store = 1;
    }
    clcd_print("Set time",LINE1(3));
    if(!flag2)
    {
        hour = read_ds1307(HOUR_ADDR);
        minute = read_ds1307(MIN_ADDR);
        second = read_ds1307(SEC_ADDR);
        hour = ((hour >> 4) * 10) + (hour & 0x0F);
        minute = ((minute >> 4) * 10) + (minute & 0x0F);
        second = ((second >> 4) * 10) + (second & 0x0F);
        flag2 = 1;
    }
 
    if(wait++ == 10)
    {
        wait = 0;
        flag3 = !flag3;
    }   
    if(!flag3)
    {
        clcd_putch('0' + (hour / 10),LINE2(3));
        clcd_putch('0' + (hour % 10),LINE2(4));
        clcd_putch(':',LINE2(5));
        clcd_putch('0' + (minute / 10),LINE2(6));
        clcd_putch('0' + (minute % 10),LINE2(7));
        clcd_putch(':',LINE2(8));
        clcd_putch('0' + (second / 10),LINE2(9));
        clcd_putch('0' + (second % 10),LINE2(10));
    }
    else 
    {
        if(sec_blink)
        {
            clcd_putch('0' + (hour / 10),LINE2(3));
            clcd_putch('0' + (hour % 10),LINE2(4));
            clcd_putch(':',LINE2(5));
            clcd_putch('0' + (minute / 10),LINE2(6));
            clcd_putch('0' + (minute % 10),LINE2(7));
            clcd_putch(':',LINE2(8));
            clcd_putch(' ',LINE2(9));
            clcd_putch(' ',LINE2(10));
        }
        else if(min_blink)
        {
            clcd_putch('0' + (hour / 10),LINE2(3));
            clcd_putch('0' + (hour % 10),LINE2(4));
            clcd_putch(':',LINE2(5));
            clcd_putch(' ',LINE2(6));
            clcd_putch(' ',LINE2(7));
            clcd_putch(':',LINE2(8));
            clcd_putch('0' + (second / 10),LINE2(9));
            clcd_putch('0' + (second % 10),LINE2(10));  
        }
        else if(hour_blink)
        {
            clcd_putch(' ',LINE2(3));
            clcd_putch(' ',LINE2(4));
            clcd_putch(':',LINE2(5));
            clcd_putch('0' + (minute / 10),LINE2(6));
            clcd_putch('0' + (minute % 10),LINE2(7));
            clcd_putch(':',LINE2(8));
            clcd_putch('0' + (second / 10),LINE2(9));
            clcd_putch('0' + (second % 10),LINE2(10));
        }
    
    }
    
    int result = press(key);
    if(prekey == MK_SW6 && result == SHORTPRESS) //changing field shortpress
    {
        count++;
        prekey = 0;
        if(count == 0)
        {
            sec_blink = 1;
            min_blink = 0;
            hour_blink = 0;
        }
        else if(count == 1)
        {
            sec_blink = 0;
            min_blink = 1;
            hour_blink = 0;
        }
        else if(count == 2)
        {
            sec_blink = 0;
            min_blink = 0;
            hour_blink = 1;
        }
    }
    
    else if(prekey == MK_SW5 && result == SHORTPRESS) //increase shortpress
    {
        prekey = 0;
        if(count == 0 && second++ > 58) //sec field
            second = 0;
        else if(count == 1 && minute++ > 58) 
            minute = 0;
        else if(count == 2 && hour++ > 22)
            hour = 0; 
    }
    
    else if(prekey == MK_SW5 && result == LONGPRESS)  //setting time MK_SW5 Longpress
    {
        prekey = 0;
        hour = ((hour / 10) << 4) | (hour % 10); 
        minute = ((minute / 10) << 4) | (minute % 10);
        second = ((second / 10) << 4) | (second % 10);
        write_ds1307(HOUR_ADDR,hour);
        write_ds1307(MIN_ADDR,minute);
        write_ds1307(SEC_ADDR,second);
        CLEAR_DISP_SCREEN;
        main_flag = MENUSCREEN;
    }
    else if(prekey == MK_SW6 && result == LONGPRESS)
    {
        prekey = 0;
        CLEAR_DISP_SCREEN;
        main_flag = MENUSCREEN;
    }
}

char new_pass1[5],new_pass2[5];
int wait1 = 0,key_count = 0,key_count1 = 0,disp = 0,flag1 = 0;

void setpassword(unsigned char key)
{
    int store = 0;
    if(!store)
    {
        store_event();
        store = 1; 
    }
    int result = press(key);
    if(key_count < 4 && !flag1)
        {
            clcd_print("Enter Password  ",LINE1(0));     
            if(wait1++ == 1000)
            {
                clcd_putch('_',LINE2(key_count));
            }
            else if(wait1++ == 2000)
            {
                wait1 = 0;
                clcd_putch(' ',LINE2(key_count));
            }

            if(prekey == MK_SW5 && result == SHORTPRESS)
             {
                prekey = 0;
                clcd_putch('*',LINE2(key_count));
                new_pass1[key_count] = '0';
                key_count++;
            }
            else if(prekey == MK_SW6 && result == SHORTPRESS)
            {
                prekey = 0;
                clcd_putch('*',LINE2(key_count));
                new_pass1[key_count] = '1';
                key_count++;   
            }
        }
    if(key_count == 4 && !flag1)
    {
        if(!disp)
            CLEAR_DISP_SCREEN;
        if(key_count1 < 4)
        {
            disp = 1;
            clcd_print("Re-enter",LINE1(0));
            if(wait++ == 1000)
            {
                clcd_putch('_',LINE2(key_count1));
            }
            else if(wait++ == 2000)
            {
                wait = 0;
                clcd_putch(' ',LINE2(key_count1));
            }

            if(prekey == MK_SW5 && result == SHORTPRESS)
             {
                prekey = 0;
                clcd_putch('*',LINE2(key_count1));
                new_pass2[key_count1] = '0';
                key_count1++;
            }
            else if(prekey == MK_SW6 && result == SHORTPRESS)
            {
                prekey = 0;
                clcd_putch('*',LINE2(key_count1));
                new_pass2[key_count1] = '1';
                key_count1++;   
            }
            else if(key_count1 == 4)
                flag1 = 1;
        }
    }
    if(key_count1 == 4)
    {
        new_pass1[4] = '\0',new_pass2[4] = '\0';
        if(!(strcmp(new_pass1,new_pass2)))
        {
            for(int a = 0;a < 4;a++)
                write_eeprom(a,new_pass1[a]);

            clcd_print("Password updated",LINE1(0));
            clcd_print("     ",LINE2(0));
            
            if(prekey == MK_SW6 && result == LONGPRESS)
            {
                key_count = 0,key_count1 = 0;
                prekey = 0;
                CLEAR_DISP_SCREEN;
                main_flag = MENUSCREEN;
            }
        }
        else 
        {
            CLEAR_DISP_SCREEN;
            clcd_print("Wrong Password",LINE1(0));
            
            if(time1 == 0)
                TMR0ON = 1;
            if(time1 == 5)
            {
                TMR0ON = 0;
                time1 = 0;
                CLEAR_DISP_SCREEN;
                main_flag = MENUSCREEN;
            }
            
//            if(prekey == MK_SW6 && result == LONGPRESS)
//            {
//                CLEAR_DISP_SCREEN;
//                prekey = 0;
//                key_count = key_count1 = 0;
//                main_flag = MENUSCREEN;
//            }      
        }
    }
            
    }
    