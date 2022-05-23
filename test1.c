
/*
unsigned char button1;
unsigned char button2;


void main()
{
	
	portInit('F');
	ledInit('F',1);
	ledInit('F',2);
	ledInit('F',3);
	buttonInit('F',0);
	buttonInit('f',4);
	

	button1 = buttonRead('f',0);

	button2 = buttonRead('f',4);
	
	while (1)
	{
		if( button1 == 0) ledON('F',1);
		else if( button2 == 0) ledON('F',2);
		else ledON('F',3);
	}
}


unsigned char sw1_input(void){
	
	return GPIO_PORTF_DATA_R&0x10;
}
unsigned char sw2_input(void){
	
	return GPIO_PORTF_DATA_R&0x01;	 
}
void RGB_Output (unsigned char data){
	
	GPIO_PORTF_DATA_R &=~0x0E;	
	GPIO_PORTF_DATA_R |= data;
}
unsigned char RedLed = 0x02;
unsigned char BlueLed = 0x04;  
unsigned char GreenLed = 0x08;
unsigned char button_in1; 
unsigned char button_in2;
void main() 
{
	SYSCTL_RCGCGPIO_R|=0x20; //INTIALIZE THE CLOCK OF PORTF
	while((SYSCTL_PRGPIO_R & 0x20)==0); //delay 
	GPIO_PORTF_LOCK_R = 0x4C4F434B;	//Constant value
	GPIO_PORTF_AMSEL_R =0x00;	//disable analog function
	GPIO_PORTF_CR_R |= 0xFF; //setting pin p0 to change
	GPIO_PORTF_PCTL_R =0x00; //enable digital function
	GPIO_PORTF_AFSEL_R =0x00; //disable alterante function
	GPIO_PORTF_DIR_R = 0x0E; 	//DIR--> 0->input & 1->output
	GPIO_PORTF_PUR_R =0x11;	//active low
	GPIO_PORTF_DEN_R =0xFF;	//Enable digital for sw2
	while(1){
		
		button_in1 = sw1_input(); //pf4
		button_in2 = sw2_input(); //pf0
		if(button_in1 == 0x00) RGB_Output(RedLed);
		else RGB_Output(BlueLed);
	}
}
*/