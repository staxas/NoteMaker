/*
 * ScriptCommand.h
 *
 *  Created on: Mar 18, 2014
 *      Author: edwinrietmeijer
 */

#ifndef SCRIPTCOMMAND_H_
#define SCRIPTCOMMAND_H_

#include <vector>

#include "CustomTypes.h"
#include "CommonFunctions.h"
#include "ScriptCommandStructs.h"
#include "NoteBlock.h"
#include "Generator.h"
#include "OscTransmitter.h"
#include "MusicalFunctions.h"
#include "GeneratorMediation.h"

namespace scriptcommand {

class ScriptCommand {

private:
	ScriptCommandVars scrCommVars_;
	genmediate::GeneratorMediatorVariablePointers generatorMedVarPointers_;
	genmediate::GeneratorMediatorVariablePointers mutatorMedVarPointers_;
	bool isPlaying_;
	std::vector<notestack::NoteStack *>::iterator nbPos_;
	std::vector<notestack::NoteStack *>::iterator nbPosBegin_;
	std::vector<notestack::NoteStack *>::iterator nbPosEnd_;
	noteblock::NoteBlock	* noteBlockPointer_;
	gentypes::GeneratorReturnStructure genStructReturned_;
	ScriptCommandReturn dataToReturn_;
	int nbIndex_;
	int nbSize_;
	osctransmitter::OscTransmitter * transmitter_;

public:
	ScriptCommand();
	ScriptCommand( ScriptCommandVars );
	void setMediatorPointers( genmediate::GeneratorMediatorVariables &, genmediate::GeneratorMediatorVariables & );
	void setConfigPointers( int &, double &, std::vector<double> & );
	void setTransmitter( osctransmitter::OscTransmitter * );
	ScriptCommandReturn run();
	void setVarPointersToReturnType();
	void processGeneratorNotes( int );
	void processGeneratorNotes();


	void dump();
	bool isPlay();
	virtual ~ScriptCommand();
};

} /* namespace scriptcommand */

#endif /* SCRIPTCOMMAND_H_ */
