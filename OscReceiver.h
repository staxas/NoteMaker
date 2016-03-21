/*
 * OscReceiver.h
 *
 *  Created on: Mar 6, 2014
 *      Author: edwinrietmeijer
 */

#ifndef OSCRECEIVER_H_
#define OSCRECEIVER_H_

#include <iostream>
#include <string>
#include <ctime>
#include <vector>

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/IpEndpointName.h"
#include "ip/UdpSocket.h"
#include "Config.h"
#include "CustomTypes.h"
#include "NoteBlock.h"
#include "MusicalFunctions.h"
#include "OscTransmitter.h"
#include "FileInterpreter.h"

#include <unistd.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>

namespace oscreceiver {

#define RECEIVEPORT 7000
#define ADDRESS "127.0.0.1"
#define OUTPUT_BUFFER_SIZE 1024

// OSC receiver for syncing and sending calculated notes to the OscTransmitter object

class OscReceiver : public osc::OscPacketListener {
protected:
//	std::vector<customtypes::Note> stackToPlay_;
//	std::vector<customtypes::Note>::iterator nPos;

	osctransmitter::OscTransmitter * transmitter;

	virtual void ProcessMessage( const osc::ReceivedMessage&,
				const IpEndpointName& );

};

} /* namespace oscreceiver */

#endif /* OSCRECEIVER_H_ */
