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
enum Lock_States{ Start, init, press_pound, rel_pound, y_press, y_rel, unlock, lock} lock_state;

void Tick_lock(){
	
	switch(lock_state){
		case Start:
			lock_state = init;
			break;
		case init:
			PORTC = 1;
			if ((PINA & 0x07) == 0x04)
			{
				lock_state = press_pound;
				
			}
			else if ((PINA & 0x80) == 0x80)
			{
				lock_state = lock;
			}
			else lock_state = init;
			break;
		case press_pound:
		 	PORTC = 2;
			if ((PINA & 0x07) == 0x00)
			{
				lock_state = rel_pound;
			}
			else if ((PINA & 0x80) == 0x80)
                        {
                                lock_state = lock;
                        }
			else lock_state = init;
			break;
		case rel_pound:
		 	PORTC = 3;	
			if ((PINA & 0x07) == 0x02)
                        {
                                lock_state = y_press;
                        }
			else if ((PINA & 0x80) == 0x80)
                        {
                                lock_state = lock;
                        }
                        else lock_state = init;
			break;
		case y_press:
			PORTC = 4;
			if ((PINA & 0x07) == 0x00){
				lock_state = y_rel;
			}
			else if ((PINA & 0x80) == 0x80){
				lock_state = lock;
			}
			else lock_state = init;
			break;
		case y_rel:
			PORTC = 5;
			if ((PINA & 0x80) == 0x80){
                                lock_state = lock;
                        }
			else {
				lock_state = unlock;
				PORTB = 1;
			}
			break;
		case unlock:
			PORTC = 6;
			break;
		case lock:
			PORTC = 7;
			PORTB = 0;
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
	case y_rel:
		break;
	case y_press:
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
	PORTB = 0;
	lock_state = Start;
    while (1) {
	Tick_lock();
    }
    return 1;
}
