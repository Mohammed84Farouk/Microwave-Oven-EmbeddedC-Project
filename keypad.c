// The keypad is initializied by adding the rows to ports E0>>E3 in tiva C and the columns to ports C4>>C7
// The Columns will be set to be digital Input while the Rows will be set to be digital Output

#include "TM4C123GH6PM.h"
#include <stdint.h>

#define KEYPAD_ROW GPIOE
#define KEYPAD_COL GPIOC

void enablePClock(int x){																									//enables clock to Port x/*************************/
	SYSCTL->RCGCGPIO|=x;
}
void setDirection(int x , unsigned char PortName){
	switch(PortName){
		case 'R':
		case 'r':
			KEYPAD_ROW->DIR |= x;
			break;
		case 'C':
		case 'c':
			KEYPAD_COL->DIR &= ~x;
		break;
			
	}
}
void setDigital(int x , unsigned char PortName){
	switch(PortName){
		case 'R':
		case 'r':
			KEYPAD_ROW->DEN |= x;
			break;
		case 'C':
		case 'c':
			KEYPAD_COL->DEN |= x;
		break;
			
	}
}
void setPullUp(int x , unsigned char PortName)
{
	switch(PortName){
		case 'R':
		case 'r':
			KEYPAD_ROW->PUR |= x;
			break;
		case 'C':
		case 'c':
			KEYPAD_COL->PUR |= x;
		break;
			
	}
}
void setOpenDrain(int x , unsigned char PortName)
{
	switch(PortName){
		case 'R':
		case 'r':
			KEYPAD_ROW->ODR |= x;
			break;
		case 'C':
		case 'c':
			KEYPAD_COL->ODR |= x;
		break;
			
	}
}


/* this function initializes the ports connected to the keypad */
// The R used in the Functions refer to Rows and the C refer to Columns
void keypad_init(void) {
			enablePClock(0x04);																						//enable clock to GPIOC
			enablePClock(0x10);																						//enable clock to GPIOE							el mafroud d bta3t modather
			setDirection(0x0F , 'R');																			// set row pins 3-0 as output 
			setDigital(0x0F ,'R'); 																			// set row pins 3-0 as digital pins 
			setOpenDrain(0x0F ,'R');																		// set row pins 3-0 as open drain 									
			setDirection(0x0F , 'C');																		// set column pin 7-4 as input 
			setDigital(0x0F ,'C');																			// set column pin 7-4 as digital
			setPullUp(0xF0 , 'C');																			//set column pin 7-4 as PullUp
}
/* This is a non-blocking function to read the keypad. */
/* If a key is pressed, it returns the key label in ASCII encoding. Otherwise, it
returns a 0 (not ASCII 0). */
unsigned char keypad_getkey(void)
{
	const unsigned char keymap[4][4] = {
	{ '1', '2', '3', 'A'},
	{ '4', '5', '6', 'B'},
	{ '7', '8', '9', 'C'},
	{ '*', '0', '#', 'D'}};
	int row, col;
/* check to see any key pressed first */
	KEYPAD_ROW->DATA = 0; /* enable all rows */
	col = KEYPAD_COL->DATA & 0xF0; /* read all columns */
	if (col == 0xF0) return 0; /* no key pressed */
/* If a key is pressed, it gets here to find out which key. */
/* Although it is written as an infinite loop, it will take one of the breaks or
return in one pass.*/
	while (1){
		row = 0;
		KEYPAD_ROW->DATA = 0x0E; 																		/* enable row 0 at E0 */
		delayUs(2); 																								/* wait for signal to settle */
		col = KEYPAD_COL->DATA & 0xF0;
		if (col != 0xF0) break;
		row = 1;
		KEYPAD_ROW->DATA = 0x0D; 																		/* enable row 1 at E1 */
		delayUs(2); 																								/* wait for signal to settle */
		col = KEYPAD_COL->DATA & 0xF0;
		if (col != 0xF0) break;
		row = 2;
		KEYPAD_ROW->DATA = 0x0B; 																		/* enable row 2 at E2 */
		delayUs(2); 																								/* wait for signal to settle */
		col = KEYPAD_COL->DATA & 0xF0;
		if (col != 0xF0) break;
		row = 3;
		KEYPAD_ROW->DATA = 0x07; 																		/* enable row 3 at at E3 */
		delayUs(2); 																								/* wait for signal to settle */
		col = KEYPAD_COL->DATA & 0xF0;
		if (col != 0xF0) break;
		return 0; 																									/* if no key is pressed */
	}
	/* gets here when one of the rows has key pressed */
	if (col == 0xE0) return keymap[row][3]; 										/* key in column 3 */
	if (col == 0xD0) return keymap[row][2]; 										/* key in column 2 */
	if (col == 0xB0) return keymap[row][1]; 										/* key in column 1 */
	if (col == 0x70) return keymap[row][0]; 										/* key in column 0 */
	return 0; 																									/* just to be safe */
}