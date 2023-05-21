/*
 * Tetris_V1.c
 *
 * Created: 06/04/2021 19:41:36
 * Author : dakak
 */  

#include "analogRead.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <util/delay.h>

// https://wokwi.com/projects/296234816685212169

// B (digital pin 8 to 13)
// C (analog input pins)
// D (digital pins 0 to 7)

#define VERT_PIN 0
#define HORZ_PIN 1
#define SEL_PIN  2

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

#define BUTTON_IS_CLICKED(PINB,BUTTON_PIN) !BIT_CHECK(PINB,BUTTON_PIN)

#define min(X,Y) ((X) < (Y) ? (X) : (Y))
#define max(X,Y) ((X) > (Y) ? (X) : (Y))

int main()
{
	BIT_CLEAR(DDRC,VERT_PIN);
	BIT_CLEAR(DDRC,HORZ_PIN);

	  //Sätt till INPUT_PULLUP
    BIT_CLEAR(DDRD,SEL_PIN); // INPUT MODE
    BIT_SET(PORTD,SEL_PIN); 

	init_serial();
	int y = 0;
	int x = 0;
	int maxX = 16;
	int maxY = 8;
	while (1) {
		int horz = analogRead(HORZ_PIN);
  		int vert = analogRead(VERT_PIN);
		if (vert < 300) {
			y = min(y + 1, maxY);
			printf("y:%d\n", y);
		}
		if (vert > 700) {
			y = max(y - 1, 0);
			printf("y:%d\n", y);
		}
		if (horz > 700) {
			x = min(x + 1, maxX);
			printf("x:%d\n", x);
		}
		if (horz < 300) {
			x = max(x - 1, 0);
			printf("x:%d\n", x);
		}
		if (BUTTON_IS_CLICKED(PIND,SEL_PIN)) {
			printf("CLICK\n");
		}		
		_delay_ms(100);
  	}
	return 0;
}