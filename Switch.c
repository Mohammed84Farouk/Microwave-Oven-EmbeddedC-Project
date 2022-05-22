#include "tm4c123gh6pm.h"

#define GPIO_PORTA_DATA_R       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_R        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_R      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_R        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_DEN_R        (*((volatile unsigned long *)0x4000451C))
//#define GPIO_PORTA_LOCK_R       (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_CR_R         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_R      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_R       (*((volatile unsigned long *)0x4000452C))
#define GPIO_LOCK_KEY           0x4C4F434B  // Unlocks the GPIO_CR register    ask Farouk
#define SYSCTL_RCGCGPIO_R       (*((volatile unsigned long *)0x400FE608))
#define SYSCTL_PRGPIO_R         (*((volatile unsigned long *)0x400FEA08))
#define PA0                     (*((volatile unsigned long *)0x40004004))
#define PA0 					0x01

void init_portA(){
	SYSCTL_RCGCGPIO_R |= 0x01; // PortA clock enable
	while ((SYSCTL_PRGPIO_R & 0x01)==0); //Delay
	GPIO_PORTA_LOCK_R = 0x4C4F434B; // Unlock PortA Commit register
	GPIO_PORTA_CR_R = 0x01;//enable control 
	GPIO_PORTA_PUR_R |= 0x01;   	//Enable Pull Up SW on PA0
	GPIO_PORTA_AFSEL_R &= ~0x01; // No alternate function
	GPIO_PORTA_PCTL_R &= ~0x01 ; 	// Regular GPIO of PORTA
	GPIO_PORTA_AMSEL_R &= ~0x01; // Disable analog function
	GPIO_PORTA_DIR_R |= 0x00; // PA0 input
 	GPIO_PORTA_DEN_R |= 0x01; // Enable Port A0  
}