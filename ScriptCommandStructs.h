/*
 * ScriptCommandStruct.h
 *
 *  Created on: Mar 19, 2014
 *      Author: edwinrietmeijer
 */

#ifndef SCRIPTCOMMANDSTRUCT_H_
#define SCRIPTCOMMANDSTRUCT_H_

#include "CustomTypes.h"
#include "NoteBlock.h"
#include "Generator.h"
#include "NoteStack.h"

typedef struct {
	noteblock::NoteBlock * noteBlock;
	noteblock::NoteBlock * anotherNoteBlock;
	generator::Generator * generator;
	customtypes::NoteBlockFunc noteBlockFunction;
	customtypes::GeneratorFunc generatorFunction;
	std::string * streamName;
	std::vector<int> * pitchSet ;
	std::vector<double> * durationSet;
	std::vector<double> * velocitySet;
	std::vector<double> variableSet;
	 int firstGenFuncInt;
	 int secondGenFuncInt;
	 int thirdGenFuncInt;
	 double firstGenFuncDouble;
	 double secondGenFuncDouble;
	 double thirdGenFuncDouble;
} ScriptCommandVars;

typedef struct {
//	notestack::NoteStack * noteStack;
	ScriptCommandVars * scriptCommandVars;
	double commandDur;
	bool * isPlaying;
} ScriptCommandReturn;

#endif /* SCRIPTCOMMANDSTRUCT_H_ */
