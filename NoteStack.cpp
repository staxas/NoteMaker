/*
 * NoteStack.cpp
 *
 *  Created on: Jan 28, 2014
 *      Author: edwinrietmeijer
 */

#include "NoteStack.h"

namespace notestack {

NoteStack::NoteStack() : longestDur_ ( 0.0 ) {
}

void NoteStack::addNote( const int & newPitch, const double & newDuration, const double & newVelocity ) {
	noteStackPitches_.push_back( newPitch );
	noteStackDurations_.push_back( newDuration );
	noteStackVelocities_.push_back( newVelocity );

	if ( newDuration > longestDur_ ) {
		longestDur_ = newDuration;
	}
}

const double & NoteStack::getLongestDur() {
	return longestDur_;
}

int NoteStack::getPitchVecSize() {
	return noteStackPitches_.size();
}

int NoteStack::getDurVecSize() {
	return noteStackDurations_.size();
}

int NoteStack::getVelVecSize() {
	return noteStackVelocities_.size();
}

int NoteStack::getPitch( int pitchIndex ) {
	if (! noteStackPitches_.empty() ) {
		if( pitchIndex >= 0 && pitchIndex < noteStackPitches_.size() ) {
			return noteStackPitches_.at( pitchIndex );
		} else {
			if ( pitchIndex >= noteStackPitches_.size() ) {
				return noteStackPitches_.back();
			} else {
				return noteStackPitches_.front();
			}
		}
	} else {
		return 0;
	}
}

double NoteStack::getDuration( int durIndex ) {
	if( durIndex >= 0 && durIndex < noteStackDurations_.size() ) {
		return noteStackDurations_.at( durIndex );
	} else {
		return longestDur_;
	}
}

double NoteStack::getVelocity( int velIndex ) {
	if( velIndex >= 0 && velIndex < noteStackVelocities_.size() ) {
		return noteStackVelocities_.at( velIndex );
	} else {
		return 0.0;
	}
}

int NoteStack::getLowestNoteIndex() {
	int lowestNoteIndex = 0;
	if (! noteStackPitches_.empty() ) {
		int lowestNote = noteStackPitches_.front();

		for ( int i = 1; i < noteStackPitches_.size(); ++i ) {

			if ( noteStackPitches_.at( i ) < lowestNote ) {
				lowestNote = noteStackPitches_.at( i );
				lowestNoteIndex = i;
			}
		}
	}
	return lowestNoteIndex;
}

void NoteStack::merge( notestack::NoteStack	* noteStackToMerge ) {
	noteStackPitches_.insert( noteStackPitches_.end(), noteStackToMerge -> noteStackPitches_.begin(), noteStackToMerge -> noteStackPitches_.end() );
	noteStackDurations_.insert( noteStackDurations_.end(), noteStackToMerge -> noteStackDurations_.begin(), noteStackToMerge -> noteStackDurations_.end() );
	noteStackVelocities_.insert( noteStackVelocities_.end(), noteStackToMerge -> noteStackVelocities_.begin(), noteStackToMerge -> noteStackVelocities_.end() );
}



void NoteStack::clear() {
	noteStackPitches_.clear();
	noteStackDurations_.clear();
	noteStackVelocities_.clear();
	//	noteStack_.clear();
}

void NoteStack::dump() {
	for ( int i = 0; i < noteStackPitches_.size(); ++i ) {
		std::cout <<  std::setw( 3 ) << noteStackPitches_.at( i )  << " " << noteStackDurations_.at( i ) << " " << noteStackVelocities_.at( i );
		if ( i < noteStackPitches_.size() - 1 ) {
			 std::cout << "  - ";
		}
	}
	std::cout << std::endl;
}
//std::vector<customtypes::Note> & NoteStack::getStack() {
//	return noteStack_;
//}

NoteStack::~NoteStack() {
}

} // namespace noteStack
