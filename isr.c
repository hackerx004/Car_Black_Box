#include <xc.h>
#include "main.h"

void __interrupt() isr(void)
{
	static unsigned short count;
     
	if (TMR0IF)
	{
		TMR0 = TMR0 + 8;

		if (count++ == 20000)
		{
			count = 0;
            seconds--;
            time1++;
		}
		TMR0IF = 0;
	}
    if(RCIF)
    {
        if(OERR)
            OERR = 0;
        RCIF = 0;
    }
}