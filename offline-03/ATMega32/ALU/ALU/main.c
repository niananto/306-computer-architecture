/*
 * ALU.c
 *
 * Created: 26-Aug-22 11:59:08 AM
 * Author : redwa
 */

#include <avr/io.h>

#define ADD_ 0b00011001
#define SUB_ 0b00000110
#define  OR_ 0b00101110
#define AND_ 0b00101011
#define NOR_ 0b00100001



int main(void)
{
    /* Replace with your application code */
    	DDRB = 0x00;
	DDRC = 0x00;
	DDRA = 0xFF;

	MCUCSR = (1<<JTD);
	MCUCSR = (1<<JTD);

	while (1)
    {
		unsigned char aluOP = PINC & 63;  //6bit aluop C5 - C0
		unsigned char input1 = PINB & 15;   //B3 - B0
		unsigned char input2 = (PINB >> 4) & 15; //B7-B4

		unsigned char result = input1;
		if(aluOP == ADD_){
			result = input1 + input2;
		}
		if(aluOP == SUB_){
			result = input1 - input2;
		}
		if(aluOP == AND_){
			result = input1 & input2;
		}
		if(aluOP == OR_){
			result = input1 | input2;
		}
		if(aluOP == NOR_){
			result = (~(input1 | input2)) & 15;
		}
		result = result & 15;

		if(result == 0){
			result |= (1 << 4);
		}

		PORTA = result;
	}
}

