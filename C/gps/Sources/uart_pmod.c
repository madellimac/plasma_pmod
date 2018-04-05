//
// Created by Biscuit on 05-Apr-18.
//

#include "../Includes/uart_pmod.h"

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

int putchar_pmod(int value)
{
    while((MemoryRead(UART_PMOD_STATUS) & UART_PMOD_WRITE_AVAILABLE) == 0)
        ;
    MemoryWrite(UART_PMOD_WRITE, value);
    return 0;
}

int getline_pmod(char *string, int n){
    int i = 0;
    int c = 'a';
    while(c != '\n' && i < n){
        c = getch_pmod();
        string[i] = c;
        i++;
    }
}
