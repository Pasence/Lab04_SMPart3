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
enum Lock_States{ Start, init, press_pound, rel_pound,y_press, unlock} lock_state;

void Tick_lock(){
	
	switch(lock_state){
		case Start:
			lock_state = init;
			break;
		case init:
			PORTC = 1;
			if (PINA == 0x04)
			{
				lock_state = press_pound;
				
			}
			else if ((PINA & 0x80) == 0x80)
			{
				lock_state = unlock;
			}
			else lock_state = init;
			break;
		case press_pound:
		 	PORTC = 2;
			if (PINA == 0x00)
			{
				lock_state = rel_pound;
			}
			else if ((PINA & 0x80) == 0x80)
                        {
                                lock_state = unlock;
                        }
			else lock_state = init;
			break;
		case rel_pound:
		 	PORTC = 3;	
			if (PINA == 0x02)
                        {
                                lock_state = y_press;
                        }
			else if ((PINA & 0x80) == 0x80)
                        {
                                lock_state = unlock;
                        }
                        else lock_state = init;
			break;
		case y_press:
			PORTC = 4;
			if (PINA == 0x00){
				lock_state = unlock;
			}
			else if ((PINA & 0x80) == 0x80){
				lock_state = unlock;
			}
			else lock_state = init;
			break;
				
		case unlock:
			PORTC = 5;
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
