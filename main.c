// (c) 2013

/*
 * main.c
 */

#include "inc/lm4f120h5qr.h"	// LM4F120H5QR: our board
#include "inc/hw_types.h"		// Register datatypes
#include "driverlib/sysctl.h"	// Clock setup


int main(void) {
    // Use the external ("main") oscillator
    // Don't divide that oscillation.
    // Don't multiply that oscillation.
	// Oscillates at 16MHz.
    SysCtlClockSet(SYSCTL_OSC_MAIN | SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_XTAL_16MHZ);

	// Enable port F
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

	long int i;
	for (i=0; i<10000; i++) {
		// Let the peripherals initialize
		;
	}

	// PF4.
	// 0b00001000
	GPIO_PORTF_DIR_R = 0x10;
	GPIO_PORTF_DEN_R = 0x10;

	while(1) {
		// Don't do anything.
		GPIO_PORTF_DATA_R |= 0x10;

		// 440Hz (A4): (16*10^6 cycle / 1 sec) * (1 loop / 11 cycle) * (1 sec / 880 transition)
		// -> 1652 loop / transition
		for (i=0; i<1652; i++) {
			;
		}

		GPIO_PORTF_DATA_R &= ~(0x10);

		for (i=0; i<1652; i++) {
			;
		}
	}

	return 0;
}
