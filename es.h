#define  setbit(reg,bit) reg|= 1 << bit
#define  clearbit(reg,bit) reg &= (~(1<<bit))
#define  togglebit(reg,bit) reg ^= (1<<bit)
#define  readbit(reg,bit) (reg&(1<<bit))>>bit