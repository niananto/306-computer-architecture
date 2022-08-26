/*
 * PCJumpBranch.c
 *
 * Created: 26-Aug-22 11:04:30 AM
 * Author : redwa
 */ 

#define  F_CPU 1000000
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0x00;
	DDRA = 0xFF;
	DDRD = 0x00;
	DDRC = 0x00;
	MCUSR = (1<<JTD);
	MCUSR = (1<<JTD);
	
	unsigned char prev_clk = 0;
	unsigned char pc = 0;
    /* Replace with your application code */
    while (1) {
		unsigned char curr_clk = (PIND >> 7) & 1;
		unsigned char jmpAddress = PINB;
		unsigned char immediate = PIND & 15;
		unsigned char jump = (PIND >> 6) & 1;
		unsigned char branch = (PIND >> 5) & 1;
		unsigned char bneq = (PIND >> 4) & 1;
		unsigned char ALUzero = PINC & 1;
		if(curr_clk ==1 && prev_clk==0){
			pc = pc + 1;
			if(branch){
				if(ALUzero!=bneq){
					pc = pc + immediate;
				}
			}
			if(jump){
				pc = jmpAddress;
			}
			PORTA = pc;
			_delay_ms(5000);
		}
		prev_clk = curr_clk;
    }
}

