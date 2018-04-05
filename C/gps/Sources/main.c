#include "../../shared/plasmaSoPCDesign.h"
#include "../../shared/plasma.h"
#include "../../shared/plasmaMyPrint.h"
#include <stdio.h>

#include "uart_pmod.h"
#include "gps.h"

#define MemoryRead(A)     (*(volatile unsigned int*)(A))
#define MemoryWrite(A,V) *(volatile unsigned int*)(A)=(V)

int main(int argc, char ** argv)
{
    MemoryWrite(CTRL_SL_RST, 1);

  while (1) {
      //putchar(getch_pmod());

      value =  MemoryRead(UART_PMOD_STATUS); // MSByte drives the 2 RBG Led (6 bit), LSByte drives the led
      MemoryWrite(CTRL_SL_RW, value); // drive the LEDs with value
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
