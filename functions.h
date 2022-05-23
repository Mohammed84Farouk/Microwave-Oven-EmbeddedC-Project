/*
void portInit ( unsigned char port );
void setpinDIR ( unsigned char port , unsigned char pin , unsigned char dir);
void setportDIR (unsigned char port , unsigned char dir);
void writepin ( unsigned char port , unsigned char pin , unsigned char data);
void writeport ( unsigned char port , unsigned char data);
unsigned char readpin (unsigned char port , unsigned char pin);
unsigned char readport (unsigned char port);
void pullup_enable (unsigned char port , unsigned char pin);
void write_low (unsigned char port , unsigned char data);
void write_high (unsigned char port , unsigned char data);

void ledInit ( unsigned char port , unsigned char pin);
void ledON (unsigned char port , unsigned char pin);
void ledOFF (unsigned char port , unsigned char pin);

void buttonInit (unsigned char port , unsigned char pin);
unsigned char buttonRead (unsigned char port , unsigned char pin);
