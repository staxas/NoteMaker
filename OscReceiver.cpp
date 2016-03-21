/*
 * OscReceiver.cpp
 *
 *  Created on: Mar 6, 2014
 *      Author: edwinrietmeijer
 */

#include "OscReceiver.h"

namespace oscreceiver {
void OscReceiver::ProcessMessage( const osc::ReceivedMessage& m,
		const IpEndpointName& remoteEndpoint )
{

	try{
		clock_t Start = clock();
//				transmitter = osctransmitter::OscTransmitter::Instance();

//		bool nextIsNotPlay = true;

		if( strcmp( m.AddressPattern(), "/timing" ) == 0 ){

			// Receving OSC message
			osc::ReceivedMessageArgumentStream args = m.ArgumentStream();
			osc::int32 a1;
			float a2;
			args >> a1 >> a2 >> osc::EndMessage;

			// Echo OSC message to console
//			std::cout << "received " << m.AddressPattern() << " message with arguments: "
//					<< a1 << " " << a2 << "\n";
			std::cout << "Time Difference: " << clock() - Start << std::endl;

			double durTime = static_cast<double>( a2 );
			long newFileDate = common::getFileMutateDate( config::scriptFileName );

			config::playSCStackProcessor -> playStack( durTime );
			if ( config::fileMutate != newFileDate ) {

				processFile( config::scriptFileName, false );
				std::cout << " PLAY STACK UPDATED! " << std::endl;
			}
			config::fileMutate = newFileDate;

			/*

			// Create iterators/indexes
			std::vector<std::vector<scriptcommand::ScriptCommand *> >::iterator loopPos;
			std::vector<scriptcommand::ScriptCommand *> scriptCommVec;
			std::vector<customtypes::Note>::iterator nPos;
			int scriptStackIndex = -1;

			// Start playing separate Script Command loops

			for( loopPos = config::playScriptCommandStack.begin(); loopPos != config::playScriptCommandStack.end(); ++loopPos ) {
				std::cout << std::endl;

				// Increment script stack index, output to console
				++scriptStackIndex;

				std::cout << "scriptStack " << scriptStackIndex + 1 << " of  " << config::playScriptCommandStack.size() << ": ";

				// Get the current vector script commands to loop
				scriptCommVec = ( *loopPos );

				// Check if previous wait time has been depleted/reached
				if ( config::loopWaitFor.at( scriptStackIndex ) <= 0.0 ) {
					config::loopWaitFor.at( scriptStackIndex ) = 0.0;

					// If previous wait time has been depleted,
					// Get next script command in current script command loop
					ScriptCommandReturn returnedScriptData;
					returnedScriptData = scriptCommVec.at( config::loopCurrentIndex.at( scriptStackIndex ) ) -> run();

					// If last script command is finished playing or did not contain a play function
					if ( ! * returnedScriptData.isPlaying ) {
						config::loopCurrentIndex.at( scriptStackIndex ) += 1;
						if ( config::loopCurrentIndex.at( scriptStackIndex ) >= scriptCommVec.size() ) {
							config::loopCurrentIndex.at( scriptStackIndex ) = 0;
						}
					}

					// Update wait time for this script command loop
					std::cout << "ran script command " << customtypes::nbFuncScriptNames[ returnedScriptData.scriptCommandVars -> noteBlockFunction ] << ", returned notestack " << returnedScriptData.noteStack  << " of size " << returnedScriptData.noteStack -> getSize() <<", returned isPlaying " << * returnedScriptData.isPlaying << std::endl;

					std::cout << "current scriptStack size " << scriptCommVec.size() << ": ";
					std::cout << "current scriptStack index " << config::loopCurrentIndex.at( scriptStackIndex ) << ": ";

					std::cout << "now waiting for: " << returnedScriptData.commandDur << std::endl;
					config::loopWaitFor.at( scriptStackIndex ) = returnedScriptData.commandDur;

					// If the script command variables returned contain a non-empty noteStack,
					if ( returnedScriptData.noteStack != nullptr ) {

//						char buffer[OUTPUT_BUFFER_SIZE];
//						osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
//						UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, SENDPORT ) );

						// Play note stack
						for (nPos = returnedScriptData.noteStack -> begin(); nPos != returnedScriptData.noteStack -> end(); ++nPos ) {
							std::string thisStreamName = '/' + *(returnedScriptData.scriptCommandVars) -> streamName;

							// Clear, fill and send OSC buffer
//							p.Clear();
//							p << osc::BeginBundleImmediate
//									<< osc::BeginMessage( thisStreamName.c_str() )
//							<< musical::convertNoteNumToHertz( ( *nPos ).pitch, config::noteRelatives, config::centerFreq, config::centerNote )
//							<< ( *nPos ).duration << ( *nPos ).velocity <<
//							osc::EndMessage
//							<< osc::EndBundle;
//							transmitSocket.Send( p.Data(), p.Size() );

							transmitter -> transmit( thisStreamName, musical::convertNoteNumToHertz( ( *nPos ).pitch, config::noteRelatives, config::centerFreq, config::centerNote ), ( *nPos ).duration, ( *nPos ).velocity );

							// Echo sent notes to console
							std::cout << "Playing: scriptStack: " << scriptStackIndex << " stream: " << thisStreamName << " p: " << ( *nPos ).pitch << " d: " << ( *nPos ).duration << " v: " << ( *nPos ).velocity << " h: " << musical::convertNoteNumToHertz( ( *nPos ).pitch, config::noteRelatives, config::centerFreq, config::centerNote ) << std::endl;

//							Send local timer
//							std::string timerMsg = "/notemakerclock";
//							int currTime = clock();
//							p.Clear();
//							p << osc::BeginBundleImmediate
//									<< osc::BeginMessage( timerMsg.c_str() )
//							<< currTime <<
//							osc::EndMessage
//							<< osc::EndBundle;
//							transmitSocket.Send( p.Data(), p.Size() );
//							std::cout << "Notemaker clock: " << currTime << std::endl;

						}
					}
				} else {
					// If previous wait time has NOT been depleted
					std::cout << std::endl;
					std::cout << "Waiting for " << config::loopWaitFor.at( scriptStackIndex ) << std::endl;
					config::loopWaitFor.at( scriptStackIndex ) -= a2;
				}
			} */
//			End of '/timing' OSC message received loop

		} else if( strcmp( m.AddressPattern(), "/test2" ) == 0 ){
			// example #2 -- argument iterator interface, supports
			// reflection for overloaded messages (eg you can call
			// (*arg)->IsBool() to check if a bool was passed etc).
			osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
			int a1 = (arg++)->AsInt32();
			float a2 = (arg++)->AsFloat();
			if( arg != m.ArgumentsEnd() )
				throw osc::ExcessArgumentException();

			std::cout << "received '/test2' message with arguments: "
					<< a1 << " " << a2 << "\n";
		}
	} catch( osc::Exception& e ){
		// any parsing errors such as unexpected argument types, or
		// missing arguments get thrown as exceptions.
		std::cout << "error while parsing message: "
				<< m.AddressPattern() << ": " << e.what() << "\n";
	}
}
} /* namespace oscreceiver */
