/*
 * File:   main.c
 * Author: jahna
 *
 * Created on 19 September, 2024, 9:23 AM
 */


#include <xc.h>
#include "adc.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "main.h"
#include "timer0.h"
#include "i2c.h"
#include "rtc.h"
#include "uart.h"
#include "external_eeprom.h"


void init_config(void) {
    PEIE = 1;
    init_clcd();
    init_matrix_keypad();
    init_adc();
    init_timer0();
    init_i2c();
    init_ds1307();
    init_uart();
    GIE = 1;
}





void main(void) {
    init_config();
    for(int i = 0;i < 4;i++)
        write_eeprom(i,password[i]);
    store_event();
    while (1) {
        key = read_switches(LEVEL_CHANGE);
        //type = press(key);
        
        if (key == MK_SW5 && main_flag == DASHBOARD) {
            CLEAR_DISP_SCREEN;
            main_flag = LOGINSCREEN;
        }
//        else if(key == MK_SW7 && main_flag == MENUSCREEN)
//        {
//            CLEAR_DISP_SCREEN;
//            main_flag = DASHBOARD;
//        }
    
          
        if (main_flag == DASHBOARD)
            dashboard();
        else if (main_flag == LOGINSCREEN)
            loginscreen();
        else if (main_flag == MENUSCREEN)
            menuscreen(key);
        else if(main_flag == VIEWLOG)
            viewlog(key);
        else if(main_flag == DOWNLOADLOG)
            downloadlog(key);
        else if(main_flag == CLEARLOG)
            clearlog(key);
        else if(main_flag == SETTIME)
            settime(key);
        else if(main_flag == SETPASSWORD)
            setpassword(key);
        }       
    return;
}
