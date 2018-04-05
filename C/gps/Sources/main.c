#include "../../shared/plasmaSoPCDesign.h"
#include "../../shared/plasma.h"
#include "../../shared/plasmaMyPrint.h"
#include <stdio.h>
#include <stdlib.h>

//#include "../Includes/uart_pmod.h"
//#include "../Includes/gps.h"

#define MemoryRead(A)     (*(volatile unsigned int*)(A))
#define MemoryWrite(A,V) *(volatile unsigned int*)(A)=(V)

struct Gps_Data_GPGGA {
    char utc_time[11];
    char latitude[10];
    char longitude[11];
    char vert[2];
    char horz[2];
    int fix;
    int sats;
};

struct Gps_Data_GPGGA* Gps_init();
void Gps_close(struct Gps_Data_GPGGA* _to_delete);
int Gps_Get_GPGGA(struct Gps_Data_GPGGA* _gpsdat);
void Gps_Display_GPGGA(struct Gps_Data_GPGGA* _gpsdat);

int puts_pmod(const char *string);
int kbhit_pmod(void);
int getch_pmod(void);
int putchar_pmod(int value);
int getline_pmod(char *string, int n);

int main(int argc, char ** argv)
{
    MemoryWrite(CTRL_SL_RST, 1);
  unsigned int value =0;
  while (1) {
      //putchar(getch_pmod());

      value = MemoryRead(UART_PMOD_STATUS); // MSByte drives the 2 RBG Led (6 bit), LSByte drives the led
      for (int i = 0; i < 2000000; i++) {

      }
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

int putchar_pmod(int value)
{
    while((MemoryRead(UART_PMOD_STATUS) & UART_PMOD_WRITE_AVAILABLE) == 0)
        ;
    MemoryWrite(UART_PMOD_WRITE, value);
    return 0;
}

int getline_pmod(char *string, int n){
    int i = 0;
    int c = 'a';
    while(c != '\n' && i < n){
        c = getch_pmod();
        string[i] = c;
        i++;
    }
}


struct Gps_Data_GPGGA* Gps_init(){
    /*struct Gps_Data_GPGGA* newData= malloc(sizeof(struct Gps_Data_GPGGA));
    strcpy(newData->utc_time, "");
    strcpy(newData->latitude, "");
    strcpy(newData->longitude, "");
    strcpy(newData->vert, "");
    strcpy(newData->horz, "");
    newData->fix = 0;
    newData->sats = 0;
    return newData;*/
    return 0;
}

int Gps_Get_GPGGA(struct Gps_Data_GPGGA* _gpsdat){
    char data[100] = "";
    getline_pmod(data, 99);
    //int i = 0;
    if(data[0] = '$'){

        return 1;
    }
    else{
        return 0;
    }
}

void Gps_Close(struct Gps_Data_GPGGA* _to_delete){
    //free(_to_delete);
}

void Gps_Display_GPGGA(struct Gps_Data_GPGGA* _gpsdat){

}
