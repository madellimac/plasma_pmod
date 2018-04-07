//
// Created by Biscuit on 05-Apr-18.
//

#ifndef C_GPS_H
#define C_GPS_H

#include "../../shared/plasmaSoPCDesign.h"
#include "../../shared/plasma.h"
#include "../../shared/plasmaMyPrint.h"

#include "../Includes/uart_pmod.h"

struct Gps_Data_GPGGA{
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

#endif //C_GPS_H
