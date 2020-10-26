/*	Author: pasen001
 *  Partner(s) Name: Peter John Asence
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
enum Lock_States{ Start, init, press_pound, rel_pound, unlock} lock_state;

void Tick_lock(){
	unsigned char x_but;
	unsigned char y_but;
	unsigned char pnd_but;
	unsigned char lock_but;
	x_but = PINA & 0x01;
	y_but = (PINA & 0x02) >> 1;
	pnd_but = (PINA & 0x04) >> 2;
	lock_but = (PINA & 0x80) >> 7;
	switch(lock_state){
		case Start:
			lock_state = init;
			break;
		case init:
			PORTC = 1;
			if (pnd_but == 1 && x_but == 0 && y_but ==0 && lock_but == 0)
			{
				lock_state = press_pound;
				
			}
			else if (pnd_but == 0 && x_but == 0 && y_but ==0 && lock_but == 1)
			{
				lock_state = unlock;
			}
			else lock_state = init;
			break;
		case press_pound:
		 	PORTC = 2;
			if (pnd_but == 0 && x_but == 0 && y_but ==0 && lock_but == 0)
			{
				lock_state = rel_pound;
			}
			else if (pnd_but == 0 && x_but == 0 && y_but ==0 && lock_but == 1)
                        {
                                lock_state = unlock;
                        }
			else lock_state = init;
			break;
		case rel_pound:
		 	PORTC = 3;	
			if (pnd_but == 0 && x_but == 0 && y_but ==1 && lock_but == 0)
                        {
                                lock_state = unlock;
                        }
			else if (pnd_but == 0 && x_but == 0 && y_but ==0 && lock_but == 1)
                        {
                                lock_state = unlock;
                        }
                        else lock_state = init;
			break;
		case unlock:
			PORTC = 4;
			PORTB = 1;
			break;
		default:
			lock_state = Start;
			break;
	}//transition actions
	switch(lock_state){

	case Start:
		
		break;
	case init: 
		
		break;
	case press_pound:
		
		break;
	case rel_pound:
		
		break;
	case unlock:
		
		
		break;
	default:
		break;
	}// state actions	
}
	
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	lock_state = Start;
    while (1) {
	Tick_lock();
    }
    return 1;
}
