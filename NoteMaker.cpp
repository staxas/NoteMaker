//============================================================================
// Name        : NoteMaker.cpp
// Author      : Edwin Rietmeijer
// Version     :
// Copyright   : This code is owned by Edwin Rietmeijer as of 2014
// Description : Musical material generator
//============================================================================

#include <iostream>
#include <algorithm>
#include <cmath>

#include "CommonFunctions.h"
#include "CustomTypes.h"
#include "FileInterpreter.h"
#include "Generator.h"
#include "GenAdmin.h"
#include "GeneratorMediation.h"
#include "NoteBlock.h"
#include "Serialism.h"
#include "DummyGen.h"
#include "DummyMut.h"
#include "ScriptCommandProcessor.h"
#include "OscReceiver.h"
#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/IpEndpointName.h"
#include "ip/UdpSocket.h"

#define ADDRESS "127.0.0.1"
#define PORT 7000
#define SENDERPORT 7001
#define OUTPUT_BUFFER_SIZE 1024

void nbDump() {
	std::cout << "Noteblock sizes of " << config::noteBlockStack.size() << " noteblocks (empty blocks are ommitted)"<<std::endl;
	for ( int i = 0; i < config::noteBlockStack.size(); ++i ) {
		if (  config::noteBlockStack.at( i ) -> getSize()  > 0 ) {
			std::cout << "- NoteBlock "<< i << ": " << config::noteBlockStack.at( i ) -> getSize() << std::endl;
			config::noteBlockStack.at( i ) -> dump();
		}

	}
}

int main( int argc, char* argv[] )
{
	( void ) argc; // suppress unused parameter warnings
	( void ) argv; // suppress unused parameter warnings

	// -- Init default pitch, dur, vel vectors --
	config::initDefaultPitch.push_back( 0 );
	config::initDefaultDur.push_back( 0.25 );
	config::initDefaultVel.push_back( 0.5 );
	config::streamNames.push_back( "default" );

	config::centerNote = -3;
	config::centerFreq = 440;

	config::isDiatonic = false;

	config::receivePort = 7000;
	config::sendPort = 7001;
	config::receiveAddress = "127.0.0.1";
	config::sendAddress = "127.0.0.1";

	genmediate::setVariablePointers( config::genMediatorVars, config::genMediatorVarPointers );
	genmediate::clearVariables( config::genMediatorVarPointers );

	oscreceiver::OscReceiver listener;

	// Interpretate script
	config::scriptFileName="firstscript.txt";
	std::cout << "Processing script..." << std::endl;

	processFile( config::scriptFileName, true );
	std::cout << "...finished processing script." << std::endl;

	endline();

	config::fileMutate = common::getFileMutateDate( config::scriptFileName );

	//	std::for_each( config::noteRelatives.begin(), config::noteRelatives.end(), toScreen() );

	if ( ! config::initScriptCommandStack.empty() ) {
		std::cout << "Running init script commands..." << std::endl;
		scprocessor::initStack( config::initScriptCommandStack, 1 );
	}

	if ( ! config::playScriptCommandStack.empty() ) {

		// Create playStack script command processor
		config::playSCStackProcessor = new scprocessor::ScriptCommandProcessor( config::playScriptCommandStack );

		// Set dump of playScript to true or false ( 1/0 ) as stated in config::
		config::playSCStackProcessor -> setDump( config::dumpPlayCommandStack );

		std::cout << "Pre-running play script commands..." << std::endl;
		config::playSCStackProcessor -> prerunStack();
	}

	endline();

	std::cout << "Dumping currently used noteblocks..." << std::endl;

	nbDump();

	endline();

	UdpListeningReceiveSocket s(
			IpEndpointName( IpEndpointName::ANY_ADDRESS, RECEIVEPORT ),
			&listener );

	std::cout << "Press ctrl-c to end" << std::endl;
	s.RunUntilSigInt();

	return 0;
}

