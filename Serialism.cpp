/*
 * Serialism.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: edwinrietmeijer
 */

#include "Serialism.h"

namespace serialism {

const int Serialism::rev[ 4 ] = { 0, 1, 0, 1 };
const int Serialism::inv[ 4 ] = { 0, 0, 1, 1 };

std::random_device rd;
std::RANDOM_DEV my_random_device( rd() );

Serialism::Serialism() : setIndexesSize_ ( scaleSize_ ) {
	// MANDATORY FOR ALL GENERATOR CLASSES:
	scriptName_ = "serialism";
	genId_ = typeid( this ).name();
	generatorReturnType_ = gentypes::PITCH;
	generatorReturnOrientation_ = gentypes::HORIZONTAL;
}

void Serialism::init() {
	noteSetIndexes_.clear();
	setIndexesSize_ = scaleSize_;
	for ( int i = 0; i < scaleSize_; i++ ) {
		initNoteSet_.push_back( i );
		noteSetIndexes_.push_back( i );
	}
	this -> shuffleSetIndexes( );
	this -> generateSet();
}

void Serialism::shuffleSetIndexes() {
	shuffle( noteSetIndexes_.begin(), noteSetIndexes_.end(), my_random_device );
}

void Serialism::generateSet() {
	std::vector<int>::iterator pos;
	int currIndex;
	int currNote;
	int invIndex;
	int intIterator = 0;
	int indexDifference;
	for ( int i = 0; i < 4; i ++ ) {
		intIterator = 0; 	// position iterator in the form of an int
		for ( int j = 0; j < noteSetIndexes_.size(); j++ ) {

			// find the initial ARRAY INDEX of the current note to be calculated
			if ( rev[ i ] == 0  && inv[ i ] == 0 ) {
				currIndex = noteSetIndexes_.at( j );
			}
			if ( rev[ i ] == 1 && inv[ i ] == 0 ) {
				currIndex = noteSetIndexes_.at( noteSetIndexes_.size() - j - 1 );
			}
			if ( inv[ i ] == 0 ) {
				currNote = initNoteSet_.at( currIndex );
			}
			if ( rev[ i ] == 0 && inv[ i ] == 1 ) {
				if ( j == 0 ) {
					invIndex = initNoteSet_.at( noteSetIndexes_.at( j ) );
				}
				else {

					indexDifference = noteSetIndexes_.at( j ) - noteSetIndexes_.at( j - 1) ;
					invIndex =  invIndex - ( indexDifference );
					currNote = initNoteSet_.at( indexMod_( invIndex, initNoteSet_.size()) );
				}
			}
			if ( rev[ i ] == 1 && inv[ i ] == 1 ) {
				currNote = serialSet_.at( ( noteSetIndexes_.size() * 3 ) -  j - 1 );
			}
			serialSet_.push_back( currNote );
		}
	}
}

int Serialism::get( int blockSize ) {
	int thisBlockSize = blockSize;
	if ( blockSize > serialSet_.size() -1 ) {
		thisBlockSize = serialSet_.size() -1;
	}
	std::vector<int> aSet;
	std::uniform_int_distribution<int> setToGrab( 0, 3 );
	std::uniform_int_distribution<int> relativeStartPlace( 0, ( scaleSize_ / thisBlockSize ) - 1 );
	int startPlace = ( setToGrab( my_random_device ) * scaleSize_ ) + ( relativeStartPlace( my_random_device ) * thisBlockSize );
//	* genMedVarPointers_.pitches = std::vector<int> ( serialSet.begin() + startPlace, serialSet.begin() + startPlace + thisBlockSize);
		std::vector<int> aPitchSet =  std::vector<int> ( serialSet_.begin() + startPlace, serialSet_.begin() + startPlace + thisBlockSize );
		addPitch( aPitchSet );
//	if ( ! genMedVarPointers_.pitches -> empty() ) {
//		genReturnStruct_.generatorReturnType = gentypes::PITCH;
//	} else {
//		genReturnStruct_.generatorReturnType =  gentypes::EMPTY;
//	}
	return 1;
}

void Serialism::toScreen() {
	std::vector<int>::iterator pos;
	int i = 0;
	for ( pos = serialSet_.begin(); pos != serialSet_.end(); ++pos ) {
		std::cout << *pos << " ";
		if ( i == initNoteSet_.size() - 1 ) {
			std::cout << " |  ";
			i = - 1;
		}
		i++;
	}
	std::cout << std::endl;
}

Serialism::~Serialism() {
}

} // namespace serialism
