/*
 * File:   external_eeprom.c
 * Author: jahna
 *
 * Created on 28 September, 2024, 8:39 AM
 */


#include <xc.h>
#include "main.h"
#include "i2c.h"
#include "external_eeprom.h"

void write_eeprom(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(EEPROM_WRITE);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
    for(int delay = 3000;delay--;);
}

unsigned char read_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(EEPROM_WRITE);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(EEPROM_READ);
	data = i2c_read();
	i2c_stop();

	return data;
}