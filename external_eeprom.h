#ifndef EXT_EEP_H
#define EXT_EEP_H

#define EEPROM_READ		0xA1
#define EEPROM_WRITE    0xA0


void write_eeprom(unsigned char address1,  unsigned char data);
unsigned char read_eeprom(unsigned char address1);

#endif