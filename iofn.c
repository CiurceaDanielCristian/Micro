#include <avr/io.h>

#define clrbit(var,bit) var &= ~(1<<bit)
#define setbit(var,bit) var |= 1<<bit

#define E  7
#define RW 6
#define RS 5

#define IReg 0
#define SReg 0
#define DReg 1

#define nop asm("nop"::);

volatile unsigned long int delay;

void wait(unsigned long int val){
   for(delay=0;delay<val;delay++){}
}

unsigned char rd_LCDreg(unsigned char vRS){
   unsigned char data;

   DDRD=0x00;

   if(vRS==0)
   	  clrbit(PORTB,RS);
   else
   	  setbit(PORTB,RS);
   
   setbit(PORTB,RW);
   nop;
   setbit(PORTB,E);
   nop;nop;nop;nop;nop;
   data=PIND;
   clrbit(PORTB,E);
   nop;
   DDRD=0b11111111;

   return data;

   
}

void wr_LCDreg(unsigned char vRS, unsigned char data){
    
	if(vRS==0)
   	  clrbit(PORTB,RS);
    else
   	  setbit(PORTB,RS);

    clrbit(PORTB,RW);
	PORTD=data;
	nop;
	setbit(PORTB,E);
	nop;nop;nop;nop;nop;
	clrbit(PORTB,E);
    nop;
	DDRD=0xff;
}


void ckbf(){
   while(rd_LCDreg(SReg)&1<<7){
      nop;
   }
}

void initLCD(){
   ckbf();
   // Function set
   //bit 7 6 5 4   3 2 1 0
   //    0 0 1 DL  N F — — 
   //    0 0 1 1 1 1 1 1
   wr_LCDreg(IReg,0b00111111);

   ckbf();
   // entry mode set
   //bit 7 6 5 4   3 2 1 0
   //...     
   //    
   wr_LCDreg(IReg,0b00000110);

   ckbf();
   // Display on/off control
   //bit 7 6 5 4   3 2 1 0
   // ...    
   //    
   wr_LCDreg(IReg,0b00001111);

   ckbf();
   //Clear display
   wr_LCDreg(IReg,0b00000001);
}

void sysinit(){
   PORTB = 0x00;
   DDRB  = 0b11100000;
   DDRD  = 0xFF;
   wait(120000UL);
   initLCD();
}

/*
void putchLCD( char ch){
.....
}

void putsLCD( char* ch){
......
}

void clrLCD(){
.......
}

*/
