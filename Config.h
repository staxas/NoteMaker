/*
 * Config.h
 *
 *  Created on: Mar 11, 2014
 *      Author: edwinrietmeijer
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <vector>
#include <string>
#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/IpEndpointName.h"
#include "ip/UdpSocket.h"
#include "OscTransmitter.h"

#include "Generator.h"
#include "GeneratorMediation.h"
#include "NoteBlock.h"
#include "CustomTypes.h"
#include "ScriptCommand.h"
#include "ScriptCommandProcessor.h"
#include "ScriptCommandStructs.h"

namespace config {
// Script file name
extern std::string scriptFileName;
extern long fileMutate;

extern int receivePort;
extern int sendPort;
extern std::string receiveAddress;
extern std::string sendAddress;

// A4 note is first note C minus 3
extern int centerNote;

// The frequency below is the given frequency of the center note.
// On a normal piano A would be 440Hz, sometimes 432Hz is used.
extern double centerFreq;
// Default generator chromatic/diatonic setting
extern bool isDiatonic;
// Default note values
extern std::vector<int> initDefaultPitch;
extern std::vector<int> * defaultPitch;
// Default duration values
extern std::vector<double> initDefaultDur;
extern std::vector<double> * defaultDuration;
// Default velocity values
extern std::vector<double> initDefaultVel;
extern std::vector<double> * defaultVelocity;

// -- Basic stacks and vectors --
extern std::vector<double> noteRelatives;
extern std::vector<std::vector<int> > pitchStack;
extern std::vector<std::vector<double> > durationStack;
extern std::vector<std::vector<double> > velocityStack;
//extern std::vector<noteblock::NoteBlock *> streamStack;
extern std::vector<std::string> streamNames;
extern std::vector<int> loopCurrentIndex;
extern std::vector<double>loopWaitFor;
extern std::vector<double> loopTimePassed;

extern std::vector<noteblock::NoteBlock * > noteBlockStack;
extern std::vector<generator::Generator *> generatorStack;
extern std::vector<customtypes::GenId> generatorIds;

//extern scriptcommand::ScriptCommand * dummyScriptCommand;
//extern notestack::NoteStack * dummyNoteStack;

//extern scriptcommand::ScriptCommand * dummyPlayScriptCommand;

extern std::vector<scriptcommand::ScriptCommand *> initScriptCommandStack;
extern std::vector<std::vector<scriptcommand::ScriptCommand *> > playScriptCommandStack;
extern bool dumpPlayCommandStack;

extern genmediate::GeneratorMediatorVariables genMediatorVars;
extern genmediate::GeneratorMediatorVariablePointers genMediatorVarPointers;

extern genmediate::GeneratorMediatorVariables mutatorMediatorVars;
extern genmediate::GeneratorMediatorVariablePointers mutatorMediatorVarPointers;


extern scprocessor::ScriptCommandProcessor * playSCStackProcessor;

//extern osctransmitter::OscTransmitter * transmitter;
}

#endif /* CONFIG_H_ */
