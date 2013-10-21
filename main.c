// (c) 2013

/*
 * main.c
 */

#include "inc/lm4f120h5qr.h"

int main(void) {
	
	// Enable port F
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

	long int i;
	for (i=0; i<10000; i++) {
		// Let the peripheral initialize
		;
	}

	// PF4.
	// 0b00001000
	GPIO_PORTF_DIR_R = 0x10;
	GPIO_PORTF_DEN_R = 0x10;

	while(1) {
		// Don't do anything.
		GPIO_PORTF_DATA_R |= 0x10;

		for (i=0; i<2000; i++) {
			;
		}

		GPIO_PORTF_DATA_R &= ~(0x10);

		for (i=0; i<2000; i++) {
			;
		}
	}

	return 0;
}
