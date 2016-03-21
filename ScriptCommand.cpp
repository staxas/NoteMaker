/*
 * ScriptCommand.cpp
 *
 *  Created on: Mar 18, 2014
 *      Author: edwinrietmeijer
 */

#include "ScriptCommand.h"

namespace scriptcommand {

ScriptCommand::ScriptCommand() : isPlaying_( false ), noteBlockPointer_ ( nullptr )
, nbIndex_( 0 ), nbSize_( 0 )
{
	transmitter_ = osctransmitter::OscTransmitter::Instance();
}

ScriptCommand::ScriptCommand( ScriptCommandVars scv ) : scrCommVars_( scv ), isPlaying_( false ), noteBlockPointer_ ( nullptr )
, nbIndex_( 0 ), nbSize_( 0 )
{
	transmitter_ = osctransmitter::OscTransmitter::Instance();
}

void ScriptCommand::setMediatorPointers( genmediate::GeneratorMediatorVariables & genMedVars, genmediate::GeneratorMediatorVariables & mutMedVars) {
	genmediate::setVariablePointers( genMedVars, generatorMedVarPointers_ );
	genmediate::setVariablePointers( mutMedVars, mutatorMedVarPointers_ );

//	genMedVarPointers_.generatorReturnTypePtr = generatorReturnType_;
}

void ScriptCommand::setConfigPointers( int & cntrNote, double & cntrFreq, std::vector<double> & nteRels ) {
	genmediate::setConfigPointers( generatorMedVarPointers_, cntrNote, cntrFreq, nteRels);
}

void ScriptCommand::setTransmitter( osctransmitter::OscTransmitter * aTransmitter ) {
	transmitter_ = aTransmitter;
}

ScriptCommandReturn ScriptCommand::run() {

	std::vector<int> noteVec;
	genStructReturned_.generatorReturnType = gentypes::EMPTY;
	genStructReturned_.generatorReturnOrientation = gentypes::HORIZONTAL;

	dataToReturn_.scriptCommandVars = &scrCommVars_;
	//	dataToReturn_.noteStack = nullptr;
	dataToReturn_.commandDur = 0.0;

	if ( scrCommVars_.generatorFunction == customtypes::NO_GEN_FUNC ) {

		switch( scrCommVars_.noteBlockFunction ) {
		case customtypes::CLEAR:
			scrCommVars_.noteBlock -> clear();
			break;

		case customtypes::MERGE_HORIZONTAL:
			scrCommVars_.noteBlock -> mergeHorizontal( scrCommVars_.anotherNoteBlock );
			break;

		case customtypes::MERGE_VERTICAL:
			scrCommVars_.noteBlock -> mergeVertical( scrCommVars_.anotherNoteBlock );
			break;

		case customtypes::PLAY:
			// PLAY ROUTINE

			//			std::cout << "About to play SC" << std::endl;

			// Check if noteBlock pointer is non-dummy and non-empty
			if ( scrCommVars_.noteBlock != nullptr && scrCommVars_.noteBlock -> getSize() > 0 ) {

				if ( ! isPlaying_ ) {
					//					toConsole( "Wasn't playing yet");
					// Init noteBlock variables
					noteBlockPointer_ = scrCommVars_.noteBlock;
					nbPosBegin_ = noteBlockPointer_ -> begin();
					nbPosEnd_ = noteBlockPointer_ -> end();
					nbPos_ = nbPosBegin_;
					isPlaying_ = true;

					// Console output variable reset
					nbSize_ = noteBlockPointer_ -> getSize();
					nbIndex_ = 0;
				}
				// Ouput noteBlock size and index to console
				std::cout << "noteBlock size: " << nbSize_ << " noteBlock index: " << nbIndex_ << std::endl;

				if ( nbPos_ != nbPosEnd_ ) {

					std::string thisStreamName = '/' + * ( scrCommVars_.streamName );
					toConsole( thisStreamName );
//					std::vector<customtypes::Note>::iterator nPos;
//					std::cout << "noteStack pitchVec size: " << ( *nbPos_ ) -> getPitchVecSize() << std::endl;
//					std::cout << "noteStack durVec size: " << ( *nbPos_ ) -> getVelVecSize() << std::endl;
//					std::cout << "noteStack velVec size: " << ( *nbPos_ ) -> getDurVecSize() << std::endl;
//					std::cout << ( ( *nbPos_ ) -> getPitch( 0 ) ) << " ";
//				 	int pitchVecSize = ( *nbPos_ ) -> getPitchVecSize();
					( *nbPos_ )  -> dump();

					for ( int i = 0; i < ( *nbPos_ ) -> getPitchVecSize(); i++ ) {
//					for ( nPos = ( *nbPos_ ) -> begin(); nPos != ( *nbPos_ ) -> end(); ++nPos ) {
//						std::cout << ( *nPos ).pitch << "|" << ( *nPos ).duration << "|" << ( *nPos ).velocity << " ";
//						std::cout << ( *nbPos_ ) -> getPitch( i ) << "|" << ( *nbPos_ ) -> getDuration( i ) << "|" << ( *nbPos_ ) -> getVelocity( i ) << " ";
						transmitter_ -> transmit( thisStreamName, musical::convertNoteNumToHertz( ( *nbPos_ ) -> getPitch( i ), * generatorMedVarPointers_.noteRelativesPtr, * generatorMedVarPointers_.centerFreqPtr, * generatorMedVarPointers_.centerNotePtr ), ( *nbPos_ ) -> getDuration( i ), ( *nbPos_ ) -> getVelocity( i ) );
//						transmitter_ -> transmit( thisStreamName, musical::convertNoteNumToHertz( ( *nPos ).pitch, * genMedVarPointers_.noteRelativesPtr, * genMedVarPointers_.centerFreqPtr, * genMedVarPointers_.centerNotePtr ), ( *nPos ).duration, ( *nPos ).velocity );

					}
					dataToReturn_.commandDur = ( * nbPos_ ) -> getLongestDur();
					++nbPos_;
					++nbIndex_;
				}

				if ( nbPos_ == nbPosEnd_ ) {
					isPlaying_ = false;
				}
			}
			break;
		}
		// End of non-generator function interpretation

	} else {

		// Generator function interpretation


		bool isVarPtrsSet = false;

		int genReturnCode = 0;

		switch( scrCommVars_.generatorFunction ) {

		case customtypes::INIT:
			scrCommVars_.generator -> init();
			break;

		case customtypes::SET:
			scrCommVars_.generator -> set( scrCommVars_.variableSet );
			break;

		case customtypes::GET:
			genmediate::clearVariables( generatorMedVarPointers_ );
			genReturnCode = scrCommVars_.generator -> get();
			this -> setVarPointersToReturnType();
			this -> processGeneratorNotes();
			break;

		case customtypes::GET_INT:
			genmediate::clearVariables( generatorMedVarPointers_ );
			genReturnCode = scrCommVars_.generator -> get( scrCommVars_.firstGenFuncInt );
			this -> setVarPointersToReturnType();
			this -> processGeneratorNotes();
			break;

		case customtypes::NEXT:
			genmediate::clearVariables( generatorMedVarPointers_ );
			genReturnCode = scrCommVars_.generator -> next();
			this -> setVarPointersToReturnType();
			this -> processGeneratorNotes();
			break;

		case customtypes::NEXT_INT:
			genmediate::clearVariables( generatorMedVarPointers_ );
			isVarPtrsSet = false;
			for ( int i = 0; i < scrCommVars_.firstGenFuncInt; ++i ) {
				genmediate::clearVariables( generatorMedVarPointers_ );
				genReturnCode = scrCommVars_.generator -> next();

				if ( ! isVarPtrsSet ) {
					this -> setVarPointersToReturnType();
					isVarPtrsSet = true;
				}
				this -> processGeneratorNotes( i );
			}
			break;

		case customtypes::PROCESS:
			genmediate::clearVariables( generatorMedVarPointers_ );
			genmediate::clearVariables( mutatorMedVarPointers_ );
			* mutatorMedVarPointers_.pitches = scrCommVars_.anotherNoteBlock -> getLowestPitches();
//			for( int i = 0; i < mutatorMedVarPointers_.pitches -> size(); ++i ) {
//				std::cout << mutatorMedVarPointers_.pitches ->at( i ) << " ";
//			}
//			std::cout << std::endl;
			genReturnCode = scrCommVars_.generator -> process();

			this -> setVarPointersToReturnType();
//			* generatorMedVarPointers_.generatorReturnOrientationPtr = gentypes::HORIZONTAL;

			this -> processGeneratorNotes();
			break;

		case customtypes::NO_GEN_FUNC:
			break;
		}

		isPlaying_ = false;
		dataToReturn_.commandDur = 0.0;

	} 		// End of generator function interpretation

	dataToReturn_.isPlaying = &isPlaying_;
	return dataToReturn_;
}

void ScriptCommand::setVarPointersToReturnType() {
//	if ( genStructReturned_.generatorReturnType == generator::PITCH ) {
	if ( ( * generatorMedVarPointers_.generatorReturnTypePtr ) == gentypes::PITCH ) {
		scrCommVars_.pitchSet = generatorMedVarPointers_.pitches;
	}
	if ( ( * generatorMedVarPointers_.generatorReturnTypePtr ) == gentypes::DURATION ) {
		scrCommVars_.velocitySet = generatorMedVarPointers_.durations;
	}
	if ( ( * generatorMedVarPointers_.generatorReturnTypePtr ) == gentypes::VELOCITY ) {
		scrCommVars_.velocitySet = generatorMedVarPointers_.velocities;
	}
	if ( ( * generatorMedVarPointers_.generatorReturnTypePtr ) == gentypes::NOTE ) {
		scrCommVars_.pitchSet = generatorMedVarPointers_.pitches;
		scrCommVars_.velocitySet = generatorMedVarPointers_.velocities;
		scrCommVars_.durationSet = generatorMedVarPointers_.durations;
	}
}

void ScriptCommand::processGeneratorNotes( int nextIndex ) {

	if ( ( * generatorMedVarPointers_.generatorReturnTypePtr )  != gentypes::EMPTY ) {
		// Vectors and their pointers are set up that allow durations and velocities
		// to be 'loop' added to note blocks horizontally,
		// while pitches are added to note blocks vertically
		std::vector<int> indexedPitchSet;
		std::vector<double> indexedDurSet;
		std::vector<double> indexedVelSet;
		indexedPitchSet.push_back( scrCommVars_.pitchSet -> at( common::indexMod( nextIndex, ( scrCommVars_.pitchSet ) -> size() ) ) );
		indexedDurSet.push_back( scrCommVars_.durationSet -> at( common::indexMod( nextIndex, ( scrCommVars_.durationSet ) -> size() ) ) );
		indexedVelSet.push_back( scrCommVars_.velocitySet -> at( common::indexMod( nextIndex, ( scrCommVars_.velocitySet ) -> size() ) ) );
		std::vector<int> * indexedPitchSetPtr = &indexedPitchSet;
		std::vector<double> * indexedDurSetPtr = &indexedDurSet;
		std::vector<double> * indexedVelSetPtr = &indexedVelSet;

		if ( ( * generatorMedVarPointers_.generatorReturnOrientationPtr )  == gentypes::HORIZONTAL ) {
			if ( nextIndex == 0 ) {
			switch( scrCommVars_.noteBlockFunction ) {
			case customtypes::ADD_END:
				scrCommVars_.noteBlock -> addEndHorizontal( scrCommVars_.pitchSet, scrCommVars_.durationSet, scrCommVars_.velocitySet );
				break;
			case customtypes::ADD_OVER_END:
				scrCommVars_.noteBlock -> addOverEndHorizontal( scrCommVars_.pitchSet, scrCommVars_.durationSet, scrCommVars_.velocitySet );
				break;
			default:
				break;
			}
			} else {
				switch( scrCommVars_.noteBlockFunction ) {
				case customtypes::ADD_END:
					scrCommVars_.noteBlock -> addEndHorizontal( indexedPitchSetPtr, indexedDurSetPtr, indexedVelSetPtr );
					break;
				case customtypes::ADD_OVER_END:
					scrCommVars_.noteBlock -> addOverEndHorizontal( indexedPitchSetPtr, indexedDurSetPtr, indexedVelSetPtr );
					break;
				default:
					break;
				}

			}
		}

		if ( ( * generatorMedVarPointers_.generatorReturnOrientationPtr )  == gentypes::VERTICAL ) {

			switch( scrCommVars_.noteBlockFunction ) {
			case customtypes::ADD_END:
				scrCommVars_.noteBlock -> addEndVertical( scrCommVars_.pitchSet, indexedDurSetPtr, indexedVelSetPtr );
				break;
			case customtypes::ADD_OVER_END:
				scrCommVars_.noteBlock -> addOverEndVertical( scrCommVars_.pitchSet, indexedDurSetPtr, indexedVelSetPtr );
				break;

			default:
				break;
			}
		}
	}
}

void ScriptCommand::processGeneratorNotes() {
	processGeneratorNotes( 0 );
}

void ScriptCommand::dump() {
	std::cout << "nb*:" << scrCommVars_.noteBlock << " ";
	std::cout << "gen*:" << scrCommVars_.generator << " ";
	std::cout << customtypes::nbFuncScriptNames[ scrCommVars_.noteBlockFunction ] << " ";
	std::cout << customtypes::genFuncScriptNames[ scrCommVars_.generatorFunction ] << " ";
	std::cout << "str*:" << scrCommVars_.streamName << " ";
	std::cout << "ptc*:" << scrCommVars_.pitchSet << " ";
	std::cout << "dur*:" << scrCommVars_.durationSet << " ";
	std::cout << "vel*:" << scrCommVars_.velocitySet << " ";
	std::cout << std::endl;
}

bool ScriptCommand::isPlay() {
	return scrCommVars_.noteBlockFunction == customtypes::PLAY;
}

ScriptCommand::~ScriptCommand() {
}

} /* namespace scriptcommand */
