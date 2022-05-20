#include "TM4C123GH6PM.h"
#include <stdint.h>
#include "prototypes.h"
#include "math.h"
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))	/***********************************/

void SW_Init(void){																												/***********************/
	SYSCTL->RCGCGPIO |=0x20;
	while((SYSCTL->RCGCGPIO & 0x20)==0); //delay
	GPIOF->LOCK = 0x4C4F434B;
	GPIOF->AMSEL &=~0x11;
	GPIO_PORTF_CR_R |= 0x11; //setting pin p4 & p0 to change
	GPIOF->PCTL &=~0x000F000F; //enable digital function
	GPIOF->AFSEL &=~0x11; //disable alterante function
	GPIOF->DIR &=~0x11; //DIR--> 0->input & 1->output
	GPIOF->PUR |=0x11; //active low
	GPIOF->DEN |= 0x11; //Enable digital for sw1 and sw2
}
unsigned char SW1_input(void){																					/***********************/
return (GPIOF->DATA)&0x10;
}
unsigned char sw;																												/**********************/
uint8_t key;      //to recieve the returned character

int main(void){

/* enable clock to GPIOF at clock gating control register */																		//use modather's function
				SYSCTL->RCGCGPIO |= 0x20;
/* enable the GPIO pins for the LED (PF3, 2 1) as output */
				GPIOF->DIR = 0x0E;
/* enable the GPIO pins for digital function */
				GPIOF->DEN = 0x0E;
	
	      SW_Init();																												/***************use SW1 for clearing using keypad*****************/
				LCD_init();
        keypad_init();
      
	Idle:		LCD_command(1);    				//clear the lcd.
					LCD_command(0x80); 				/* lcd cursor location */
					lcd_data('O');lcd_data('F');lcd_data('F');lcd_data('O');lcd_data('F');lcd_data('F');
					delayMs(3000);
					LCD_command(1);    				//clear the lcd.
  while(1){
			do{                          	//to be sure that the user really entered a key.
				
					sw=SW1_input();																								/*******************use SW1 for clearing using keypad****************/
					if(sw!=0x10){																									/*******************use SW1 for clearing using keypad****************/
							LCD_command(1);
							lcd_data('C');lcd_data('l');lcd_data('e');lcd_data('a');lcd_data('r');lcd_data('i');lcd_data('n');lcd_data('g');lcd_data('.');lcd_data('.');lcd_data('.');
							delayMs(1500);
							LCD_command(1);
							LCD_command(0x80);
					}
					key= keypad_getkey();
					delayMs(200);   					//wait for the debounce
					
			}while(key==0);
			
			switch(key){
              case 'A':	{
                  lcd_data('P');lcd_data('o');lcd_data('p');lcd_data('C');lcd_data('o');lcd_data('r');lcd_data('n');
                  delayMs(2000);			//wait 2 sec
									LCD_command(1);
									lcd_data('T');lcd_data('i');lcd_data('m');lcd_data('e');lcd_data('r');lcd_data(':');lcd_data(' ');
									delayMs(1000);
									LCD_command(1);
									break;
							}
              case 'B':
                  lcd_data(key);
                  break;
              case 'C':
                  lcd_data(key);
                  break;
              case 'D':
                  lcd_data(key);
									break;
							default:
									error();
        }
  }
}
//this function is used to show an error message on the lcd and turns the red led on and then off.
void error(void)
{

	     LCD_command(1);     //clear the screen
	     LCD_command(0x80); /* lcd cursor location:first location in the first row */
             delayMs(500);
	     GPIOF->DATA = 0x02;    //it turns on the red led. 
             delayMs(500);             
             GPIOF->DATA = 0x00;    //it turns off the red led. 
             delayMs(500);
             lcd_data('e');
             lcd_data('r');
             lcd_data('r');
             lcd_data('o');
             lcd_data('r');
             delayMs(1000);
             LCD_command(1);
        
}

/* delay n milliseconds (16 MHz CPU clock) */
void delayMs(uint32_t n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3180; j++)
{} /* do nothing for 1 ms */
}
/* delay n microseconds (16 MHz CPU clock) */
void delayUs(uint32_t n)
{
int i, j;
for(i = 0 ; i < n; i++)
for(j = 0; j < 3; j++)
{} /* do nothing for 1 us */
}
/* This function is called by the startup assembly code to perform system specific
initialization tasks. */
void SystemInit(void)
{
/* Grant coprocessor access */
/* This is required since TM4C123G has a floating point coprocessor */
SCB->CPACR |= 0x00F00000;
}
