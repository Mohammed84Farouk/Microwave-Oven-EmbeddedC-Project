#include "Io.h"
#include "tm4c123gh6pm.h"

char Err;
bool SW3, SW2, SW1;

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
	SysTick_wait(80000);          //delay 1ms if it operates on 80MHz
	}
}

void get_weight(){
	int W;
	stdin W;
	if (W < 1 || W > 9)
	{	
		return -1;
	}
	elseif (W >= 1 && W <= 9)
	{
		return W; 
	}
}

bool ClosedDoor(){
	if (SW3)
	{
		return true;
	}
	else
		return false;
}

bool Check(){
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
	}
	while(time--){
		if (!Check())
		{
			state = pause();
		}
		if (SW3)
		{
			state = start_cooking();
		}
	}
	return true;
}

void special_time(){
	int min1 = 0, min2 = 0, sec1 = 0, sec2 = 0;
	int sum;		            
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
	sum = (min1:min2) * 60 + (sec1:sec2) 		// ex. 25:23 ----> 25 * 60 + 23
	return sum;
}