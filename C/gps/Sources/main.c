#include "../Includes/gps.h"

int main(int argc, char ** argv)
{
    MemoryWrite(CTRL_SL_RST, 1);
  unsigned int value =0;
  while (1) {
      //putchar(getch_pmod());

      value = MemoryRead(UART_PMOD_STATUS); // MSByte drives the 2 RBG Led (6 bit), LSByte drives the led

      MemoryWrite(CTRL_SL_RW, value); // drive the LEDs with value
  }

}
