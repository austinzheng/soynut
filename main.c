// (c) 2013

/*
 * main.c
 */

#include <stdint.h>

#include "inc/lm4f120h5qr.h"	// LM4F120H5QR: our board
#include "inc/hw_types.h"		// Register datatypes
#include "driverlib/sysctl.h"	// Clock setup

#include "tone.h"
#include "util.h"


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

	//tone_t myTone = {A4, 5000};
	//PlayTone(&myTone);


	while (1) {
		// Square wave
		for (i = 0; i < 500; i++) {
			squareTest();
		}
		GPIO_PORTF_DATA_R &= ~(0x10);
		for (i = 0; i < 50000; i++)
			;

		// Triangle wave
		for (i = 0; i < 500; i++) {
			triangleTest();
		}
		GPIO_PORTF_DATA_R &= ~(0x10);
		for (i = 0; i < 50000; i++)
			;

		// Sawtooth wave
		for (i = 0; i < 500; i++) {
			sawtoothTest();
		}
		GPIO_PORTF_DATA_R &= ~(0x10);
		for (i = 0; i < 50000; i++)
			;

	}

	/*
	tone_t mario_theme[] = { {E5, 198}, {SILENCE, 4}, {E5, 198}, {SILENCE, 200}, {E5, 200}, {SILENCE, 200}, {C5, 200}, {E5, 200}, {SILENCE, 200}, {G5, 200}, {SILENCE, 600}, {G4, 200} };
    uint8_t iterator = 0;
    while (iterator < ARRAY_LENGTH(mario_theme)) {
        PlayTone(&(mario_theme[iterator]));
        iterator++;
    }
	*/
	return 0;
}
