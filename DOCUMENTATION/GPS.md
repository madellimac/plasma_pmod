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
`uart_pmod_read()` : allows you to read a char from the uart pmod.

- ### GPS Library
To use it you just have to include gps.h in your code.
#### Functions
`gps_init()` : initialize the library

## Controller addressing

The UART Pmod Controller has been addressed to `0x40000500`.



----------

