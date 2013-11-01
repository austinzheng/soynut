/*
 * tone.c
 *
 *  Created on: Oct 23, 2013
 *      Author: ComputerUser
 */

#include <stdint.h>

#include "inc/lm4f120h5qr.h"    // Registers

#include "tone.h"
#include "note.h"


// Try A440 as triangle note.
// A440 = 440 cycles/second. If dividing into 16 intervals, each is 1/7040 seconds in duration
// 16 MHz clock, 11 cycles per loop = 1454545 loops/sec
// 206 loops per pwm (1454545/7040)
/*
 * 0: 3.125% = 6
 * 1: 13
 * 2: 19
 * 3: 26
 * 4: 32
 * 5: 39
 * 6: 45
 * 7: 52
 * 8: 58
 * 9: 64
 * 10: 71
 * 11: 77
 * 12: 84
 * 13: 90
 * 14: 97
 * 15: 103
 */

void triangleTest() {
	long levels[16] = { 6, 19, 32, 45, 58, 71, 84, 97, 103, 90, 77, 64, 52, 39, 26, 13};

	int high = 0;
		int low = 0;
		int i, j;
		for (i=0; i<16; i++) {
			high = levels[i];
			low = 206 - high;
			// High
			GPIO_PORTF_DATA_R |= 0x10;
			for (j=0; j<high; j++) ;
			// Low
			GPIO_PORTF_DATA_R &= ~(0x10);
			for (j=0; j<low; j++) ;
		}
}

void sawtoothTest() {
	long levels[16] = { 6, 13, 19, 26, 32, 39, 45, 52, 58, 64, 71, 77, 84, 90, 97, 103 };

	int high = 0;
	int low = 0;
	int i, j;
	for (i=0; i<16; i++) {
		high = levels[i];
		low = 206 - high;
		// High
		GPIO_PORTF_DATA_R |= 0x10;
		for (j=0; j<high; j++) ;
		// Low
		GPIO_PORTF_DATA_R &= ~(0x10);
		for (j=0; j<low; j++) ;
	}
}

void squareTest() {
	int i;
	GPIO_PORTF_DATA_R |= 0x10;
	for (i=0; i<1653; i++) ;
	GPIO_PORTF_DATA_R &= ~(0x10);
	for (i=0; i<1654; i++) ;
}



void PlayTone(tone_t* tone) {
    // Silence is a special case: just do nothing for as long as was specified.
    if (tone->note == SILENCE) {
        // x, # loops = frequency (aka cycles/sec) / (cycles/loop) * (period of silence, in sec)
        uint64_t num_loops = ((16000000 / 1000) / 33) * (tone->duration); // clk * (1/(period) * cycles)
        //@todo why does /33 sound so much more accurate than /11?
        uint64_t i;

        GPIO_PORTF_DATA_R &= ~(0x10);

        for (i=0; i<num_loops; i++) {
            ;
        }

        return;
    }

    // x, # sec / note period = 1/(frequency) = 1/(tone->note)
    // y, # note periods = duration / x = (tone->duration/1000) / (1/(tone->note))
    uint64_t num_outer_loops = (tone->duration * tone->note) / 3000;
    //@todo why does /3000 sound so much more accurate than /1000?

    // z, # loops / transition = (16*10^6 cycle / 1 sec) * (1 loop / 11 cycle) * (1 sec / x transitions)
    uint64_t num_inner_loops = ((16000000 / 11) / 2) / (tone->note);

    uint64_t i;
    uint64_t j;

    for(i=0; i<num_outer_loops; i++) {
        GPIO_PORTF_DATA_R |= 0x10;
        for (j=0; j<num_inner_loops; j++) {
            ;
        }

        GPIO_PORTF_DATA_R &= ~(0x10);
        for (j=0; j<num_inner_loops; j++) {
            ;
        }
    }
}
