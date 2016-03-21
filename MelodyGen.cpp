/*
 * MelodyGen.cpp
 *
 *  Created on: May 2, 2014
 *      Author: edwinrietmeijer
 */

#include "MelodyGen.h"

namespace melodygen {

std::random_device rd;
std::RANDOM_DEV my_random_device( rd() );

MelodyGen::MelodyGen() : startNote_( 0 ), currNote_( 0 ), nextNote_( 0 ), lowestNote_( 0 ), highestNote_( 11 ), movement_( 1 ), isLastLeap_( false ), melodyLeapChance_( 0 ) {
	// MANDATORY FOR ALL GENERATOR CLASSES:
	scriptName_ = "melodygen";
	genId_ = typeid( this ).name();
	generatorReturnType_ = gentypes::PITCH;
	generatorReturnOrientation_ = gentypes::HORIZONTAL;
}

void MelodyGen::init() {
	startNote_ = 0;
	currNote_ = 0;
	movement_ = 1;
}


int MelodyGen::next() {

	if ( nextNote_ >= highestNote_ ) {
		nextNote_ = highestNote_;
		movement_ = -1;
	}

	if ( nextNote_ <= lowestNote_ ) {
		nextNote_ = lowestNote_;
		movement_ = 1;
	}	currNote_ = nextNote_;

	melodyLeapChance_++;
	if ( melodyLeapChance_ >= 6 ) {
		melodyLeapChance_ = 5;
	}

	int steps = 1;

	std::uniform_int_distribution<int> chordLeapCheck( melodyLeapChance_, 5 );

	if ( chordLeapCheck( rd ) == 5 ) {
		melodyLeapChance_ = 0;
		isLastLeap_ = true;
	}


	if( isLastLeap_ ) {
		isLastLeap_ = false;
		std::uniform_int_distribution<int> leapSize( 2, highestNote_ - currNote_ );
		steps = leapSize( rd );
		nextNote_ += steps * movement_;
		movement_ = movement_ *  -1;
	} else {
		nextNote_ += steps * movement_;
	}


	addPitch( currNote_ );
	return 1;
}


MelodyGen::~MelodyGen() {
	// TODO Auto-generated destructor stub
}

} /* namespace melodygen */
