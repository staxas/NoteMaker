/*
 * OscTransmitter.h
 *
 *  Created on: Mar 12, 2014
 *      Author: edwinrietmeijer
 */

#ifndef OSCTRANSMITTER_H_
#define OSCTRANSMITTER_H_

#include <string>
#include <iostream>
#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/IpEndpointName.h"
#include "ip/UdpSocket.h"

#define ADDRESS "127.0.0.1"
#define SENDPORT 7001
#define OUTPUT_BUFFER_SIZE 1024

// OSC Transmitter, sends out note data in the form /note, pitch, duration, velocity
// Modelled as singleton class

namespace osctransmitter {

class OscTransmitter {

public:
	static OscTransmitter * Instance();
	void transmit( std::string, double, double, double );
//	void transmitFake( std::string, double, double, double );
private:
    bool isTransmitting;
	UdpTransmitSocket transmitSocket;
	char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p;
	OscTransmitter();
	OscTransmitter( const OscTransmitter& );
	OscTransmitter& operator=( OscTransmitter const& );
};

} /* namespace osctransmitter */

#endif /* OSCTRANSMITTER_H_ */
