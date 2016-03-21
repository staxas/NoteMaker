/*
 * GeneratorMediation.cpp
 *
 *  Created on: Apr 3, 2014
 *      Author: edwinrietmeijer
 */

#include "GeneratorMediation.h"

namespace genmediate {

void clearVariables( GeneratorMediatorVariablePointers & gMVP ) {
	( gMVP.pitches ) -> clear();
	( gMVP.durations ) -> clear();
	( gMVP.velocities ) -> clear();
}

void setVariablePointers( GeneratorMediatorVariables & gMV, GeneratorMediatorVariablePointers & gMVP ) {
	gMVP.pitches = & gMV.pitches;
	gMVP.durations = & gMV.durations;
	gMVP.velocities = & gMV.velocities;
	gMVP.generatorReturnTypePtr = & gMV.generatorReturnType;
	gMVP.generatorReturnOrientationPtr = & gMV.generatorReturnOrientation;

}

void setConfigPointers( GeneratorMediatorVariablePointers & gMVP, int & cntrNote, double & cntrFreq, std::vector<double> & nteRels ) {
	gMVP.centerNotePtr = & cntrNote;
	gMVP.centerFreqPtr = & cntrFreq;
	gMVP.noteRelativesPtr = & nteRels;
}

void setPointersToSets( GeneratorMediatorVariablePointers & gMVP, std::vector<int> * pitchSet, std::vector<double> * durationsSet , std::vector<double> * velocitiesSet ) {
	gMVP.pitches = pitchSet;
	gMVP.durations = durationsSet;
	gMVP.velocities = velocitiesSet;
}

} /* namespace generatormediation */
