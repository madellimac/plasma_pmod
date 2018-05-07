//
// Created by Biscuit on 05-Apr-18.
//

#ifndef C_GPS_H
#define C_GPS_H

#include "../../shared/plasmaSoPCDesign.h"
#include "../../shared/plasma.h"
#include "../../shared/plasmaMyPrint.h"

#include "../Includes/uart_pmod.h"


int my_strcmp (const char* s1, const char* s2)
{
    while (*s1 != '\0' && (*s1++ == *s2++));
    return (*((unsigned char *)--s1) < *((unsigned char *)--s2)) ? -1 : (*(unsigned char *)s1 != *(unsigned char *)s2);
}

int my_atoi(char *str)
{
    int res = 0;
	int i = 0;
    while(str[i] != '\0'){
        res = res*10 + str[i] - '0';
		i++;
	}
    return res;
}

struct Gps_Data_GPGGA{
    char utc_time[11];
    char latitude[10];
    char longitude[11];
    char vert[2];
    char horz[2];
    int fix;
    int sats;
};

void Gps_init( struct Gps_Data_GPGGA* _gpsdat ){
    _gpsdat->utc_time[0] = 0;
    _gpsdat->latitude[0] = 0;
    _gpsdat->longitude[0] = 0;
    _gpsdat->vert[0] = 0;
    _gpsdat->horz[0] = 0;
    _gpsdat->fix = 0;
    _gpsdat->sats = 0;
}

int Gps_Get_GPGGA(struct Gps_Data_GPGGA* _gpsdat){
    char data[100];
    data[0] = 0;
	char fixed[3];
	char sats[4];
    getline_pmod(data, 99);
    int i = 7;
	int v = 6;
    if(data[0] == '$'){
		char inst[6] = {data[1], data[2], data[3], data[4], data[5], '\0'};
		if(my_strcmp(inst, "GPGGA") == 0){
			while(data[i] != ','){
				_gpsdat->utc_time[i-v-1] = data[i];
				i++;
			}
			_gpsdat->utc_time[i-v-1] = '\0';
			v = i;
			i++;

			while(data[i] != ','){
				_gpsdat->latitude[i-v-1] = data[i];
				i++;
			}
			_gpsdat->latitude[i-v-1] = '\0';
			v = i;
			i++;

			while(data[i] != ','){
				_gpsdat->vert[i-v-1] = data[i];
				i++;
			}
			_gpsdat->vert[i-v-1] = '\0';
			v = i;
			i++;

			while(data[i] != ','){
				_gpsdat->longitude[i-v-1] = data[i];
				i++;
			}
			_gpsdat->longitude[i-v-1] = '\0';
			v = i;
			i++;

			while(data[i] != ','){
				_gpsdat->horz[i-v-1] = data[i];
				i++;
			}
			_gpsdat->horz[i-v-1] = '\0';
			v = i;
			i++;

			while(data[i] != ','){
				fixed[i-v-1] = data[i];
				i++;
			}
			fixed[i-v-1] = '\0';
			_gpsdat->fix = my_atoi(fixed);
			v = i;
			i++;

			while(data[i] != ','){
				sats[i-v-1] = data[i];
				i++;
			}
			sats[i-v-1] = '\0';
			_gpsdat->sats = my_atoi(sats);
			v = i;
			i++;
			return 1;
		}
    }
    return 0;
}

void Gps_Display_GPGGA(struct Gps_Data_GPGGA* _gpsdat){
	puts("\nGPGGA DATA : \n");
	puts("UTC :");
	puts(_gpsdat->utc_time);
	puts("\n");
	puts("Latitude :");
	puts(_gpsdat->latitude);
	puts(_gpsdat->vert);
	puts("\n");
	puts("Longitude :");
	puts(_gpsdat->longitude);
  puts(_gpsdat->horz);
	puts("\n");
	my_printf("Fix : ", _gpsdat->fix);
	my_printf("Satellites : ", _gpsdat->sats);
}

#endif //C_GPS_H
