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

int puts_pmod(const char *string);
int kbhit_pmod(void);
int getch_pmod(void);
int putchar_pmod(int value);
int getline_pmod(char *string, int n);

#endif //C_UART_PMOD_H
