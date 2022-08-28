/*
 * ControlUnit.c
 *
 * Created: 26-Aug-22 11:23:29 AM
 * Author : redwa
 */ 

#include <avr/io.h>


long controlBits[] = {0x06c19, 0x00306, 0x06006, 0x00106, 0x00080, 0x06019, 0x03019, 0x0406e,0x04059, 0x0406b, 0x0602e, 0x04061, 0x0602b, 0x04046, 0x0c000, 0x1c000};
int main(void){
	DDRB = 0x00;
	DDRA = 0xFF;
	DDRC = 0xFF;
	DDRD = 0xFF;
	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);
    /* Replace with your application code */
    while (1) {
		unsigned char opcode = PINB;
		opcode = opcode & 15;
		PORTA = controlBits[opcode] & 255;
		PORTC = (controlBits[opcode] >> 8) & 255;
		PORTD = ((controlBits[opcode] >> 16) & 1) << 7;
    }
}

