#include "tm4c123gh6pm.h"
#include "stdint.h"

void PORTA_Init(){                                            //Switch3 at PA3, and buzzer at PA2

  SYSCTL_RCGCGPIO_R |= 0x01;                     // PortA clock enable
  while ((SYSCTL_PRGPIO_R & 0x01)==0);// Delay
  GPIO_PORTA_LOCK_R = 0x4C4F434B;     // unlock GPIO of PORTA
  GPIO_PORTA_CR_R = 0x0C;             // Enable to commit
  GPIO_PORTA_PUR_R |= 0x08;                   // Enable Pull Up SW on PA3
  GPIO_PORTA_DEN_R |= 0x0C;              // Enable pin 2 and 3 of PORTA
  GPIO_PORTA_DIR_R |= 0x04;              // Make pin 2 of PORTA as ouptut pin for buzzer
  GPIO_PORTA_PCTL_R &= ~0x0000FF00;     // Regular GPIO of PORTA
  GPIO_PORTA_AMSEL_R &= ~0x0C;        // Disable analog function on pin 2 and 3 of PORTA
  GPIO_PORTA_AFSEL_R &= ~0x0C;        // Regular port function
}