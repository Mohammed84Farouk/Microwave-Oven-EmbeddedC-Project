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
unsigned char reading(){
    unsigned char r=0;
    do{                          	//to be sure that the user really entered a key.
        r= keypad_getkey();
        delayMs(200);   					//wait for the debounce		
	}while(r==0);
    return r;
}
unsigned char get_weight(){
	return reading();
}
int TimeUp(){
    int i, j;
    clear(); 
	setportDIR('f' , 0x0E);
	sendstring("Done");
	for(i=0;i<3;i++){
		sendchr('.');
		for(j=1; j<=3; j++)	writepin('f',j,1);
		writepin('a',2,1);
		delayMs(500);
		for(j=1; j<=3; j++) writepin('f',j,0);
		writepin('a',2,0);
		delayMs(500);
	}
	delayMs(500);
	return 1;
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
int Pause(){                           //returns 1 to resume, 0 to reset;
    clear();                            //remove that line
    sendstring("Pausing");              //remove that line
    sw2=0x01, sw1= 0x10;
	while(sw2==0x01&&sw1==0x10){
        sw2=SW2_input();
        sw1=SW1_input();
    }
    if(sw2!=0x01) return 1;             //resume 
    return 0;                           //reset
    
}
uint32_t ii, jj;
int set_timer(int time){
	int i, m, s, flag = -1;
	unsigned char mins, secs, minutes[2], seconds[2];
	for(i=time; i>=0; i--){
		clear();
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
		delayMs(100);							//0.1s
		for(ii = 0 ; ii < 300; ii++){           //0.9s the rest of the second for counting down
			sw1=SW1_input();					//make it SW3 in the future
			if(sw1!=0x10){
				flag = Pause();
                if(!flag){
                    clear();
                    return 0;
                }
			}
			for(jj = 0; jj < 3180; jj++){}			//1ms
		}
	}
	//timer is done and is now 00:00
	clear();
	return 1;
}
int PopCorn(){
    sendstring(popC);
    delayMs(2000);			//wait 2 sec
	clear();
	sendstring(timer);
	clear();
    state= set_timer(60);
    if(state==0) return 0;			//to go to Idle
    return TimeUp();
}
int Animal(char c){
    if(c=='C'){
        Chicken:
            clear();
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
            clear();
            sendstring(timer);
            delayMs(1000);
            state= set_timer((w-'0')*12);
            if(state==0) return 0;			//to go to Idle
            return TimeUp();
    }
    else{
        Beef:
            clear();
			sendstring(BeefW);
            sendCmd(0xC0);
            w=get_weight();				//first print the number and the clear the lcd
            sendchr(w);
            delayMs(2000);
            clear();
            if(w<'1'||w>'9'){
                sendstring(err);
                delayMs(2000);
                goto Beef;
            }
            sendstring(timer);
            delayMs(1000);
            state= set_timer((w-'0')*30);
            if(state==0) return 0;			//to go to Idle
            return TimeUp();
    }
}
int idx;
int SpecialTiming(){
    cookingTime:
        clear();
        writepin('a',2,0);                  //buzzer is turned off
        for(idx = 0; idx < 4; idx++) tt[idx] = (idx>1? 'm':'s');
        sendstring("Cooking Time?");
        moveCursor(2, 1);
        sendstring("mm:ss");
        delayMs(2000);			//wait 2 se$
        do{                          	//to be sure that the user really entered a key.
            value= keypad_getkey();
            if((value >= 'A' && value <= 'D') ||value =='*' ||value =='#' || value > '3'){
                writepin('a',2,1);
                delayMs(1000);
                goto cookingTime;
            }
            sw1=SW1_input();																								/*******************use SW1 for clearing using keypad****************/
            if(sw1!=0x10){																									/*******************use SW1 for clearing using keypad****************/
                clear();
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
            if((value >= 'A' && value <= 'D') ||value =='*' ||value =='#'){
                writepin('a',2,1);
                delayMs(1000);
                goto cookingTime;
            }
            sw1=SW1_input();																								/*******************use SW1 for clearing using keypad****************/
            if(sw1!=0x10){																									/*******************use SW1 for clearing using keypad****************/
                clear();
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
            if((value >= 'A' && value <= 'D') ||value =='*' ||value =='#'|| value >'5'){
                writepin('a',2,1);
                delayMs(1000);
                goto cookingTime;
            }
            sw1=SW1_input();																								/*******************use SW1 for clearing using keypad****************/
            if(sw1!=0x10){																									/*******************use SW1 for clearing using keypad****************/
                clear();
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
            if((value >= 'A' && value <= 'D') ||value =='*' ||value =='#'){
                writepin('a',2,1);
                delayMs(1000);
                goto cookingTime;
            }
            sw1=SW1_input();																								/*******************use SW1 for clearing using keypad****************/
            if(sw1!=0x10){																									/*******************use SW1 for clearing using keypad****************/
                clear();
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
        if(state==0) return 0;			//to go to Idle
        return TimeUp();
}

int main(){
	keypad_init();
	portInit(ctrlport);
	portInit(dataport);
	lcdInit();
	portInit('F');
	PORTA_Init();
	while (1){
    Idle:
        sendstring(idle);
		key=reading();
        switch(key){
            case 'A':
				PopCorn();
                break;
            case 'B':
                Animal('B');
                break;
            case 'C':
                Animal('C');
                break;
            case 'D':                 //7asbya allah wane3m al wakil.
                SpecialTiming();
                break;
            default:
                error();
        }
	}
	return 0;
}