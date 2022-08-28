/*
 * RegisterFile.c
 *
 * Created: 26-Aug-22 11:41:30 AM
 * Author : redwa
 */ 

#define F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>
unsigned char registers[10] = {0};

int main(void)
{
	registers[6] = 15;
	unsigned char ekbar=0;
	DDRB = 0x00;
	DDRD = 0x00;
	DDRA = 0xFF;
	DDRC = 0b01111000;
	unsigned prev_clk = 0;
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);
    /* Replace with your application code */
    while (1) {
		unsigned readReg1 = PINB & 7;
		unsigned readReg2 = (PINB >> 3) & 7;
		unsigned writeReg = PIND & 7;
		unsigned writeData = (PIND >> 3) & 15;
		unsigned regWrite = (PINB >> 7) & 1;
		unsigned clk = (PINB >> 6) & 1;
		unsigned showAddress = PINC & 7;
		unsigned memWrite = (PINC >> 7) & 1;

		PORTA = (registers[readReg1] & 15) | (registers[readReg2] << 4);
		PORTC = (registers[showAddress] << 3);
		if(prev_clk==0 && clk==1){
			if(regWrite){

				if(writeReg)registers[writeReg] = writeData;
				_delay_ms(1000);
			}
		}
		if (clk==0)
		{	
			_delay_ms(25);
			if (clk==0)
			{
				if(readReg1 == 6 && memWrite == 0 && (ekbar==0)){
					registers[6]++;
					ekbar=1;
				}
			}
		}
		if (prev_clk==0 && clk==1)
		{
			
			if(readReg1 == 6 && memWrite == 1){
				registers[6]--;
			}
			ekbar=0;
			_delay_ms(786);
		}
		
		
		
		prev_clk = clk;
		
		
    }
}

