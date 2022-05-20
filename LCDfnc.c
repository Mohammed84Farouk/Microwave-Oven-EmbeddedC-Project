#include "lcdDef.h"
#include "Io.h"

void sendCmd(unsigned char cmd);

void lcdInit ()
{
	setportDIR(dataport,0xFF);
	setpinDIR(ctrlport , E , 1);
	setpinDIR(ctrlport , RS , 1);
	setpinDIR(ctrlport , RW , 1);
	writepin(ctrlport, RW , 0);
	sendCmd(0x38); // work in 8 bit mode
	delay_ms(1);
	sendCmd(displayON_cursorBlink);
	delay_ms(1);
	sendCmd(clr);
	delay_ms(10);
	sendCmd(entryMode);
}
static void pulse (void)
{
	writepin(ctrlport , E , 1);
	delay_ms(2);
	writepin(ctrlport , E , 0);
	delay_ms(2);
}
void sendCmd(unsigned char cmd)
{
	writeport(dataport , cmd);
	writepin(dataport , RS , 0);
	pulse();
	delay_ms(1);
}
void sendchr(unsigned char chr)
{
	writeport(dataport , chr);
	writepin(dataport , RS , 1);
	pulse();
	delay_ms(1);
}
void sendstring( char* data)
{
	while((*data) != '\0'){
		sendchr(*data);
		data++;
	}
}
void clear()
{
	sendCmd(clr);
	delay_ms(10);
}
void moveCursor(unsigned char row , unsigned char col)
{
	char pos = 0;
	if(row == 1) pos = 0x80 + col - 1 ;
	else if (row == 2) pos = 0xC0 + col - 1;
	else pos = 0x80;
	sendCmd(pos);
	delay_ms(1);
}