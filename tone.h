/*
 * tone.h
 *
 *  Created on: Oct 23, 2013
 *      Author: ComputerUser
 */

#ifndef TONE_H_
#define TONE_H_

#include "note.h"


typedef struct tone_s {
    note_e note;
    uint16_t duration;
} tone_t;


void PlayTone(tone_t* tone);


#endif /* TONE_H_ */
