/*
 * Generator.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: edwinrietmeijer
 */

#include "Generator.h"

namespace generator {

Generator::Generator() : scriptName_ ( "" ), isDia_( false ), scaleSize_( 12 ), chordNo_( 0 ) {
	genId_ = typeid( this ).name();
	generatorReturnType_ = gentypes::EMPTY;
	generatorReturnOrientation_ = gentypes::HORIZONTAL;
}

std::string Generator::getScriptName() {
	return scriptName_;
}

std::string Generator::getGenId() {
	return genId_;
}

void Generator::setMediatorPointers( genmediate::GeneratorMediatorVariables & genMedVars, genmediate::GeneratorMediatorVariables & mutMedVars ) {
	genmediate::setVariablePointers( genMedVars, genMedVarPointers_ );
	genmediate::setVariablePointers( mutMedVars, mutatorMedVarPointers_ );
}

void Generator::setScaleSize( const int & newScaleSize ) {
	scaleSize_ = newScaleSize;
}

void Generator::setDia( bool isDia ) {
	if( isDia && scaleSize_ == 12 ) {
		scaleSize_ = 8;
		isDia_ = isDia;
	}
}

int Generator::calcNote( int & chromNote ) {
	if( isDia_ ) {
	int absChromNote = abs( chromNote );
	int octave;
	int octBias;
	int isNeg = 0;
	if ( chromNote < 0 ) {
		absChromNote = 7 - ( absChromNote % 7 );
		if ( chromToDia[ absChromNote % 7 ] != 0 ) {
			isNeg = -1;
			octBias = 1;
		} else {
			octBias = 0;
		}
	}
	octave = chromNote / 7 + isNeg;
	return chromToDia[ absChromNote % 7 ] + ( octave * 12 ) + chordNo_;
	} else {
		return chromNote;
	}
}

int Generator::calcNoteOct( int & chromNote ) {
	if( isDia_ ) {

	int absChromNote = abs( chromNote );
	int octave;
	int octBias;
	int isNeg = 0;
	if ( chromNote < 0 ) {
		absChromNote = 7 - ( absChromNote % 7 );
		if ( chromToDia[ absChromNote % 7 ] != 0 ) {
			isNeg = -1;
			octBias = 1;
		} else {
			octBias = 0;
		}
	}
	octave = chromNote / 7 + isNeg;
	return octave * 12 + chordNo_ ;
	} else {
		int absChromNote = abs( chromNote );
		int octave;
		int octBias;
		int isNeg = 0;
		if ( chromNote < 0 ) {
			absChromNote = 12 - ( absChromNote % 12 );
			if ( absChromNote % 7 != 0 ) {
				isNeg = -1;
				octBias = 1;
			} else {
				octBias = 0;
			}
		}
		octave = chromNote / 12 + isNeg;
		return octave * 12;
	}
}

void Generator::addPitch( int newPitch ) {
	genMedVarPointers_.pitches -> push_back( calcNote( newPitch ) );
	* genMedVarPointers_.generatorReturnTypePtr = generatorReturnType_;
	* genMedVarPointers_.generatorReturnOrientationPtr = generatorReturnOrientation_;
}

void Generator::addPitch( std::vector<int> & pitchesToSend ) {
	std::vector<int>::iterator pos;
	for( pos = pitchesToSend.begin(); pos != pitchesToSend.end(); ++pos ) {
		genMedVarPointers_.pitches -> push_back( calcNote( *pos ) );
	}
	* genMedVarPointers_.generatorReturnTypePtr = generatorReturnType_;
	* genMedVarPointers_.generatorReturnOrientationPtr = generatorReturnOrientation_;
}

std::vector<int> Generator::getPitches() {
	return * mutatorMedVarPointers_.pitches;
}

void Generator::setChordNo( int & newChordNo) {
	chordNo_ = newChordNo;
}

void Generator::init() {
//		std::cout << "init() function not implemented for this generator" << std::endl;
}

void Generator::reset() {
	std::cout << "reset() function not implemented for this generator" << std::endl;
}

void Generator::set( std::vector<double> doubleVec) {
	std::cout << "set() function not implemented for this generator" << std::endl;
}

int Generator::get() {
	std::cout << "get() function not implemented for this generator, maybe you meant to call get( int )?" << std::endl;
	clearVariables( genMedVarPointers_);
	generatorReturnType_ = gentypes::EMPTY;
	generatorReturnOrientation_= gentypes::HORIZONTAL;
	return 0;
}

int Generator::get(  int blockToReturn ) {
	std::cout << "get( int ) function not implemented for this generator, maybe you meant to call get()?" << std::endl;
	clearVariables( genMedVarPointers_);
	generatorReturnType_ = gentypes::EMPTY;
	generatorReturnOrientation_= gentypes::HORIZONTAL;
	return 0;
}

int Generator::next() {
	std::cout << "next() function not implemented for this generator, maybe you meant to call next( int )?" << std::endl;
	clearVariables( genMedVarPointers_);
	generatorReturnType_ = gentypes::EMPTY;
	generatorReturnOrientation_= gentypes::HORIZONTAL;
	return 0;
}

int Generator::process() {
	std::cout << "process() function not implemented for this generator" << std::endl;
	clearVariables( genMedVarPointers_);
	generatorReturnType_ = gentypes::EMPTY;
	generatorReturnOrientation_= gentypes::HORIZONTAL;
	return 0;
}

//std::vector<int> Generator::getLowestPitches( noteblock::NoteBlock * nbToStrip ) {
//	std::vector<int> strippedPitches;
//	std::vector<notestack::NoteStack *>::iterator pos;
//	for( pos = nbToStrip -> begin(); pos != nbToStrip -> end(); ++pos ) {
//		strippedPitches.push_back( ( pos -> getStack() ).at( 0 ) );
//	}
//return strippedPitches;
//}

int Generator::indexMod_( int index, int size ) {
	size = ( int ) size;
	index = ( int ) index;
	int diff = 0;
	if ( index < 0 ) {
		diff = ( ( abs( static_cast<int> ( index ) ) ) / size ) + 1;
	}
	index = ( index + ( size * diff ) ) % size;
	return index;
}

Generator::~Generator() {
}

} // namespace generator
