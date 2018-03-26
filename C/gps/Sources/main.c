#include "../../shared/plasmaSoPCDesign.h"
#include "../../shared/plasma.h"

#define MemoryRead(A)     (*(volatile unsigned int*)(A))
#define MemoryWrite(A,V) *(volatile unsigned int*)(A)=(V)

int main(int argc, char ** argv)
{
	char message[128] = "";
	char time[10] = "";
	char c;
	char message_id[5] = "";
	int i = 0;
	int j = 0;
	puts("Welcome to Gps project\n");
	while(1){
		if(UART_PMOD_STATUS){
			i = 0;
			j = 0;
			while((c = MemoryRead(0x40000500)) != '\n'){
				message[i] = c;
				i++;
			}
			message[i] = '\n';
			puts(message);
			while(message[j] != '$')
				j++;
			j++;
			for(int k = 0; k < 5; k++){
				message_id[k] = message[j+k];
				j++;
			}
			if(strcmp(message_id, "GPGGA") == 0){

			}
		}
	}
}
