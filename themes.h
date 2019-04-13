#include "pitches.h"

//##############**"HE IS A PIRATE" Theme song of Pirates of caribbean**##############//
const PROGMEM uint16_t Pirates_note[] = {
	NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, // 8
	NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, // 8
	NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_D4, // 8
	NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_F4, // 8
	NOTE_F4, NOTE_G4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4, NOTE_D4, // 8
	0, NOTE_A3, NOTE_C4, NOTE_B3, NOTE_D4, NOTE_B3, NOTE_E4, NOTE_F4, // 8
	NOTE_F4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_C4, NOTE_D4, NOTE_C4, // 7
	NOTE_D4, 0, 0, NOTE_A3, NOTE_C4, NOTE_D4, NOTE_D4, NOTE_D4, NOTE_F4,// 9
	NOTE_G4, NOTE_G4, NOTE_G4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_A4, NOTE_G4, // 8
	NOTE_A4, NOTE_D4, 0, NOTE_D4, NOTE_E3, NOTE_F4, NOTE_F4, NOTE_G4, NOTE_A4, // 9
	NOTE_D4, 0, NOTE_D4, NOTE_F4, NOTE_E4, NOTE_E4, NOTE_F4, NOTE_D4 // 8
};
const PROGMEM uint16_t Pirates_duration[] = {
	4,8,4,8,4,8,8,8,8,4,8,4,8,4,8,8,8,8,4,8,4,8,
	4,8,8,8,8,4,4,8,8,4,4,8,8,4,4,8,8,
	8,4,8,8,8,4,4,8,8,4,4,8,8,4,4,8,4,
	4,8,8,8,8,4,4,8,8,4,4,8,8,4,4,8,8,
	8,4,8,8,8,4,4,4,8,4,8,8,8,4,4,8,8
};
//###########End of He is a Pirate song#############//



const PROGMEM uint16_t Babyshark_durations[] = {
	4, 4, 8, 8, 8, 16, 16, 4, 4,
	4, 8, 8, 8, 16, 16, 4, 4, 4,
	8, 8, 8, 16, 16, 4, 4, 4, 8, 8, 8, 16,
	16, 4, 4, 4, 8, 8, 8, 16, 16,
	4, 4, 4, 8, 8, 8, 16, 16, 4,
	4, 4, 8, 8, 8, 16, 16, 4, 4, 4, 8, 8
};

const PROGMEM uint16_t Babyshark_notes[] = {
	    NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,
	    NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,
	    NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_FS4,
	    NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,
	    NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,
	    NOTE_D4, NOTE_E4,  NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_G4,   NOTE_FS4
};

