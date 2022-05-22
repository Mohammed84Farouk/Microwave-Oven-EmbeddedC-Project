#include "portF.h"
#include "tm4c123gh6pm.h"
#include "stdint.h"
#include "buzzer.h"

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
unsigned char SW3_input(void){                                                                                    /***/
    return GPIO_PORTA_DATA_R&0x08;
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
int set_timer(int time){
    int i, m, s, flag = 0;
    unsigned char mins, secs, minutes[2], seconds[2];
    for(i=time; i>=0; i--){
        LCD_command(1);
        lcd_string(timer);
        m = i/60;
        s = i%60;
        if (m>9) lcd_data((unsigned char)('0' + (m/10)));
        else lcd_data('0');
        lcd_data((unsigned char)('0' + (m%10)));
        lcd_data(':');
        if (s>9) lcd_data((unsigned char)('0' + (s/10)));
        else lcd_data('0');
        lcd_data((unsigned char)('0' + (s%10)));
        delayMs(1000);
        sw=SW3_input();                    //make it SW3 in the future
        if(sw!=0x10){
           	LCD_command(1);
            lcd_string("Pausing");
            while(sw!=0x01) sw=SW1_input();
        }
    }
    //timer is done and is now 00:00
    LCD_command(1);
    return 0;
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