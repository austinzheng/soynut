/*
 * tone.h
 *
 *  Created on: Oct 23, 2013
 *      Author: ComputerUser
 */

#ifndef NOTE_H_
#define NOTE_H_


// Note -> frequency
//@todo generate programmatically
typedef enum {
    SILENCE = 0,
    C0 = 16,
    D0 = 18,
    E0 = 21,
    F0 = 22,
    G0 = 25,
    A0 = 28,
    B0 = 31,
    C1 = 33,
    D1 = 37,
    E1 = 41,
    F1 = 44,
    G1 = 49,
    A1 = 55,
    B1 = 62,
    C2 = 65,
    D2 = 73,
    E2 = 82,
    F2 = 87,
    G2 = 98,
    A2 = 110,
    B2 = 123,
    C3 = 131,
    D3 = 147,
    E3 = 165,
    F3 = 175,
    G3 = 196,
    A3 = 220,
    B3 = 247,
    C4 = 262,
    D4 = 294,
    E4 = 330,
    F4 = 349,
    G4 = 392,
    A4 = 440,
    B4 = 494,
    C5 = 523,
    D5 = 587,
    E5 = 659,
    F5 = 698,
    G5 = 784,
    A5 = 880,
    B5 = 988
} note_e;


#endif /* NOTE_H_ */
