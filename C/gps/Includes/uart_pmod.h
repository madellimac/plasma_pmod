//
// Created by Biscuit on 05-Apr-18.
//

#ifndef C_UART_PMOD_H
#define C_UART_PMOD_H

int puts_pmod(const char *string);
int kbhit_pmod(void);
int getch_pmod(void);
int putchar_pmod(int value);
int getline_pmod(char *string, int n);

#endif //C_UART_PMOD_H
