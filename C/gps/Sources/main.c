#include "../Includes/gps.h"
#include "../../shared/plasmaSoPCDesign.h"
#include "../../shared/plasma.h"

int main(int argc, char ** argv)
{
    MemoryWrite(CTRL_SL_RST, 1);
	unsigned int value =0;
	int debug = 2;
	while (1) {
		if(debug == 1){
			value = MemoryRead(UART_PMOD_STATUS); // MSByte drives the 2 RBG Led (6 bit), LSByte drives the led
			MemoryWrite(CTRL_SL_RW, value); // drive the LEDs with value
		}
		else if(debug == 2){
			char test[3];
			test[0] = getchar_pmod();
			test[1] = '\n';
			test[2] = '\0';
			if(test[0] != 0)
				MemoryWrite(CTRL_SL_RW, 0x00000010);
			else
				MemoryWrite(CTRL_SL_RW, 0x00000000);
			puts(test);
		}
		else{
			struct Gps_Data_GPGGA gpsdat;
			Gps_init(&gpsdat);
			int ok = Gps_Get_GPGGA(&gpsdat);
			if(ok == 1)
				Gps_Display_GPGGA(&gpsdat);
		}
	}
}
