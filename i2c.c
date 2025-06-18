
#include <xc.h>

void init_i2c(void)
{
	/* Set SCL and SDA pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;
	/* Set I2C master mode */
	SSPCON1 = 0x28;

	SSPADD = 0x31;
	/* Use I2C levels, worked also with '0' */
	CKE = 0;
	/* Disable slew rate control  worked also with '0' */
	SMP = 1;
	/* Clear SSPIF interrupt flag */
	SSPIF = 0;
	/* Clear bus collision flag */
	BCLIF = 0;
}

void i2c_idle(void) /* check whether instruction completed or not */
{
	while (!SSPIF); /* 0 instruction not completed */
	SSPIF = 0;      /* 1 instruction completed */
}

void i2c_ack(void)
{
	if (ACKSTAT)
	{
		/* Do debug print here if required */
	}
}

void i2c_start(void) /* to start communication */ 
{
	SEN = 1;
	i2c_idle();
}

void i2c_stop(void) /* to stop communication */
{
	PEN = 1;
	i2c_idle();
}

void i2c_rep_start(void) /* to initiate repeat start */
{
	RSEN = 1;
	i2c_idle();
}

void i2c_write(unsigned char data) /* to transmit the data */
{
	SSPBUF = data;
	i2c_idle();
}

void i2c_rx_mode(void) /*to put master on receive mode */
{
	RCEN = 1;
	i2c_idle();
}

void i2c_no_ack(void)
{
	ACKDT = 1;
	ACKEN = 1;
}

unsigned char i2c_read(void) /* to receive the data */
{
	i2c_rx_mode();
	i2c_no_ack();

	return SSPBUF;
}