/*
 * ScriptCommandProcessor.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: edwinrietmeijer
 */

#include "ScriptCommandProcessor.h"

namespace scprocessor {

ScriptCommandProcessor::ScriptCommandProcessor() : aScriptStack_( nullptr ), isDump_( false ), dummyPlayScriptCommand_( new scriptcommand::ScriptCommand( this -> setDummyPlaySCPointer() ) ) {
	this -> resetStack();

}

ScriptCommandProcessor::ScriptCommandProcessor( std::vector<std::vector<scriptcommand::ScriptCommand *> > & aScrCommStack ) : 	aScriptStack_( & aScrCommStack ), isDump_( false ), dummyPlayScriptCommand_( new scriptcommand::ScriptCommand( this -> setDummyPlaySCPointer() ) ) {
	this -> resetStack();
}

void ScriptCommandProcessor::resetStack() {
	scrStackLoopSize_.clear();
	scrStackLoopPos_.clear();
	std::vector<std::vector<scriptcommand::ScriptCommand *> >:: iterator pos;
	for( pos = aScriptStack_ -> begin(); pos != aScriptStack_ -> end(); ++pos ) {
		scrStackLoopSize_.push_back( pos -> size() );
		scrStackLoopPos_.push_back ( 0 );
		playStacks_.push_back( nullptr );
		waitDur_.push_back( 0.0 );
	}
}

void ScriptCommandProcessor::setStack( std::vector<std::vector<scriptcommand::ScriptCommand *> > & aScrCommStack ) {
	aScriptStack_ = & aScrCommStack;
	this -> resetStack();
}

void ScriptCommandProcessor::dumpStack() {
	for ( int scrStackPos = 0; scrStackPos < aScriptStack_ -> size(); ++scrStackPos ) {
		std::cout << "Script Stack Loop " << scrStackPos + 1<< ": " << std::endl;
		for ( int scrLoopPos = 0; scrLoopPos < ( aScriptStack_ -> at( scrStackPos ) ).size(); ++scrLoopPos ) {
			( aScriptStack_ -> at( scrStackPos ) ).at( scrLoopPos ) -> dump();
		}
	}
}

void ScriptCommandProcessor::prerunStack() {

	bool isCurrScrCommPlay = false;

	for ( int scrStackPos = 0; scrStackPos < aScriptStack_ -> size(); ++scrStackPos ) {

				std::cout << "starting pre-run of loop " << scrStackPos + 1 << " at index " << scrStackLoopPos_.at( scrStackPos ) << " of loop size " << ( aScriptStack_ -> at( scrStackPos ) ).size()<< std::endl;

		// Check to see if the script command that is currently pointed to in this loop is playable
		// ( and is thus being played )
		isCurrScrCommPlay = ( aScriptStack_ -> at( scrStackPos ) ).at( scrStackLoopPos_.at( scrStackPos ) ) -> isPlay();

//				std::cout << "SC playable: " << 	isCurrScrCommPlay << std::endl;
		// If current SC is playable, and the loops' playSC pointer is empty, point it to the current script command
		if ( isCurrScrCommPlay && playStacks_.at( scrStackPos ) == nullptr ) {
			playStacks_.at( scrStackPos ) = ( aScriptStack_ -> at( scrStackPos ) ).at( scrStackLoopPos_.at( scrStackPos ) );
//						std::cout  << " added index " << scrStackLoopPos_.at( scrStackPos ) << " to playloop pointer of loop " << scrStackPos + 1 << std::endl;

			// This script command has been processed/pointed to, so increment the loop index
			++scrStackLoopPos_.at( scrStackPos );
			// If reached the end of the loops' script command vector, set pointer to zero
			if ( scrStackLoopPos_.at( scrStackPos ) >= ( aScriptStack_ -> at( scrStackPos ) ).size() ) {
				scrStackLoopPos_.at( scrStackPos ) = 0;
			}
		}

		// If current SC is NOT playable, run it ( 'pre-run' )
		if ( ! isCurrScrCommPlay ) {
			int loopRanNo = 0;
			while ( ! isCurrScrCommPlay ) {


				// Dump to console if isDump is enabled( true )
				if ( isDump_  ) {
					( aScriptStack_ -> at( scrStackPos ) ).at( scrStackLoopPos_.at( scrStackPos ) ) -> dump();
				}

				// Run currently pointed-to script command, and increment pointer
				//				toConsole( "Running pre-run type ScriptCommand");
				//				std::cout << " loop index " << ( scrStackLoopPos_.at( scrStackPos ) ) << " being run" << std::endl;
				( aScriptStack_ -> at( scrStackPos ) ).at( scrStackLoopPos_.at( scrStackPos ) ) -> run();

				// Increment loop index
				++scrStackLoopPos_.at( scrStackPos );
				// If reached the end of the loops' script command vector, set pointer to zero
				if ( scrStackLoopPos_.at( scrStackPos ) >= ( aScriptStack_ -> at( scrStackPos ) ).size() ) {
					scrStackLoopPos_.at( scrStackPos ) = 0;
				}

				// Check if the NEXT SC is playable. If so, the 'while' loop will end
				isCurrScrCommPlay = ( aScriptStack_ -> at( scrStackPos ) ).at( scrStackLoopPos_.at( scrStackPos) ) -> isPlay();

				// Check if the loop has been run as many times as there are commands in the stack,
				// WITHOUT finding a playable script command (see previous line of code)
				// This would indicate no  play script commands in the loop, resulting in an infinite pre-run loop
				// If this is the case, point the loops' playStacks_ pointer to the dummy play script command object
				++loopRanNo;
				//				std::cout << "loopRanNo: " << loopRanNo << std::endl;
				if ( loopRanNo >= ( aScriptStack_ -> at( scrStackPos ) ).size() ) {
					playStacks_.at( scrStackPos ) = dummyPlayScriptCommand_;
					isCurrScrCommPlay = true;
				}
			} // end of 		while ( ! isCurrScrCommPlay )
		} // end of 		if ( ! isCurrScrCommPlay )
		if ( isCurrScrCommPlay && playStacks_.at( scrStackPos ) == nullptr ) {
			playStacks_.at( scrStackPos ) = ( aScriptStack_ -> at( scrStackPos ) ).at( scrStackLoopPos_.at( scrStackPos ) );
			//			std::cout  << " added index " << scrStackLoopPos_.at( scrStackPos ) << " to playloop pointer of loop " << scrStackPos + 1 << " AFTER pre-run stage" << std::endl;
		}

	}

	//	for ( int scrStackPos = 0; scrStackPos < aScriptStack_ -> size(); ++scrStackPos ) {
	//
	//		bool isCurrScrCommPlay = false;
	//
	//		int loopRanNo = 0;
	//
	//		isCurrScrCommPlay = ( aScriptStack_ -> at( scrStackPos ) ).at( scrStackLoopPos_.at( scrStackPos) ) -> isPlay();
	//
	//		while ( ! isCurrScrCommPlay ) {
	//
	//			// If dump is enabled ( isDump_ == true ), dump to console
	//			if ( isDump_  ) {
	//				( aScriptStack_ -> at( scrStackPos ) ).at( scrStackLoopPos_.at( scrStackPos) ) -> dump();
	//			}
	//
	//			( aScriptStack_ -> at( scrStackPos ) ).at( scrStackLoopPos_.at( scrStackPos) ) -> run();
	//
	//			++scrStackLoopPos_.at( scrStackPos);
	//
	//			isCurrScrCommPlay = ( aScriptStack_ -> at( scrStackPos ) ).at( scrStackLoopPos_.at( scrStackPos) ) -> isPlay();
	//
	//			// Check if the loop has been run as many times as there are commands in the stack,
	//			// WITHOUT finding a playable script command (see previous line of code)
	//			// This would indicate no  play script commands in the loop, resulting in an infinite pre-run loop
	//			// If this is the case, point the loops' playStacks_ pointer to the dummy play script command object
	//			++loopRanNo;
	//			if ( loopRanNo >= ( aScriptStack_ -> at( scrStackPos ) ).size() ) {
	//				std::cout << "Linked to dummy play script command" << std::endl;
	//				playStacks_.at( scrStackPos ) = dummyPlayScriptCommand_;
	//				isCurrScrCommPlay = true;
	//			}
	//		}
	//
	//		if ( isCurrScrCommPlay ) {
	//			std::cout << "Setting playStacks_ pointer" << std::endl;
	//			playStacks_.at( scrStackPos ) = ( aScriptStack_ -> at( scrStackPos ) ).at( scrStackLoopPos_.at( scrStackPos) );
	//		}
	//	}
}

void ScriptCommandProcessor::playStack( double & timingDiff ) {
	int scrStackPos = 0;
	int scriptStackSize = aScriptStack_ -> size();

	while ( scrStackPos < scriptStackSize ) {

		if ( waitDur_.at( scrStackPos ) <= 0.0 ) {

			waitDur_.at( scrStackPos ) = 0.0;

			if ( playStacks_.at( scrStackPos ) != nullptr ) {

				if ( isDump_  ) {
					playStacks_.at( scrStackPos ) -> dump();
				}
				ScriptCommandReturn returnedScriptData;
				returnedScriptData = playStacks_.at( scrStackPos ) -> run();

				waitDur_.at( scrStackPos ) = returnedScriptData.commandDur;

				if ( ! * returnedScriptData.isPlaying ) {
					playStacks_.at( scrStackPos ) = nullptr;
				}
			}
		}

		waitDur_.at( scrStackPos ) -= timingDiff;
		++scrStackPos;
		scriptStackSize = aScriptStack_ -> size();

	}

	this -> prerunStack();
}


void ScriptCommandProcessor::setDump( bool newIsDump ) {
	isDump_ =newIsDump;
}

ScriptCommandVars ScriptCommandProcessor::setDummyPlaySCPointer() {

	ScriptCommandVars dummyPlayScriptCommVars;

	dummyPlayScriptCommVars.noteBlock = nullptr;
	dummyPlayScriptCommVars.generator  = nullptr;
	dummyPlayScriptCommVars.noteBlockFunction = customtypes::PLAY;
	dummyPlayScriptCommVars.generatorFunction = customtypes::NO_GEN_FUNC;

	return dummyPlayScriptCommVars;
}

void ScriptCommandProcessor::setScriptFileName( std::string scrFileName ) {
	scriptFileName_ = scrFileName;
}

ScriptCommandProcessor::~ScriptCommandProcessor() {
}

void initStack( std::vector<scriptcommand::ScriptCommand *> & stackToInit, bool isDump ) {
	std::vector<scriptcommand::ScriptCommand *>:: iterator initPos;
	for ( initPos = stackToInit.begin(); initPos != stackToInit.end(); ++initPos ) {
		bool checkedForPlay = false;
		checkedForPlay = ( * initPos ) -> isPlay();
		if ( ! checkedForPlay ) {
			if ( isDump ) {
				( *initPos ) -> dump();
			}
			( * initPos ) -> run();
		}
	}
}

void initStack( std::vector<scriptcommand::ScriptCommand *> & stackToInit) {
	initStack( stackToInit, 0 );
}

} /* namespace scprocessor */
