//
// Created by Biscuit on 05-Apr-18.
//

#include "../Includes/gps.h"

void Gps_init( struct Gps_Data_GPGGA* newData ){

    strcpy(newData->utc_time, "");
    strcpy(newData->latitude, "");
    strcpy(newData->longitude, "");
    strcpy(newData->vert, "");
    strcpy(newData->horz, "");
    newData->fix = 0;
    newData->sats = 0;
}

int Gps_Get_GPGGA(struct Gps_Data_GPGGA* _gpsdat){
    char data[100];
    data[0] = 0;
    getline_pmod(data, 99);
    //int i = 0;
    if(getline[0] = '$'){

        return 1;
    }
    else{
        return 0;
    }
}

void Gps_Close(struct Gps_Data_GPGGA* _to_delete){
}

void Gps_Display_GPGGA(struct Gps_Data_GPGGA* _gpsdat){

}
