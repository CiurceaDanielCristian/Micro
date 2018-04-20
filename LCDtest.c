#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#define S2 250000UL
void sysinit();
void putchLCD(char ch);
void putsLCD (char* ch);


int main(){
   sysinit();
   
   while(1){

   }   
}

