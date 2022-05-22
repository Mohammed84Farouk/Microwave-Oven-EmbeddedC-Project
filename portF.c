#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define PF4                     (*((volatile unsigned long *)0x40025040))
#define PF3                     (*((volatile unsigned long *)0x40025020))
#define PF2                     (*((volatile unsigned long *)0x40025010))
#define PF1                     (*((volatile unsigned long *)0x40025008))
#define PF0                     (*((volatile unsigned long *)0x40025004))
#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_PRGPIO_R         (*((volatile unsigned long *)0x400FEA08))
#define RED      				0x02
#define BLUE      				0x04
#define GREEN     				0x08
#define PF123_mask              0x0E
#define PF04_mask               0x11
#define PF_mask                 0x20
#include "stdint.h"
#include "tm4c123gh6pm.h"
char SW1, SW2;
void init_PortF(void){

	SYSCTL_RCGCGPIO_R |= 0x20; // PortF clock enable
	while ((SYSCTL_PRGPIO_R & 0x20)==0); //Delay
	GPIO_PORTF_LOCK_R = 0x4C4F434B; // Unlock PortF Commit register
	GPIO_PORTF_CR_R |= 0x02; // Allow changes to PF1
	GPIO_PORTF_AMSEL_R &= ~0x02; // Disable analog function
	GPIO_PORTF_PCTL_R &= ~0x000000F0; // GPIO clear bit PCTL
	GPIO_PORTF_AFSEL_R &= ~0x02; // No alternate function
	GPIO_PORTF_DIR_R |= 0x02; // PF321 output
	GPIO_PORTF_DEN_R |= 0x02; // Enable digital pins PF4-PF0
}	

int main(){
	init_PortF();
	if((GPIO_PORTF_DATA_R&0x11)==0x01){
		SW1 = 1;
	}
	else if((GPIO_PORTF_DATA_R&0x11)==0x10){
		SW2 = 1;
	}
}
