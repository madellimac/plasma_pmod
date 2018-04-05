# GPS Pmod Controller Presentation

## Introduction

New features as been added to the plasma softcore processor. The GPS Pmod module is based on an UART communication so to use it, it is necessarry to implement a new UART HDL module, this has been done based on the original UART controller with some modifications to allow it to run on 9600 Bauds. It is cabled on pmod pins in the top plasma HDL.

## Using the GPS Pmod Controller

-   ### Synthesis
The Makefile has been modified to include necessary HDL modules. To add the UART Pmod HDL to the synthesis and generate the bitstream you can just type : 
> make plasma CONFIG_UART_PMOD=yes
- ### Project compilation
In the Makefile there is also modification to add a new project which is the GPS Pmod Controller demo. To compile it and send it to the FPGA type : 
> make send CONFIG_PROJECT=gps

## Library Utilisation

To use the GPS Pmod controller a new function set has been made. We can separate GPS functions and UART Pmod functions so it is possible to use the controller to communicate with other peripherals.

 - ### UART Pmod Library
To use it you just have to include `uart_pmod.h` in your code.
#### Functions
`int puts_pmod(const char *string)` : allows you to send a string through uart pmod (the string should end with an '\0')
`int getch_pmod(void)` : returns a char read from uart pmod
`int putchar_pmod(int value)` : send a char through uart pmod
`int getline_pmod(char *string, int n)` : read a line from uart pmod (until '\n' or n char read) and returns the amount of char read.

- ### GPS Library
To use it you just have to include gps.h in your code. You shall first create a Gps_Data_XXXXX structure and initialize it before you try to fill it with data.
#### Structures
`struct Gps_Data_GPGGA {
    char utc_time[11];
    char latitude[10];
    char longitude[11];
    char vert[2];
    char horz[2];
    int fix;
    int sats;
};`

This structure contains most of paramaters which can be read on a Gps GPGGA line :
`utc_time` : UTC Time HHMMSS.SSSS
`latitude` : Latitude XXXX.XXXX
`longitude`: Longitude XXXXX.XXXX
`vert` : Orientation of latitude (N, S)
`horz` : Orientation of longitude (W, E)
`fix` : Gps module got fix
`sats` : Amount of satellites used to determine position

#### Functions
`void Gps_init(struct Gps_Data_GPGGA* _gpsdat);` : Initialize a Gps_Data_GPGGA structure
`int Gps_Get_GPGGA(struct Gps_Data_GPGGA* _gpsdat);` : Fill a Gps_Data_GPGGA structure with data read from uart pmod
`void Gps_Display_GPGGA(struct Gps_Data_GPGGA* _gpsdat);` : Display data on the Uart Usb

## Controller addressing

The UART Pmod Controller has been addressed to `0x40000500`.

## Issues



----------

