/*
 * MusicalFunctions.h
 *
 *  Created on: Feb 19, 2014
 *      Author: edwinrietmeijer
 */

#ifndef MUSICALFUNCTIONS_H_
#define MUSICALFUNCTIONS_H_

#include <vector>
#include <cmath>
#include <iostream>

namespace musical {

// Temperate 12 tone scales in cents. 
const double EQUAL_CENTS[] = { 0.0, 100.0, 200.0, 300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0,
		1000.0, 1100.0, 1200.0 };

// Werckmeister 12 tone scales in cents (first note is C)
const double WERCKMEISTER_CENTS[] = {0.0, 90.225, 192.180, 294.135, 390.225, 498.045,
		588.270, 696.090, 792.180, 888.270, 996.090, 1092.180, 1200};

// Convert a cents value to a multiplier ( note relative ) ranging between 1.0 ( 0 cents ) and 2.0 ( 1200 cents )
double centToRel( const double & );

std::vector<double> convertTempScaleToRelatives( const std::vector<double> );

// Convert a note number to a frequency in hertz via a vector of note relatives, a center frequency and center note
double convertNoteNumToHertz( const int, const std::vector<double>, const double, const int );

} // namespace musical

#endif /* MUSICALFUNCTIONS_H_ */
