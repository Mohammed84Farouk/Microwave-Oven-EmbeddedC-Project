#include "portF.c"
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "portA.c"

#define NVIC_ST_CTRL_R          (*((volatile unsigned long *)0xE000E010))
#define NVIC_ST_RELOAD_R        (*((volatile unsigned long *)0xE000E014))
#define NVIC_ST_CURRENT_R       (*((volatile unsigned long *)0xE000E018))

char Err, SW3, ClosedDoor;

void SysTick_wait(unsigned long delay){
	NVIC_ST_CTRL_R = 0x00;
	NVIC_ST_RELOAD_R = delay - 1;
	NVIC_ST_CURRENT_R = 0x00;
	NVIC_ST_CTRL_R = 0x05;
	while ((NVIC_ST_CTRL_R & 0x00010000) == 0){
	}
}

void generic_delay(unsigned long time){
	for (int i = 0; i < time; i++){
	SysTick_wait(16000);         			 //delay 1ms if it operates on 16MHz
	}
}

unsigned char get_weight(){
	do{
		key=keypad_getkey();
		delayMs(200);   					//wait for the debounce
	}
	while(key==0);
	return key;
}

// initialize SW3 
void init_SW3(){
	init_portA();
	if ((GPIO_PORTA_DATA_R & 0x11) == 0x01){
		SW3 = 1;	
	} 
	else { 
		SW3 = 0;
	}	
}

char ClosedDoor(){
	init_SW3();
	if (SW3){
		ClosedDoor = 1;
		return true;
	}
	else{
		ClosedDoor = 0;
		return false;
	}
}

char Check(){
	if (SW2 && ClosedDoor)
	{
		return true;
	}
	else 
		return false;
}
int set_time(int time){
	int state;
	if (!Check()){
			state = pause();
			if (state == idle)
			{
				return = 0;
			}
	}
	while(time--){
		delayMs(200);
		if (!Check())
		{
			state = pause();
			if (state == idle)	
			{
				return = 0;
			}
		}
		if (SW3)
		{
			state = start_cooking();
		}
	}
	if (time == 0){
		GPIO_PORTA_DATA_R = 0x02;			// PA1 = 1
	}
	return true;
}

void special_time(){
	int min1 = 0, min2 = 0, sec1 = 0, sec2 = 0;
	int sum = 0;		            
	lcd.print(Enter time in format of MM:SS);          // format (min1 min2:sec1 sec2)
	for (int i = 0; i < 4; ++i)
	{
		stdin sec2;
		sec1 = sec2 << 1;
		min2 = sec1 << 1;
		min1 = min2 << 1;
	}
	if (sec1 > 6 || sec2 > 6)
	{
		lcd.print(Err)
	}
	sum = (min1:min2) * 60 + (sec1:sec2) 			// ex. 25:23 ----> 25 * 60 + 23
	return sum;
}