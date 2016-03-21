/*
 * GeneratorMediation.h
 *
 *  Created on: Apr 3, 2014
 *      Author: edwinrietmeijer
 */

#ifndef GENERATORMEDIATION_H_
#define GENERATORMEDIATION_H_

#include <vector>
#include <iostream>
#include "GeneratorTypes.h"

namespace genmediate {

typedef struct {
	std::vector<int> pitches;
	std::vector<double> durations;
	std::vector<double> velocities;
	gentypes::GeneratorReturnStructure * genReturnStructure;
	gentypes::GeneratorReturnType generatorReturnType;
	gentypes::GeneratorReturnOrientation generatorReturnOrientation;
} GeneratorMediatorVariables;

typedef struct {
	std::vector<int> * pitches;
	std::vector<double> * durations;
	std::vector<double> * velocities;
	gentypes::GeneratorReturnType * generatorReturnTypePtr;
	gentypes::GeneratorReturnOrientation * generatorReturnOrientationPtr;
	int * centerNotePtr;
	double * centerFreqPtr;
	std::vector<double> * noteRelativesPtr;
	gentypes::GeneratorReturnStructure * genReturnStructurePtr;

} GeneratorMediatorVariablePointers;

void clearVariables( GeneratorMediatorVariablePointers & );

void setVariablePointers( GeneratorMediatorVariables &, GeneratorMediatorVariablePointers & );

void setConfigPointers( GeneratorMediatorVariablePointers &, int &, double &, std::vector<double> & );

void setPointersToSets( GeneratorMediatorVariablePointers &, std::vector<int> *, std::vector<double> *, std::vector<double> * );

} /* namespace generatormediation */

#endif /* GENERATORMEDIATION_H_ */
