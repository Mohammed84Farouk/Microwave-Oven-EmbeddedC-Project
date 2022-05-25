#include "tm4c123gh6pm.h"
#include "es.h"


void portInit ( unsigned char port )
{
	switch(port)
 	{
		case 'A' :
	  case 'a' : 
			setbit(SYSCTL_RCGCGPIO_R , 0); // unlock clock 
		  while(readbit(SYSCTL_PRGPIO_R , 0) == 0); //delay
		  GPIO_PORTA_LOCK_R = 0x4C4F434B; //unlock 
		  GPIO_PORTA_DEN_R = 0xFF; //digital enable
		  GPIO_PORTA_AMSEL_R = 0x00; // analog disable
		  GPIO_PORTA_AFSEL_R = 0x00; // alt functions disable
		  GPIO_PORTA_CR_R = 0xFF; // commit control
			GPIO_PORTA_PCTL_R = 0x00; // gpio
		break;
		case 'B' :
	  case 'b' : 
			setbit(SYSCTL_RCGCGPIO_R , 1); // unlock clock 
		  while(readbit(SYSCTL_PRGPIO_R , 1) == 0); //delay
		  GPIO_PORTB_LOCK_R = 0x4C4F434B; //unlock 
		  GPIO_PORTB_DEN_R = 0xFF; //digital enable
		  GPIO_PORTB_AMSEL_R = 0x00; // analog disable
		  GPIO_PORTB_AFSEL_R = 0x00; // alt functions disable
		  GPIO_PORTB_CR_R = 0xFF; // commit control
			GPIO_PORTB_PCTL_R = 0x00; // gpio
		break;
		case 'C' :
	  case 'c' : 
			setbit(SYSCTL_RCGCGPIO_R , 2); // unlock clock 
		  while(readbit(SYSCTL_PRGPIO_R , 2) == 0); //delay
		  GPIO_PORTC_LOCK_R = 0x4C4F434B; //unlock 
		  GPIO_PORTC_DEN_R |= 0xF0 ;
			GPIO_PORTC_AFSEL_R &= ~(0xF0);
			GPIO_PORTC_CR_R |= 0xF0;
			GPIO_PORTC_PCTL_R &= 0x0F;
			/* GPIO_PORTC_DEN_R = 0xFF; //digital enable
		  GPIO_PORTC_AMSEL_R = 0x00; // analog disable
		  GPIO_PORTC_AFSEL_R = 0x00; // alt functions disable
		  GPIO_PORTC_CR_R = 0xFF; // commit control
			GPIO_PORTC_PCTL_R = 0x00; // gpio */
		break;
		case 'D' :
	  case 'd' : 
			setbit(SYSCTL_RCGCGPIO_R , 3); // unlock clock 
		  while(readbit(SYSCTL_PRGPIO_R , 3) == 0); //delay
		  GPIO_PORTD_LOCK_R = 0x4C4F434B; //unlock 
		  GPIO_PORTD_DEN_R = 0xFF; //digital enable
		  GPIO_PORTD_AMSEL_R = 0x00; // analog disable
		  GPIO_PORTD_AFSEL_R = 0x00; // alt functions disable
		  GPIO_PORTD_CR_R = 0xFF; // commit control
			GPIO_PORTD_PCTL_R = 0x00; // gpio
		break;
		case 'E' :
	  case 'e' : 
			setbit(SYSCTL_RCGCGPIO_R , 4); // unlock clock 
		  while(readbit(SYSCTL_PRGPIO_R , 4) == 0); //delay
		  GPIO_PORTE_LOCK_R = 0x4C4F434B; //unlock 
		  GPIO_PORTE_DEN_R = 0xFF; //digital enable
		  GPIO_PORTE_AMSEL_R = 0x00; // analog disable
		  GPIO_PORTE_AFSEL_R = 0x00; // alt functions disable
		  GPIO_PORTE_CR_R = 0xFF; // commit control
			GPIO_PORTE_PCTL_R = 0x00; // gpio
		break;
		case 'F' :
	  case 'f' : 
			setbit(SYSCTL_RCGCGPIO_R , 5); // unlock clock 
		  while(readbit(SYSCTL_PRGPIO_R , 5) == 0); //delay
		  GPIO_PORTF_LOCK_R = 0x4C4F434B; //unlock
		  GPIO_PORTF_CR_R = 0xFF; // commit control
		  GPIO_PORTF_DEN_R = 0xFF; //digital enable
		  GPIO_PORTF_AMSEL_R = 0x00; // analog disable
		  GPIO_PORTF_AFSEL_R = 0x00; // alt functions disable
			GPIO_PORTF_PCTL_R = 0x00; // gpio
			GPIO_PORTF_PUR_R |=0x11; 
			GPIO_PORTF_DIR_R |=0x0E; 
		break;
	}
}

void setpinDIR ( unsigned char port , unsigned char pin , unsigned char dir)
{
	switch(port)
	{
		case 'A' :
	  case 'a' :
			if(dir == 1) setbit(GPIO_PORTA_DIR_R , pin);
		  else if (dir == 0) clearbit(GPIO_PORTA_DIR_R , pin);
		break;
		case 'B' :
	  case 'b' :
			if(dir == 1) setbit(GPIO_PORTB_DIR_R , pin);
		  else if (dir == 0) clearbit(GPIO_PORTB_DIR_R , pin);
		break;
		case 'C' :
	  case 'c' :
			if(dir == 1) setbit(GPIO_PORTC_DIR_R , pin);
		  else if (dir == 0) clearbit(GPIO_PORTC_DIR_R , pin);
		break;
		case 'D' :
	  case 'd' :
			if(dir == 1) setbit(GPIO_PORTD_DIR_R , pin);
		  else if (dir == 0) clearbit(GPIO_PORTD_DIR_R , pin);
		break;
		case 'E' :
	  case 'e' :
			if(dir == 1) setbit(GPIO_PORTE_DIR_R , pin);
		  else if (dir == 0) clearbit(GPIO_PORTE_DIR_R , pin);
		break;
		case 'F' :
	  case 'f' :
			if(dir == 1) setbit(GPIO_PORTF_DIR_R , pin);
		  else if (dir == 0) clearbit(GPIO_PORTF_DIR_R , pin);
		break;
	}
}
void setportDIR (unsigned char port , unsigned char dir)
{
	switch(port)
	{
		case 'A' :
	  case 'a' :
			GPIO_PORTA_DIR_R = dir;
		break;
		case 'B' :
	  case 'b' :
			GPIO_PORTB_DIR_R = dir;
		break;
		case 'C' :
		case 'c' :
			GPIO_PORTC_DIR_R = dir;
		break;
		case 'D' :
	  case 'd' :
			GPIO_PORTD_DIR_R = dir;
		break;
		case 'E' :
	  case 'e' :
			GPIO_PORTE_DIR_R = dir;
		break;
		case 'F' :
	  case 'f' :
			GPIO_PORTF_DIR_R = dir;
		break;
	}
}		
void writepin ( unsigned char port , unsigned char pin , unsigned char data)
{
	switch(port)
	{
		case 'A' :
	  case 'a' :
			if(data == 1) setbit(GPIO_PORTA_DATA_R , pin);
		  else if (data == 0) clearbit(GPIO_PORTA_DATA_R , pin);
		break;
		case 'B' :
	  case 'b' :
			if(data == 1) setbit(GPIO_PORTB_DATA_R , pin);
		  else if (data == 0) clearbit(GPIO_PORTB_DATA_R , pin);
		break;
		case 'C' :
	  case 'c' :
			if(data == 1) setbit(GPIO_PORTC_DATA_R, pin);
		  else if (data == 0) clearbit(GPIO_PORTC_DATA_R , pin);
		break;
		case 'D' :
	  case 'd' :
			if(data == 1) setbit(GPIO_PORTD_DATA_R , pin);
		  else if (data == 0) clearbit(GPIO_PORTD_DATA_R , pin);
		break;
		case 'E' :
	  case 'e' :
			if(data == 1) setbit(GPIO_PORTE_DATA_R , pin);
		  else if (data == 0) clearbit(GPIO_PORTE_DATA_R , pin);
		break;
		case 'F' :
	  case 'f' :
			if(data == 1) setbit(GPIO_PORTF_DATA_R , pin);
		  else if (data == 0) clearbit(GPIO_PORTF_DATA_R , pin);
		break;
	}
}
void writeport ( unsigned char port , unsigned char data)
{
	switch(port)
	{
		case 'A' :
	  case 'a' :
			GPIO_PORTA_DATA_R = data;
		break;
		case 'B' :
	  case 'b' :
			GPIO_PORTB_DATA_R = data;
		break;
		case 'C' :
		case 'c' :
			GPIO_PORTC_DATA_R = data;
		break;
		case 'D' :
	  case 'd' :
			GPIO_PORTD_DATA_R = data;
		break;
		case 'E' :
	  case 'e' :
			GPIO_PORTE_DATA_R = data;
		break;
		case 'F' :
	  case 'f' :
			GPIO_PORTF_DATA_R = data;
		break;
	}
}
unsigned char readpin (unsigned char port , unsigned char pin)
{
	switch(port)
	{
		case 'A' :
	  case 'a' :
			return readbit(GPIO_PORTA_DATA_R , pin) ;
		break;
		case 'B' :
	  case 'b' :
			return readbit(GPIO_PORTB_DATA_R , pin) ;
		break;
		case 'C' :
	  case 'c' :
			return readbit(GPIO_PORTC_DATA_R , pin) ;
		break;
		case 'D' :
	  case 'd' :
			return readbit(GPIO_PORTD_DATA_R , pin) ;
		break;
		case 'E' :
	  case 'e' :
			return readbit(GPIO_PORTE_DATA_R , pin) ;
		break;
		case 'F' :
	  case 'f' :
			return readbit(GPIO_PORTF_DATA_R , pin) ;
		break;
	}
}

unsigned char readport (unsigned char port)
{
	switch(port)
	{
		case 'A' :
	  case 'a' :
			return GPIO_PORTA_DATA_R;
		break;
		case 'B' :
	  case 'b' :
			return GPIO_PORTB_DATA_R;
		break;
		case 'C' :
	  case 'c' :
			return GPIO_PORTC_DATA_R;
		break;
		case 'D' :
	  case 'd' :
			return GPIO_PORTD_DATA_R;
		break;
		case 'E' :
	  case 'e' :
			return GPIO_PORTE_DATA_R;
		break;
		case 'F' :
	  case 'f' :
			return GPIO_PORTF_DATA_R;
		break;
	}
}
void pullup_enable (unsigned char port , unsigned char pin)
{
	switch (port)
	{
		case 'A' :
		case 'a' :
			setbit(GPIO_PORTA_PUR_R , pin);
		break;
		case 'B' :
		case 'b' :
			setbit(GPIO_PORTB_PUR_R , pin);
		break;
		case 'C' :
		case 'c' :
			setbit(GPIO_PORTC_PUR_R , pin);
		break;
		case 'D' :
		case 'd' :
			setbit(GPIO_PORTD_PUR_R , pin);
		break;
		case 'E' :
		case 'e' :
			setbit(GPIO_PORTE_PUR_R , pin);
		break;
		case 'F' :
		case 'f' :
			setbit(GPIO_PORTF_PUR_R , pin);
		break;
	}
}
void write_low (unsigned char port , unsigned char data)
{
	switch(port)
	{
		case 'A' :
	  case 'a' :
			GPIO_PORTA_DATA_R &= 0xF0;
			GPIO_PORTA_DATA_R |= data;
		break;
		case 'B' :
	  case 'b' :
			GPIO_PORTB_DATA_R &= 0xF0;
			GPIO_PORTB_DATA_R |= data;
		break;
		case 'C' :
	  case 'c' :
			GPIO_PORTC_DATA_R &= 0xF0;
			GPIO_PORTC_DATA_R |= data;
		break;
		case 'D' :
	  case 'd' :
			GPIO_PORTD_DATA_R &= 0xF0;
			GPIO_PORTD_DATA_R |= data;
		break;
		case 'E' :
	  case 'e' :
			GPIO_PORTE_DATA_R &= 0xF0;
			GPIO_PORTE_DATA_R |= data;
		break;
		case 'F' :
	  case 'f' :
			GPIO_PORTF_DATA_R &= 0xF0;
			GPIO_PORTF_DATA_R |= data;
		break;
	}
}
void write_high (unsigned char port , unsigned char data)
{
	switch(port)
	{
		case 'A' :
	  case 'a' :
			GPIO_PORTA_DATA_R &= 0x0F;
			GPIO_PORTA_DATA_R |= data;
		break;
		case 'B' :
	  case 'b' :
			GPIO_PORTB_DATA_R &= 0x0F;
			GPIO_PORTB_DATA_R |= data;
		break;
		case 'C' :
	  case 'c' :
			GPIO_PORTC_DATA_R &= 0x0F;
			GPIO_PORTC_DATA_R |= data;
		break;
		case 'D' :
	  case 'd' :
			GPIO_PORTD_DATA_R &= 0x0F;
			GPIO_PORTD_DATA_R |= data;
		break;
		case 'E' :
	  case 'e' :
			GPIO_PORTE_DATA_R &= 0x0F;
			GPIO_PORTE_DATA_R |= data;
		break;
		case 'F' :
	  case 'f' :
			GPIO_PORTF_DATA_R &= 0x0F;
			GPIO_PORTF_DATA_R |= data;
		break;
	}
}
void ledInit ( unsigned char port , unsigned char pin)
{
	setpinDIR(port , pin , 1);
}
void ledON (unsigned char port , unsigned char pin)
{
	writepin(port , pin , 1);
}
void ledOFF (unsigned char port , unsigned char pin)
{
	writepin(port , pin , 0);
}
void buttonInit (unsigned char port , unsigned char pin)
{
	setpinDIR(port , pin, 0);
	pullup_enable(port,pin);
}
unsigned char buttonRead (unsigned char port , unsigned char pin)
{
	return readpin(port , pin);
}
void systickInit(void)
{
	NVIC_ST_CTRL_R = 0x00;
	NVIC_ST_RELOAD_R = 0x00FFFFFF;
	NVIC_ST_CURRENT_R = 0x00;
	NVIC_ST_CTRL_R = 0x05;
}
void delay_ms( unsigned int n)
{
	unsigned int i ;
	systickInit();
	NVIC_ST_RELOAD_R = 16000 - 1;
	NVIC_ST_CURRENT_R = 0x00;
	for(i=0 ; i < n ; i++)
	while ( readbit(NVIC_ST_CTRL_R ,16) == 0);
}
void delay_us( unsigned int n)
{
	unsigned int i ;
	systickInit();
	NVIC_ST_RELOAD_R = 16 - 1;
	NVIC_ST_CURRENT_R = 0x00;
	for(i=0 ; i < n ; i++)
	while ( readbit(NVIC_ST_CTRL_R ,16) == 0);
}
