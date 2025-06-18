/* 
 * File:   main.h
 * Author: jahna
 *
 * Created on 20 September, 2024, 9:31 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#define  DASHBOARD       0
#define  LOGINSCREEN     1
#define  MENUSCREEN      2

#define  LONGPRESS       1
#define  SHORTPRESS      0

#define  VIEWLOG          3
#define  DOWNLOADLOG      4
#define  CLEARLOG         5
#define   SETTIME         6
#define   SETPASSWORD     7


void dashboard(void);
void loginscreen(void);
void menuscreen(unsigned char key);
int press(unsigned char key);
void viewlog(unsigned char key);
void downloadlog(unsigned char key);
void clearlog(unsigned char key);
void settime(unsigned char key);
void setpassword(unsigned char key);
void store_event(void);



int main_flag = 0,seconds = 59,time1 = 0,event_count = 0,menu_flag = 0,type;
unsigned char key,prekey;
unsigned char password[5] = "0000";



#endif	/* MAIN_H */

