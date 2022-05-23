void lcdInit ();
static void pulse (void);
void sendCmd(unsigned char cmd);
void sendchr(unsigned char chr);
void sendstring( char* data);
void clear();
void moveCursor(unsigned char row , unsigned char col);
	