#include "../Includes/gps.h"
#include "../../shared/plasmaSoPCDesign.h"
#include "../../shared/plasma.h"

int main(int argc, char ** argv)
{
    MemoryWrite(CTRL_SL_RST, 1);
	unsigned int value =0;
	debug = 1;
	while (1) {
		if(debug == 1){
			value = MemoryRead(UART_PMOD_STATUS); // MSByte drives the 2 RBG Led (6 bit), LSByte drives the led
			MemoryWrite(CTRL_SL_RW, value); // drive the LEDs with value
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
