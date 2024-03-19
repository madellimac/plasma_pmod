#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>


#include "../../shared/plasmaCoprocessors.h"
#include "../../shared/plasmaIsaCustom.h"
#include "../../shared/plasmaMisc.h"
#include "../../shared/plasmaSoPCDesign.h"
#include "../../shared/plasmaMyPrint.h"
#include "../../shared/plasma.h"

#include "../Includes/scale.h"

#define HEIGHT 28
#define WIDTH 28

void sleep(unsigned int ms) // fonction qui impose un delay en millisecondes 
{	// la fréquence d'horloge vaut 50 MHz
	unsigned int t0 = MemoryRead(TIMER_ADR);
	while (MemoryRead(TIMER_ADR) - t0 < 50000 * ms) // On compte 50000 périodes pour 1 ms
		;
}

int send_char(int value)
{
   while((MemoryRead(IRQ_STATUS) & IRQ_UART_WRITE_AVAILABLE) == 0)
      ;
   MemoryWrite(UART_WRITE, value);
   return 0;
}

unsigned char wait_data()
{
	while( !(MemoryRead(IRQ_STATUS) & IRQ_UART_READ_AVAILABLE) );
	unsigned char cc = MemoryRead(UART_READ);
	return cc;
}

inline void printPixel(char row, char col, int color)
{
	int buff = 0x00000000;

	buff = color;
	buff = (buff << 8) | row;
	buff = (buff << 8) | col;

	MemoryWrite(OLED_BITMAP_RW, buff);
}

unsigned char new_image[30][30];

typedef struct Image {
	int pixels[30][30];
}Image;

typedef struct Filtre {
	int coeff[3][3];
}Filtre;


void convolution(Image* data, signed char filtre[][3] ) {
	
	for (int i = 1; i < HEIGHT-1; i++) {
		for (int j = 1; j < WIDTH-1; j++) {
			new_image[i][j] = data->pixels[i][j] * filtre[1][1] + data->pixels[i - 1][j - 1] * filtre[0][0] +
				data->pixels[i + 1][j + 1] * filtre[2][2] +
				data->pixels[i - 1][j + 1] * filtre[0][2] +
				data->pixels[i + 1][j - 1] * filtre[2][0] +
				data->pixels[i][j - 1] * filtre[1][0] +
				data->pixels[i][j + 1] * filtre[1][2];
		}
	}
				
	for (int i = 1; i < HEIGHT - 1; i++) {
		for (int j = 1; j < WIDTH - 1; j++) {
			data->pixels[i][j] = new_image[i][j];
		}
	}
}

//unsigned char images[30*5][30] = {0};

//unsigned char small_image[16] = {15, 16, 65, 124, 210, 64, 98, 14, 67, 81, 94, 165, 154, 64, 84, 34};
Image images[6];
//Filtre filtres[1];
signed char filtre[3][3] = { {1, 0, -1}, {2, 0, -2}, {1, 0, -1} };

// Filters
int weights1[16*1*5*5];
int bias1[16];
int weights2[16*32*5*5];
int bias2[32];
int weightsFull[15680];
int biasFull[10];

int main(int argc, char **argv) {

	int r, g, b, pixel, coeff;
	unsigned int start_c, stop_c;
	
	/**********/
	// Reset the RGB OLED screen and display a white screen
	/**********/

	MemoryWrite(OLED_MUX, OLED_MUX_BITMAP); // Select the RGB OLED Bitmap controler
	MemoryWrite(OLED_BITMAP_RST, 1); // Reset the oled_rgb PMOD
	MemoryWrite(SEVEN_SEGMENT_RST, 1); // reset the 7 segment controler
	MemoryWrite(CTRL_SL_RST, 1); // reset the sw/led controler

	
	for(int py = 0; py < HEIGHT; py++)
	{
		for(int px = 0; px < WIDTH; px ++){
			
			printPixel(py, px, 0x0000); // clear the RGB OLED screen
		}
	}

	
	/**********/
	// Read and store values coming from the UART
	/**********/
	
	int images_number = wait_data();

	MemoryWrite(SEVEN_SEGMENT_REG, 1);
	for (int image = 0; image < images_number; image++)
	{
		for (int py = 0; py < HEIGHT; py++)
		{
			for (int px = 0; px < WIDTH; px++) {
				r = wait_data();
				g = wait_data();
				b = wait_data();
				pixel = (r + g + b) / 3;

				images[image].pixels[py + 1][px + 1] = pixel;
			}
		}
	
	}

	MemoryWrite(SEVEN_SEGMENT_REG, 11);
	
	for(int coeff_num=0; coeff_num<16*1*5*5; coeff_num++){
	
		int coeff1 = wait_data();
		coeff1 = coeff1 << 23;
		int coeff2 = wait_data();
		coeff2 = coeff2 << 15;
		int coeff3 = wait_data();
		coeff3 = coeff3 << 7;
		int coeff4 = wait_data();
		coeff4 = coeff4 << 0;


		weights1[coeff_num] = coeff1 + coeff2 + coeff3 + coeff4;
	}

	MemoryWrite(SEVEN_SEGMENT_REG, 12);
	for(int coeff_num=0; coeff_num<16; coeff_num++){
		int coeff1 = wait_data();
		coeff1 = coeff1 << 23;
		int coeff2 = wait_data();
		coeff2 = coeff2 << 15;
		int coeff3 = wait_data();
		coeff3 = coeff3 << 7;
		int coeff4 = wait_data();
		coeff4 = coeff4 << 0;

		bias1[coeff_num] = coeff1 + coeff2 + coeff3 + coeff4;

	}
	MemoryWrite(SEVEN_SEGMENT_REG, 13);
	for(int coeff_num=0; coeff_num<32*16*5*5; coeff_num++){
		int coeff1 = wait_data();
		coeff1 = coeff1 << 23;
		int coeff2 = wait_data();
		coeff2 = coeff2 << 15;
		int coeff3 = wait_data();
		coeff3 = coeff3 << 7;
		int coeff4 = wait_data();
		coeff4 = coeff4 << 0;


		weights2[coeff_num] = coeff1 + coeff2 + coeff3 + coeff4;
	}
	MemoryWrite(SEVEN_SEGMENT_REG, 14);
	for(int coeff_num=0; coeff_num<32; coeff_num++){
		int coeff1 = wait_data();
		coeff1 = coeff1 << 23;
		int coeff2 = wait_data();
		coeff2 = coeff2 << 15;
		int coeff3 = wait_data();
		coeff3 = coeff3 << 7;
		int coeff4 = wait_data();
		coeff4 = coeff4 << 0;

		bias2[coeff_num] = coeff1 + coeff2 + coeff3 + coeff4;
	}
MemoryWrite(SEVEN_SEGMENT_REG, 15);
	for(int coeff_num=0; coeff_num<15680; coeff_num++){
		int coeff1 = wait_data();
		coeff1 = coeff1 << 23;
		int coeff2 = wait_data();
		coeff2 = coeff2 << 15;
		int coeff3 = wait_data();
		coeff3 = coeff3 << 7;
		int coeff4 = wait_data();
		coeff4 = coeff4 << 0;


		weightsFull[coeff_num] = coeff1 + coeff2 + coeff3 + coeff4;
	}
	MemoryWrite(SEVEN_SEGMENT_REG, 16);
	for(int coeff_num=0; coeff_num<10; coeff_num++){
		int coeff1 = wait_data();
		coeff1 = coeff1 << 23;
		int coeff2 = wait_data();
		coeff2 = coeff2 << 15;
		int coeff3 = wait_data();
		coeff3 = coeff3 << 7;
		int coeff4 = wait_data();
		coeff4 = coeff4 << 0;

		biasFull[coeff_num] = coeff1 + coeff2 + coeff3 + coeff4;
	}
	
	//filtres[0].pixels = { {1, 1, 0, -1, -1},{1, 1, 0, -1, -1}, {2, 2, 0, -2, -2},{1, 1, 0, -1, -1}, {1, 1, 0, -1, -1} };
	//filtres[0].coeff = {{1, 0, -1}, {2, 0, -2},{1, 0, -1}};

	/**********/
	// Processing
	/**********/
	
	// Read the timer value before the processing starts
	start_c = r_timer();

	MemoryWrite(SEVEN_SEGMENT_REG, 111);
	
	
	// Convolution 
	
	
	for (int image = 0; image < images_number; image++)
	{
		
		convolution(&(images[image]), filtre);

	}
	
	// Read the timer value after the processing is over
	stop_c = r_timer();
	MemoryWrite(SEVEN_SEGMENT_REG, (stop_c - start_c));

	/**********/
	// Display the resulting image
	/**********/

	MemoryWrite(OLED_BITMAP_RST, 1); // Reset the oled_rgb PMOD
	MemoryWrite(SEVEN_SEGMENT_REG, images_number);

	
	int i = 0;
	int remaining_images = images_number;

	while (i < images_number) {
		if (MemoryRead(BUTTONS_CHANGE) == 1 && MemoryRead(BUTTONS_VALUES)==1)
		{
			sleep(1000);
			MemoryWrite(SEVEN_SEGMENT_RST, 1); // reset the 7 segment controler
			MemoryWrite(SEVEN_SEGMENT_REG, remaining_images);
			for (int py = 0; py < HEIGHT; py++)
			{
				for (int px = 0; px < WIDTH; px++) {
					pixel = images[i].pixels[py][px];
					pixel = ((pixel >> 3) << 11) | ((pixel >> 2) << 5) | (pixel >> 3);
					printPixel(py, px, pixel);
				}
			}
			i = i + 1;
			remaining_images = remaining_images - 1;
		}
		//sleep(3000); // 3s
	}
	MemoryWrite(SEVEN_SEGMENT_REG, remaining_images);
	
	/*
	
	for (int py = 0; py < H; py++)
	{
		for (int px = 0; px < W; px++) {
			pixel = images[py+1][px+1];
			pixel = ((pixel >> 3) << 11) | ((pixel >> 2) << 5) | (pixel >> 3);
			printPixel(py, px, pixel);
		}
	}
	*/
			//i = i + 1;
			//MemoryWrite(SEVEN_SEGMENT_REG, i);
		//}
	//}
	/**********/
	// Affichage du nombre de cycles nécessaires au traitement
	/**********/
	
	//MemoryWrite(CTRL_SL_RW, (stop_c - start_c));
	MemoryWrite(OLED_BITMAP_RST, 1); // Reset the oled_rgb PMOD
	
	return(0);
	
}