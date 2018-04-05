#include "../../shared/plasmaSoPCDesign.h"
#include "../../shared/plasma.h"
#include "../../shared/plasmaMyPrint.h"
#include <stdio.h>

#define MemoryRead(A)     (*(volatile unsigned int*)(A))
#define MemoryWrite(A,V) *(volatile unsigned int*)(A)=(V)

int putchar_2(int value)
{
   while((MemoryRead(IRQ_STATUS) & IRQ_UART_WRITE_AVAILABLE) == 0)
      ;
   MemoryWrite(UART_WRITE, value);
   return 0;
}

int putchar_pmod(int value)
{
	while((MemoryRead(UART_PMOD_STATUS) & UART_PMOD_WRITE_AVAILABLE) == 0)
		;
	MemoryWrite(UART_PMOD_WRITE, value);
	return 0;
}

int puts_pmod(const char *string)
{
	while(*string)
	{
		if(*string == '\n')
			putchar_pmod('\r');
		putchar_pmod(*string++);
	}
	return 0;
}

int kbhit_pmod(void)
{
	return MemoryRead(UART_PMOD_STATUS) & UART_PMOD_READ_AVAILABLE;
}

int getch_pmod(void)
{
	while(!kbhit_pmod()) ;
	return MemoryRead(UART_PMOD_READ);
}


int main(int argc, char ** argv)
{

  while (1) {
    putchar_2(getch_pmod());
  }


	// char message[128];
	// char time[10];
	// char c;
	// char message_id[5];
	//
	// int j = 0;
	// puts("Welcome to Gps project\n");
	// puts_pmod("Coucou\n");
	// while(1){
	// 	c = getch_pmod();
	// 	if(c != 0){
	// 		puts("Char received : ");
	// 		putchar_2(getch_pmod());
	// 		puts("\n");
	// 	}

		// if((MemoryRead(UART_PMOD_STATUS) & UART_PMOD_READ_AVAILABLE) == 1){
		// 	puts("A char is available on PMOD UART\n");
		// 	i = 0;
		// 	//j = 0;
		// 	while(c != '\n' && i < 128){
		// 		if((MemoryRead(UART_PMOD_STATUS) & UART_PMOD_READ_AVAILABLE) == 1){
		// 			c = MemoryRead(UART_PMOD_READ);
		// 			char debug[] =  "Char received : \n";
		// 			debug[15] = c;
		// 			puts(debug);
		// 			message[i] = c;
		// 			i++;
		// 		}
		// 	}
			//puts(message);
			// while(message[j] != '$')
			// 	j++;
			// j++;
			// int k;
			// for( k = 0; k < 5; k++){
			// 	message_id[k] = message[j+k];
			// 	j++;
			// }
			//if(strcmp(message_id, "GPGGA") == 0){

			//}
		//}
	//}
}
