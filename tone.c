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


void PlayTone(tone_t* tone) {
    // Silence is a special case: just do nothing for as long as was specified.
    if (tone->note == SILENCE) {
        // x, # loops = frequency (aka cycles/sec) / (cycles/loop) * (period of silence, in sec)
        uint32_t num_loops = ((16000000 / 1000) / 11) * (tone->duration); // clk * (1/(period) * cycles)
        uint32_t i;

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
