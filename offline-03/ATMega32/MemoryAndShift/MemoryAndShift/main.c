/*
 * MemoryAndShift.c
 *
 * Created: 26-Aug-22 12:10:44 PM
 * Author : redwa
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include <util/delay.h>

unsigned char data[16];

int main(void)
{
	DDRB = 0xFF;
	DDRD = 0xC0;
	DDRA = 0xFF;
	DDRC = 0x00;
	MCUSR = 1 << JTD;
	MCUSR = 1 << JTD;
	
	unsigned char prev_clk = 0;

    while (1) 
    {
		unsigned char alu = PINB & 15;
		unsigned char dataWrite = (PINB >> 4) & 15;		//READ REG 2
		unsigned char memRead = (PIND) & 1;
		unsigned char memWrite = (PIND >> 1) & 1;
		unsigned char shiftControl = (PIND >> 2) & 1;
		unsigned char shiftRight = (PIND >> 3) & 1;
		unsigned char shamt = (PINC >> 4) & 15;
		unsigned char shiftData = (PINC) & 15;			//READ REG1
		unsigned char memToReg = (PIND >> 4) & 1;
		unsigned char clk = (PIND >> 5) & 1;
		unsigned char dataOut = data[alu];
		
		if(memToReg == 0){
			dataOut = alu;		
		}
		
		unsigned char shiftResult = shiftData;
		
		if(shiftRight)shiftResult = shiftResult >> shamt;
		else shiftResult = shiftResult << shamt;
		
		if(shiftControl){
			dataOut = shiftResult;
		}
		
		PORTA = (dataOut << 4);
		
		if(memWrite && (prev_clk == 0 && clk == 1)){
			data[alu] = dataWrite;
			_delay_ms(1000);
		}
		
		prev_clk = clk;
	}
		
}

