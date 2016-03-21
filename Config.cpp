/*
 * Config.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: edwinrietmeijer
 */

#include "Config.h"

namespace config {
std::string scriptFileName;
long fileMutate;

int receivePort;
int sendPort;
std::string receiveAddress;
std::string sendAddress;

int centerNote;
// The frequency below is the given frequency of the center note.
// On a normal piano A would be 440Hz, sometimes 432Hz is used.
double centerFreq;

bool isDiatonic;


// Default note values
std::vector<int> initDefaultPitch;
std::vector<int> * defaultPitch = & initDefaultPitch;

std::vector<double> initDefaultDur;
std::vector<double> * defaultDuration = & initDefaultDur;

std::vector<double> initDefaultVel;
std::vector<double> * defaultVelocity = & initDefaultVel;

// -- Basic stacks and vectors --
std::vector<double> noteRelatives;
std::vector<std::vector<int> > pitchStack;
std::vector<std::vector<double> > durationStack;
std::vector<std::vector<double> > velocityStack;
//std::vector<noteblock::NoteBlock *> streamStack;
std::vector<std::string> streamNames;
std::vector<int> loopCurrentIndex;
std::vector<double> loopWaitFor;
std::vector<double> loopTimePassed;

std::vector<noteblock::NoteBlock *> noteBlockStack;
std::vector<generator::Generator *> generatorStack;
std::vector<customtypes::GenId> generatorIds;

//scriptcommand::ScriptCommand * dummyScriptCommand;
//notestack::NoteStack * dummyNoteStack;

std::vector<scriptcommand::ScriptCommand *> initScriptCommandStack;
std::vector<std::vector<scriptcommand::ScriptCommand *> > playScriptCommandStack;
bool dumpPlayCommandStack = true;

genmediate::GeneratorMediatorVariables genMediatorVars;
genmediate::GeneratorMediatorVariablePointers genMediatorVarPointers;

genmediate::GeneratorMediatorVariables mutatorMediatorVars;
genmediate::GeneratorMediatorVariablePointers mutatorMediatorVarPointers;

scprocessor::ScriptCommandProcessor * playSCStackProcessor;

//osctransmitter::OscTransmitter * transmitter = osctransmitter::OscTransmitter::Instance();
}
