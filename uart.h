#ifndef SCI_H
#define SCI_H

#define RX_PIN					TRISC7
#define TX_PIN					TRISC6

void init_uart(void);
void putch(unsigned char byte); //transmit 1 byte of data
int puts(const char *s); //transmit string
unsigned char getch(void); //receive 1 byte
unsigned char getch_with_timeout(unsigned short max_time); 
unsigned char getche(void);//receive 1 byte and transmit 1 byte

#endif
