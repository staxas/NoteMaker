/*
 * NoteBlock.cpp
 *
 *  Created on: Jan 28, 2014
 *      Author: edwinrietmeijer
 */

#include "NoteBlock.h"

namespace noteblock {

NoteBlock::NoteBlock() : addAllOfThisVector_( customtypes::PITCH ), sPos_( noteStackList_.begin() ), isLastStackClosed_( false ) {

}

void NoteBlock::newStack() {
	noteStackList_.push_back( new notestack::NoteStack );
}

void NoteBlock::setMainVar( const customtypes::NoteVars & addThese ) {
	addAllOfThisVector_ = addThese;
}

void NoteBlock::add( int & newPitch, double & newDuration, double & newVelocity ) {
	if ( isLastStackClosed_ ) {
		this -> newStack();
	}
	noteStackList_.back() -> addNote( newPitch, newDuration, newVelocity );
}


//void NoteBlock::add( customtypes::Note newNote ) {
//	if ( isLastStackClosed_ ) {
//		this -> newStack();
//	}
//	noteStackList_.back() -> addNote( newNote );
//}

void NoteBlock::close() {
	isLastStackClosed_ = true;
}


int NoteBlock::addThisVector(  const std::vector<int> & pitchVec, const std::vector<double> & durVec, const std::vector<double> & velVec ) {
	int vecSize;
	switch( addAllOfThisVector_ ) {
	case customtypes::VELOCITY:
		vecSize = durVec.size();
		break;
	case customtypes::DURATION:
		vecSize = velVec.size();
		break;
	default: // or case: PITCH
		vecSize = pitchVec.size();
		break;
	}
	return vecSize;
}

void NoteBlock::addEndHorizontal( const std::vector<int> * pitchVec, const std::vector<double> * durVec, const std::vector<double> * velVec ) {
	// Find vector type to add completely
	int totalNotes = this -> addThisVector( * pitchVec, * durVec, * velVec );
	// Iterate through all vectors creating new note and adding to new notestack
	//	customtypes::Note newNote;
	for ( int i = 0; i < totalNotes; i++ ) {
		this -> newStack();
		//		newNote.pitch = pitchVec -> at( indexMod ( i, pitchVec -> size() ) );
		//		newNote.duration = durVec -> at( indexMod ( i, durVec -> size() ) );
		//		newNote.velocity = velVec -> at( indexMod ( i, velVec -> size() ) );
		//		newNote.rest = false;
		//		std::cout << pitchVec -> at( indexMod ( i, pitchVec -> size() ) ) <<" " << durVec -> at( indexMod ( i, durVec -> size() ) ) << " " <<velVec -> at( indexMod ( i, velVec -> size() ) ) << std::endl;
		noteStackList_.back() -> addNote( pitchVec -> at( indexMod ( i, pitchVec -> size() ) ), durVec -> at( indexMod ( i, durVec -> size() ) ), velVec -> at( indexMod ( i, velVec -> size() ) ) );
		//		noteStackList_.back() -> addNote( newNote );
	}
	this -> stackPosReset();
}

void NoteBlock::addEndVertical( const std::vector<int> * pitchVec, const std::vector<double> * durVec, const std::vector<double> * velVec ) {
	// Find vector type to add completely
	int totalNotes = this -> addThisVector( * pitchVec, * durVec, * velVec );
	// Iterate through all vectors creating new note and adding to new notestack
	//	customtypes::Note newNote;
	this -> newStack();
	for ( int i = 0; i < totalNotes; i++ ) {
		//		newNote.pitch = pitchVec -> at( indexMod ( i, pitchVec -> size() ) );
		//		newNote.duration = durVec -> at( indexMod ( i, durVec -> size() ) );
		//		newNote.velocity = velVec -> at( indexMod ( i, velVec -> size() ) );
		//		newNote.rest = false;
		noteStackList_.back() -> addNote( pitchVec -> at( indexMod ( i, pitchVec -> size() ) ), durVec -> at( indexMod ( i, durVec -> size() ) ), velVec -> at( indexMod ( i, velVec -> size() ) ) );
		//		noteStackList_.back() -> addNote( newNote );
	}
	this -> stackPosReset();
}

void NoteBlock::addOverEndHorizontal( const std::vector<int> * pitchVec, const std::vector<double> * durVec, const std::vector<double> * velVec ) {
	// Find vector type to add completely
	int totalNotes = this -> addThisVector( * pitchVec, * durVec, * velVec );
	int startIndex = noteStackList_.size() - totalNotes;
	if ( startIndex < 0 ) {
		startIndex = 0;
	}
	// Iterate through all vectors creating new note and adding to new notestack
	//	customtypes::Note newNote;
	for ( int i = startIndex; i < noteStackList_.size(); i++ ) {
		if ( i > noteStackList_.size() - 1) {
			this -> newStack();
		}
		//		newNote.pitch = pitchVec -> at( indexMod ( i, pitchVec -> size() ) );
		//		newNote.duration = durVec -> at( indexMod ( i, durVec -> size() ) );
		//		newNote.velocity = velVec -> at( indexMod ( i, velVec -> size() ) );
		//		newNote.rest = false;
		//		std::cout << pitchVec -> at( indexMod ( i, pitchVec -> size() ) ) <<" " << durVec -> at( indexMod ( i, durVec -> size() ) ) << " " <<velVec -> at( indexMod ( i, velVec -> size() ) ) << std::endl;

		noteStackList_.at( i ) -> addNote( pitchVec -> at( indexMod ( i, pitchVec -> size() ) ), durVec -> at( indexMod ( i, durVec -> size() ) ), velVec -> at( indexMod ( i, velVec -> size() ) ) );
		//		noteStackList_.at( i ) -> addNote( newNote );
	}
	this -> stackPosReset();
}

void NoteBlock::addOverEndVertical( const std::vector<int> * pitchVec, const std::vector<double> * durVec, const std::vector<double> * velVec ) {
	// Find vector type to add completely
	int totalNotes = this -> addThisVector( * pitchVec, * durVec, * velVec );

	if ( noteStackList_.empty() ) {
		this -> newStack();
	}

	// Iterate through all vectors creating new note and adding to new notestack
	//	customtypes::Note newNote;
	for ( int i = 0; i < totalNotes; i++ ) {
		//		newNote.pitch = pitchVec -> at( indexMod ( i, pitchVec -> size() ) );
		//		newNote.duration = durVec -> at( indexMod ( i, durVec -> size() ) );
		//		newNote.velocity = velVec -> at( indexMod ( i, velVec -> size() ) );
		//		newNote.rest = false;
		noteStackList_.back() -> addNote( pitchVec -> at( indexMod ( i, pitchVec -> size() ) ), durVec -> at( indexMod ( i, durVec -> size() ) ), velVec -> at( indexMod ( i, velVec -> size() ) ) );
		//		noteStackList_.back() -> addNote( newNote );
	}
	this -> stackPosReset();
}

//std::vector<customtypes::Note> NoteBlock::getNextNoteVector() {
//	std::vector<customtypes::Note> stackToReturn;
////	std::cout << noteStackList_.size() << std::endl;
//	if ( noteStackList_.size() != 0 ) {
//		++sPos_;
//		if ( sPos_ == noteStackList_.end() ) {
//			sPos_ = noteStackList_.begin();
//			++sPos_;
//		}
//		stackToReturn = ( *sPos_ ) -> getStack() ;
//	} else {
//		customtypes::Note emptyNote;
//		emptyNote.pitch = 0;
//		emptyNote.duration = 0.25;
//		emptyNote.velocity = 0.0;
//		emptyNote.rest=false;
//		stackToReturn.push_back( emptyNote );
////		stackToReturn.push_back( 0, 0.25, 0.0 );
//	}
//	return stackToReturn;
//}

const double NoteBlock::getLongestDur() {
	double lenToReturn = 0.0;
	if ( sPos_ != noteStackList_.begin() ) {
		lenToReturn = ( *sPos_ ) -> getLongestDur();
	}
	return lenToReturn;
}

void NoteBlock::stackPosReset() {
	sPos_ = noteStackList_.begin();
}

std::vector<notestack::NoteStack *> NoteBlock::getVector() {
	return noteStackList_;
}

int NoteBlock::getSize() {
	return noteStackList_.size();
}

void NoteBlock::clear() {
	noteStackList_.clear();
}

void NoteBlock::copy( noteblock::NoteBlock* & blockToCopy ) {
	noteStackList_.clear();
	noteStackList_ = blockToCopy -> getVector();
}

void NoteBlock::mergeHorizontal( noteblock::NoteBlock* & blockToMerge ) {
	std::cout << ( blockToMerge -> getSize() ) << std::endl;

	std::cout << ( noteStackList_.size() ) << std::endl;

	std::vector<notestack::NoteStack * > stackToMerge = blockToMerge -> getVector();
	noteStackList_.insert( noteStackList_.end(), stackToMerge.begin(), stackToMerge.end() );
}

void NoteBlock::mergeVertical( noteblock::NoteBlock* & blockToMerge ) {
	std::vector<notestack::NoteStack * > stackToMerge = blockToMerge -> getVector();

	for ( int i = 0; i < stackToMerge.size(); i++ ) {
		if ( noteStackList_.size() < i ) {
			noteStackList_.push_back( new notestack::NoteStack );
		}
		noteStackList_.at( i ) -> merge( stackToMerge.at( i ) );
	}

}
void NoteBlock::append( std::vector<notestack::NoteStack *> & stackToAppend ) {
	noteStackList_.insert( noteStackList_.end(), stackToAppend.begin(), stackToAppend.end() );
}

std::vector<int> NoteBlock::getLowestPitches() {
	std::vector<int> pitchesToReturn;
	std::vector<notestack::NoteStack * >::iterator pos;
	for( pos = noteStackList_.begin(); pos != noteStackList_.end(); ++pos ) {
		pitchesToReturn.push_back( ( ( * pos ) -> getPitch( ( * pos ) -> getLowestNoteIndex() ) ) );
	}
	return pitchesToReturn;
}


int NoteBlock::indexMod( int index, int size ) {
	size = ( int ) size;
	index = ( int ) index;
	int diff = 0;
	if ( index < 0 ) {
		diff = ( ( abs( static_cast<int> ( index ) ) ) / size ) + 1;
	}
	index = ( index + ( size * diff ) ) % size;
	return index;
}

void NoteBlock::dump() {
	for ( int i = 0; i < noteStackList_.size(); ++i  ) {
		std::cout << i << ": ";
		noteStackList_.at( i ) -> dump();
	}

}
NoteBlock::~NoteBlock() {
}



} // namespace noteblock
