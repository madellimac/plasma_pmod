//
// Created by Biscuit on 05-Apr-18.
//

#include "gps.h"

struct Gps_Data_GPGGA* Gps_init(){
    struct Gps_Data_GPGGA* newData= malloc(sizeof(Gps_Data_GPGGA));
    strcpy(newData->utc_time, "");
    strcpy(newData->latitude, "");
    strcpy(newData->longitude, "");
    strcpy(newData->vert, "");
    strcpy(newData->horz, "");
    newData->fix = false;
    newData->sats = 0;
    return newData;
}

int Gps_Get_GPGGA(struct Gps_Data_GPGGA* _gpsdat){
    char data[100] = "";
    getline_pmod(data, 99);
    int i = 0;
    if(getline[0] = '$'){

        return 1;
    }
    else{
        return 0;
    }
}

void Gps_Close(struct Gps_Data_GPGGA* _to_delete){
    free(_to_delete);
}

void Gps_Display_GPGGA(struct Gps_Data_GPGGA* _gpsdat){

}

