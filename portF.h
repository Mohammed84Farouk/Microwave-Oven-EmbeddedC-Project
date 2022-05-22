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
