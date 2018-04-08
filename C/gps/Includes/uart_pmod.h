//
// Created by Biscuit on 05-Apr-18.
//

#ifndef C_UART_PMOD_H
#define C_UART_PMOD_H

#include "../../shared/plasmaSoPCDesign.h"
#include "../../shared/plasma.h"
#include "../../shared/plasmaMyPrint.h"

#define MemoryRead(A)     (*(volatile unsigned int*)(A))
#define MemoryWrite(A,V) *(volatile unsigned int*)(A)=(V)

int putchar_pmod(int value)
{
    while((MemoryRead(UART_PMOD_STATUS) & UART_PMOD_WRITE_AVAILABLE) == 0)
        ;
    MemoryWrite(UART_PMOD_WRITE, value);
    return 0;
}

int puts_pmod(const char *string)
{
    while(*string)
    {
        if(*string == '\n')
            putchar_pmod('\r');
        putchar_pmod(*string++);
    }
    return 0;
}

int kbhit_pmod(void)
{
    return MemoryRead(UART_PMOD_STATUS) & UART_PMOD_READ_AVAILABLE;
}

int getch_pmod(void)
{
    while(!kbhit_pmod()) ;
    return MemoryRead(UART_PMOD_READ);
}

int getline_pmod(char *string, int n){
    int i = 0;
    int c = 'a';
    while(c != '\n' && i < n){
        c = getch_pmod();
        string[i] = c;
        i++;
    }
	if( i == n){
        string[i-1] = 0;
    }
    else{
        string[i] = 0;
    }
	return i;
}

#endif //C_UART_PMOD_H
