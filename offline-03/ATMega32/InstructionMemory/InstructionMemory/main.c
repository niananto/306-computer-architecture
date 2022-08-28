/*
 * InstructionMemory.c
 *
 * Created: 26-Aug-22 10:54:57 AM
 * Author : redwanul karim
 */ 

#include <avr/io.h>
#define F_CPU 1000000
#include<util/delay.h>

unsigned int instructions [] = {
	0x5023,
	0x203e,
	0x8231,
	0xd234,
	0xb135,
	0x6323,
	0xf331,
	0x3341,
	0x4160,
	0xe441,
	0x0334,
	0x6620,
	0x6630,
	0x4150,
	0x7131,
	0xc531,
	0xa225,
	0x0630,
	0x9352,
	0x0620,
	0x4160,
	0x1138};

int main(void){
	DDRB = 0x00;
	DDRA = 0xFF;
	DDRD = 0xFF;
	
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);
    /* Replace with your application code */
    while (1) {
		unsigned char pc = PINB;  // input pc
		PORTA = instructions[pc] & 255; // destination reg a3-a0, source2 a7-a4, source1 c3-c0, opcode c7-c4
		unsigned int temp = instructions[pc] >> 8;
		PORTD = temp & 255; 
		_delay_ms(500);
    }
}

