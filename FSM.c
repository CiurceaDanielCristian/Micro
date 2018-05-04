#include <avr/io.h>
#include <stdio.h>
#include <string.h> 

#define FMSG   0
#define WAIT   1
#define RING   2
#define OPEN   3
#define COD1   4
#define COD2   5
#define COD3   6
#define ERR    7

void initLCD();
void putchLCD(char ch);
void putsLCD(char *ch);
void clrLCD();
void gotoLC(unsigned char line, unsigned char col);
char kbscan();
void wait(unsigned long int val);

int main(){

   char code_now=0x7f, code_ante;
   unsigned char kbhit=0;
   char kbcode;
   
   unsigned char loop_cnt=0;
   volatile unsigned long int delay;
   
   char cod[4]="123";
   int ring_contor=0,i;
   char buf[4];
   char stare = FMSG;
      
   sysinit();
   
   while (1){
      //determina daca este tasta apasata
      if(loop_cnt==100){
         code_ante=code_now;
         code_now = kbscan();
         if(code_now!=0x7f && code_ante==0x7f){
            kbhit=1;
            kbcode=code_now;
         }
         loop_cnt=0;
      }
      
      //SFSM
      switch (stare){
         case FMSG:
            clrLCD();
            putsLCD("Suna la 1..8,");
            gotoLC(2,1);
            putsLCD("C pentru cod:");
            stare = WAIT;
            break;
         
         case WAIT:
            if(kbhit){
               kbhit=0;
               if ('C'==kbcode){
                  clrLCD();
                  putsLCD("Cod=");
                  stare = COD1;
               }
               if (kbcode>='1' && kbcode <= '8'){
                  clrLCD();
                  putsLCD("Sun la ");
                  putchLCD(kbcode);                  
                  stare = RING;
               }
            }               
            break;
            
         case RING:            
            wait(250000);
			if(ring_contor==15){
			   stare=FMSG;
			   ring_contor=0;
			}
			ring_contor++;
            break;
            
         case COD1:
            if(kbhit){
               kbhit=0;
               if (kbcode>='0' && kbcode <= '9'){
                  buf[0]=kbcode;
                  putchLCD('*');
                  stare = COD2;               
               }
               else{
                  stare = FMSG;
               }
            }
            break;
            
         case COD2: 
            if(kbhit){
               kbhit=0;
               if (kbcode>='0' && kbcode <= '9'){
                  buf[1]=kbcode;
                  putchLCD('*');
                  stare = COD3;               
               }
               else{
                  stare = FMSG;
               }
            }
            break;
            
         case COD3: 
            if(kbhit){
               kbhit=0;
               if (kbcode>='0' && kbcode <= '9'){
                  buf[2]=kbcode;
                  putchLCD('*');
				  buf[3]='\0';
				  
                  if(strcmp(cod,buf)==0){
				    clrLCD();
				    putsLCD("Deschis!");
					stare=OPEN;
				  }               
               
                  else{
                    clrLCD();
				    putsLCD("Cod invalid");
				    stare=ERR;
                  }
                }
				else{
				  stare=FMSG;
				}
              }
            break;
            
         case OPEN: 
            for(i=0;i<5;i++)
			    wait(250000);
            //asteapta  5 secunde
            stare = FMSG;
            break;
            
            
         case ERR: 
		     for(i=0;i<5;i++)
			    wait(250000);
            //asteapta  5 secunde
            stare = FMSG;
            break;
            
      }//end switch
      loop_cnt++;
 }//end while
}//end main
