/*
 * PerNorgard.cpp
 *
 *  Created on: Apr 3, 2014
 *      Author: edwinrietmeijer
 */

#include "PerNorgard.h"

namespace pernorgard {

PerNorgard::PerNorgard() : firstNote_( 0 ), secondNote_( 1 ), newFirstNote_( 0 ), newSecondNote_( 1 ), noteDiff_( 1 ) {
	scriptName_ = "pernorgard";
	genId_ = typeid( this ).name();
	generatorReturnType_ = gentypes::PITCH;
	generatorReturnOrientation_ = gentypes::VERTICAL;
}

int PerNorgard::next() {
	// Set the current first and second note to the notes calculated in the last run of this function
	firstNote_ = newFirstNote_;
	secondNote_ = newSecondNote_;

	prevNoteVec_.push_back( firstNote_ );
	prevNoteVec_.push_back( secondNote_ );

	// Calculate and add the difference between the two notes to the note difference queue
	noteDiff_ = prevNoteVec_.at( 1 ) - prevNoteVec_.at( 0 );

	// Remove last note used for note difference calculation
	prevNoteVec_.erase( prevNoteVec_.begin() );

	// Use the note difference to calculate the next two notes
	newFirstNote_ = firstNote_ - noteDiff_;
	newSecondNote_ = secondNote_ + noteDiff_;

	// Send the two new note pitches to the generator mediator
	addPitch( firstNote_ );
	addPitch( secondNote_ );
//	genReturnStruct_.generatorReturnType = gentypes::PITCH;

//	std::cout << "first note " << firstNote_ << ", second note " << secondNote_<< std::endl;
//	std::cout << "new first note " << newFirstNote_ << ", new second note " << newSecondNote_<<", notediff " << noteDiff_ << std::endl;

	return 1;
}

void PerNorgard::set( std::vector<double> variables ) {
	if ( variables.size() >=2 ) {
		if ( abs( static_cast<int>( variables.at( 0 ) ) - static_cast<int>( variables.at( 1 ) ) ) > 0 ) {
			newFirstNote_ = static_cast<int>( variables.at( 0 ) );
			newSecondNote_ = static_cast<int>( variables.at( 1 ) );
		}
	}
}

PerNorgard::~PerNorgard() {
}


} /* namespace pernorgard */
