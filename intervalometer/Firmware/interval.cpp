/*
 * interval.cpp
 *
 * Created: 10/18/2014 3:58:01 PM
 *  Author: Lucas
 */ 

#define F_CPU 8000000UL

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//##ORIGINAL##
unsigned char messages[4][8] = 
	{{0xF5, 0x49, 0x61, 0x65, 0xFF, 0xFF, 0xFF, 0xFF},
	{0x41, 0x05, 0x49, 0x61, 0x65, 0xFF, 0xFF, 0xFF},
	{0x04, 0x49, 0xD1, 0xC3, 0xC7, 0xF3, 0xFF, 0xFF},
	{0xF5, 0xD1, 0xC3, 0xC7, 0xF3, 0xFF, 0xFF, 0xFF}};	
		
long ms_delay[4] = {1000,60000,1800000,3600000};
	
int mode = 0;
int count = 0;
const int int_delay = 60;
unsigned char read_val = 0;
bool rise_edge_flag = true;
//unsigned int array_len = sizeof(messages[0]);

int set_sevenseg(unsigned char val){
	for(int i=0;i<8;i++){
		unsigned char curr = 0x01&val;
		PORTA = curr;
		val = val >> 1;
		
		PORTA = 0x02|curr;
		PORTA = 0x00|curr;
		PORTA = 0x04;
		PORTA = 0x00;
	}
	return 1;
}


int start(void){
	while(1){
		//Depending on mode, trigger FET every x seconds
		set_sevenseg(0xFE);
		_delay_ms(500);
		set_sevenseg(0xFF);
		_delay_ms(500);
	}
	return 1;
}
//Mode button pressed
ISR(PCINT0_vect){
	if (rise_edge_flag){
		set_sevenseg(0xFB);
		_delay_ms(int_delay);
		mode++;
		if (mode == 4){
			mode = 0;
		}
		count = 0;
		rise_edge_flag = false;
	}else{
		rise_edge_flag = true;
	}
}
//Start button pressed
ISR(PCINT1_vect){
	set_sevenseg(0xFB);
	_delay_ms(int_delay);
	start();
	
}

int main(void)
{
	//unsigned char read_val;
	//Set PA7, PA2, PA1, and PA0 of Port A as output, rest as input **Subject to change**
	DDRA = 0b10000111;
	
	//Set all pins of Port B as output **Subject to change**
	DDRB = 0b00000000;
	
	//Enable pin change interrupts
	GIMSK |= (1<<PCIE0)|(1<<PCIE1);
	
	//Listen for interrupts on pins 10 and 5
	PCMSK0 |= (1<<PCINT3);
	PCMSK1 |= (1<<PCINT10);
	
	//Enable all interrupts
	sei();
		
	//Main Loop
    while(1){
		
		//PORTA |= 0b10000000; //FOR TESTING
		
		_delay_ms(700); //##ORIGINAL##
		set_sevenseg(messages[mode][count]);
		count++;
		if (count==8){
			count = 0;
		}
    }
}

