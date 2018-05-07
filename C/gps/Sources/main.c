
#include "../Includes/gps.h"
#include "../../shared/plasmaSoPCDesign.h"
#include "../../shared/plasma.h"

#define DEBUG 0


int main(int argc, char ** argv)
{
  MemoryWrite(CTRL_SL_RST, 1);
	unsigned int value = 0;
	
	struct Gps_Data_GPGGA gpsdat;
	Gps_init(&gpsdat);

	while (1) {
		if(DEBUG == 1){
			value = MemoryRead(UART_PMOD_STATUS); // MSByte drives the 2 RBG Led (6 bit), LSByte drives the led
			MemoryWrite(CTRL_SL_RW, value); // drive the LEDs with value
		}
		else if(DEBUG == 2){
			char test[3];
			test[0] = getch_pmod();
			test[1] = '\n';
			test[2] = '\0';
			if(test[0] != 0)
				MemoryWrite(CTRL_SL_RW, 0x00000010);
			else
				MemoryWrite(CTRL_SL_RW, 0x00000000);
			puts(test);
		}
		else if(DEBUG == 3){
			char buff[128];
			getline_pmod(buff, 128-1);
			puts(buff);
		}
		else{
			while(Gps_Get_GPGGA(&gpsdat) == 0);
			Gps_Display_GPGGA(&gpsdat);
		}
	}
}
