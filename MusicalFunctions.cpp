/*
 * MusicalFunctions.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: edwinrietmeijer
 */

#include "MusicalFunctions.h"

namespace musical {
double centToRel( const double & centsVal ) {
	return ( ( centsVal / 1200.0 ) + 1.0 );
}

std::vector<double> convertTempScaleToRelatives( const std::vector<double> cents_vector ) {
	std::vector<double> noteRelatives;
	std::vector<double>::const_iterator pos;
	for( pos = cents_vector.begin(); pos != cents_vector.end(); ++pos ) {
		std::cout << typeid( *pos ).name();
	}
	return noteRelatives;
}

double convertNoteNumToHertz( const int midiNote, const std::vector<double> tempRelatives, const double CENTER_FREQ, const int CENTER_MIDI ) {

	double noteHertz;
	double centerHertz = CENTER_FREQ;
	int relNote;
	double relOct;
	double octMultiplier = 1.0;
	int absNote;
	int relMidiNote = midiNote - CENTER_MIDI;
	if ( relMidiNote < 0 ) {
		absNote = abs ( ( double ) relMidiNote );
		relNote = 12 - ( absNote % 12 );
		relOct = ( relMidiNote / 12 ) - 1;
		if (relNote == 12) {
			relNote = 0;
			relOct += 1;
		}
		for ( int i = 0; i < std::abs( double( relOct ) ); i++) {
			octMultiplier = octMultiplier / 2.0;
		}
		relOct = octMultiplier;
	} else {
		relNote = relMidiNote % 12;
		relOct = ( relMidiNote / 12 ) + 1;
	}

	centerHertz = centerHertz * relOct;
	//	std::cout << "centerHertz: " << centerHertz << " relOct: " << relOct << " relNote: " << relNote << " tempRelatives[ relNote ]: " << tempRelatives[ relNote ] << std::endl;
	noteHertz = centerHertz * tempRelatives[ relNote ];
	//	std::cout << noteHertz << std::endl;
	//			" = ( " << CENTER_FREQ << " * " << relOct << " ) * " << tempRelatives[ relNote ] << " [ " << relNote << " ] " << endl;
	return noteHertz;
}

} // namespace musical
