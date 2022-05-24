#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "Io.h"
#include "LCD.h"
#include "lcdDef.h"
#include "keypad.h"
#include "buzzer.h"

unsigned char sw1, sw2, sw3, w, tt[4], value;
char idle[]="Choose from A-D", clearing[]="Clearing...", ChickW[]="Chicken Weight? ", BeefW[]="Beef Weight? ", err[]="Err", timer[]="Timer: ", popC[]="PopCorn";																												/**********************/
uint8_t key;      								//to recieve the returned character
int state, m1, m0, s1, s0, temp;

void delayMs(uint32_t n) {				/* delay n milliseconds (16 MHz CPU clock) */
	uint32_t i, j;
	for(i = 0 ; i < n; i++)
		for(j = 0; j < 3180; j++){} /* do nothing for 1 ms */
}
void delayUs(uint32_t n){					/* delay n microseconds (16 MHz CPU clock) */
	uint32_t i, j;
	for(i = 0 ; i < n; i++)
		for(j = 0; j < 3; j++) {} 	/* do nothing for 1 us */
}
void error(void){
    clear();							//clear the screen
    moveCursor(1, 1);  				//lcd cursor location:first location in the first row
    delayMs(500);
    GPIO_PORTF_DATA_R = 0x02;    //it turns on the red led. 
    delayMs(500);             
    GPIO_PORTF_DATA_R = 0x00;    //it turns off the red led. 
    delayMs(500);
    sendstring(err);
    delayMs(1000);
    clear();
}

unsigned char get_weight(){
	do{
		key=keypad_getkey();
		delayMs(200);   					//wait for the debounce
	}while(key==0);
	return key;
}
unsigned char SW1_input(void){																					/***********************/
	return GPIO_PORTF_DATA_R&0x10;
}
unsigned char SW2_input(void){																					/***********************/
	return GPIO_PORTF_DATA_R&0x01;
}
unsigned char SW3_input(void){																					/***********************/
	return GPIO_PORTA_DATA_R&0x08;
}
int set_timer(int time){
	int i, m, s, flag = 0;
	unsigned char mins, secs, minutes[2], seconds[2];
	for(i=time; i>=0; i--){
			sendCmd(1);
			sendstring(timer);
			m = i/60;
			s = i%60;
			if (m>9) sendchr((unsigned char)('0' + (m/10)));
			else sendchr('0');
			sendchr((unsigned char)('0' + (m%10)));
			sendchr(':');
			if (s>9) sendchr((unsigned char)('0' + (s/10)));
			else sendchr('0');
			sendchr((unsigned char)('0' + (s%10)));
			delayMs(1000);						//1s
			sw1=SW1_input();					//make it SW3 in the future
			if(sw1!=0x10){																				
					sendCmd(1);
					sendstring("Pausing");
					while(sw1!=0x01) sw1=SW1_input();
			}
	}
	//timer is done and is now 00:00
	sendCmd(1);
	return 0;
}
int main(){
	keypad_init();
	portInit(ctrlport);
	portInit(dataport);
	lcdInit();
	portInit('F');
	PORTA_Init();
	Idle:
	//sw3=SW3_input();
	sendstring("enter a leter");
	delayMs(2000);
	sendCmd(1);
	while (1){
		do{                          	//to be sure that the user really entered a key.
			sw1=SW1_input();																								/*******************use SW1 for clearing using keypad****************/
			sw2=SW2_input();																								/*******************use SW1 for clearing using keypad****************/
			if(sw1!=0x10||sw2!=0x01){																									/*******************use SW1 for clearing using keypad****************/
				sendCmd(1);
				sendstring(clearing);
				delayMs(1500);
				sendCmd(1);
				sendCmd(0x80);
			}
            key= keypad_getkey();
			delayMs(200);   					//wait for the debounce		
		}while(key==0);

			switch(key){
              case 'A':	{
									sendstring(popC);
                  delayMs(2000);			//wait 2 sec
									sendCmd(1);
									sendstring(timer);
									sendCmd(1);
									set_timer(60);
									break;
							}
              case 'B':{
								Beef:
                  sendCmd(1);
									sendstring(BeefW);
									sendCmd(0xC0);
									w=get_weight();				//first print the number and the clear the lcd
									sendchr(w);
									delayMs(2000);
									sendCmd(1);
									if(w<'1'||w>'9'){
											sendstring(err);
											delayMs(2000);
											goto Beef;
									}
									sendstring(timer);
									delayMs(1000);
									state= set_timer((w-'0')*30);
									if(state==0) goto Idle;			//******************************************redundant
									break;
							}
              case 'C':{
								Chicken:
                  sendCmd(1);
									sendstring(ChickW);
									sendCmd(0xC0);
									w=get_weight();				//first print the number and the clear the lcd
									sendchr(w);
									delayMs(2000);
									sendCmd(0xC0);
									if(w<'1'||w>'9'){
											sendstring(err);
											delayMs(2000);
											goto Chicken;
									}
									sendCmd(1);
									sendstring(timer);
									delayMs(1000);
									state= set_timer((w-'0')*12);
									sendchr(state);
									if(state==0) goto Idle;			//******************************************redundant
									break;
							}
              case 'D':{
                  int i;
        cookingTime:
                clear();
                writepin('a',2,0);
                sendstring("Cooking Time?");
                moveCursor(2, 1);
                delayMs(2000);			//wait 2 sec		
                for(i = 0; i < 4; i++){
                    tt[i] = '0';
                }
                //sendstring("00:00");
                do{                          	//to be sure that the user really entered a key.
                    value= keypad_getkey();
                    if(value == 'A' || value =='B' ||value =='C' ||value =='D' ||value =='*' ||value =='#' || value > '3'){
                        writepin('a',2,1);
                        delayMs(1000);
                        goto cookingTime;
                    }
                    sw1=SW1_input();																								/*******************use SW1 for clearing using keypad****************/
                    if(sw1!=0x10){																									/*******************use SW1 for clearing using keypad****************/
                        sendCmd(1);
                        goto cookingTime;
                    }
                    tt[3]= value;
                    delayMs(200);   					//wait for the debounce
                }while(tt[3]==0);
                clear();
                sendstring("timer: ");
                sendchr(tt[0]);sendchr(tt[1]);sendchr(':');sendchr(tt[2]);sendchr(tt[3]);
                tt[2] = tt[3]; 
                do{                          	//to be sure that the user really entered a key
                    value= keypad_getkey();
                    if(value == 'A' || value =='B' ||value =='C' ||value =='D' ||value =='*' ||value =='#'){
                        writepin('a',2,1);
                        delayMs(1000);
                        goto cookingTime;
                    }
                    sw1=SW1_input();																								/*******************use SW1 for clearing using keypad****************/
                    if(sw1!=0x10){																									/*******************use SW1 for clearing using keypad****************/
                        sendCmd(1);
                        goto cookingTime;
                    }
                    tt[3]= value;
                    delayMs(200);   					//wait for the debounce
                }while(tt[3]==0);
                clear();sendstring("timer: ");
				sendchr(tt[0]);sendchr(tt[1]);sendchr(':');sendchr(tt[2]);sendchr(tt[3]);
                tt[1] = tt[2];
                tt[2] = tt[3];
                do{                          	//to be sure that the user really entered a key.
                    value= keypad_getkey();
                    if(value == 'A' || value =='B' ||value =='C' ||value =='D' ||value =='*' ||value =='#'|| value >'5'){
                        writepin('a',2,1);
                        delayMs(1000);
                        goto cookingTime;
                    }
                    sw1=SW1_input();																								/*******************use SW1 for clearing using keypad****************/
                    if(sw1!=0x10){																									/*******************use SW1 for clearing using keypad****************/
                        sendCmd(1);
                        goto cookingTime;
                    }
                    tt[3]= value;
                    delayMs(200);   					//wait for the debounce
                }while(tt[3]==0);
                clear();sendstring("timer: ");
                sendchr(tt[0]);sendchr(tt[1]);sendchr(':');sendchr(tt[2]);sendchr(tt[3]);
                tt[0] = tt[1];
                tt[1] = tt[2];
                tt[2] = tt[3];
                do{                          	//to be sure that the user really entered a key.
                    value= keypad_getkey();
                    if(value == 'A' || value =='B' ||value =='C' ||value =='D' ||value =='*' ||value =='#'){
                        writepin('a',2,1);
                        delayMs(1000);
                        goto cookingTime;
                    }
                    sw1=SW1_input();																								/*******************use SW1 for clearing using keypad****************/
                    if(sw1!=0x10){																									/*******************use SW1 for clearing using keypad****************/
                        sendCmd(1);
                        goto cookingTime;
                    }
                    tt[3]= value;
                    delayMs(200);   					//wait for the debounce
                }while(tt[3]==0);
                clear();sendstring("timer: ");
				sendchr(tt[0]);sendchr(tt[1]);sendchr(':');sendchr(tt[2]);sendchr(tt[3]);
                if(tt[0]=='3'&&(tt[1]>'0'||tt[2]>'0'||tt[3]>'0')){
                    writepin('a',2,1);
                    delayMs(1000);
                    clear();
                    sendstring("Try again");
                    delayMs(2000);			//wait 2 sec
                    goto cookingTime; 
                }
								/******************push on switch 2 to start cooking****************************/
                m1=tt[0]-'0', m0=tt[1]-'0', s1=tt[2]-'0', s0=tt[3]-'0';
                temp=(m1*10+m0)*60+(s1*10 + s0);
                state= set_timer(temp);
                sendchr(state);
                if(state==0) goto Idle;			//******************************************redundant
                break;
            }
							default:
									error();
        }
	}
	return 0;
}