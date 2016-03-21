/*
 * OscTransmitter.cpp
 *
 *  Created on: Mar 12, 2014
 *      Author: edwinrietmeijer
 */

#include "OscTransmitter.h"

namespace osctransmitter {

OscTransmitter * OscTransmitter::Instance()
{
	static OscTransmitter instance;
	return &instance;
}

void OscTransmitter::transmit( std::string streamName, double freq, double dur, double vel ) {

    // Wait until previous transmission is completed.
    while ( isTransmitting ) {
    }
    isTransmitting = true;
    
	std::string thisStreamName = '/' + streamName;
	p.Clear();
	p << osc::BeginBundleImmediate
			<< osc::BeginMessage( streamName.c_str() )
	<< freq << dur << vel << osc::EndMessage
	<< osc::EndBundle;
	transmitSocket.Send( p.Data(), p.Size() );
	isTransmitting = false;
}

//void OscTransmitter::transmitFake( std::string streamName, double freq, double dur, double vel ) {
//	std::string thisStreamName = '/' + streamName;
//
//	std::cout << thisStreamName << " " << freq << " " << dur << " " << vel << std::endl;
//
//
//}


OscTransmitter::OscTransmitter() : isTransmitting( false ), transmitSocket( IpEndpointName( ADDRESS, SENDPORT ) ), p( buffer, OUTPUT_BUFFER_SIZE ) {

}

} /* namespace osctransmitter */
