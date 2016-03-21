/*
 * Counterpoint.cpp
 *
 *  Created on: May 2, 2014
 *      Author: edwinrietmeijer
 */

#include "Counterpoint.h"

namespace counterpoint {

Counterpoint::Counterpoint() {
	// MANDATORY FOR ALL GENERATOR CLASSES:
	scriptName_ = "counterpoint";
	genId_ = typeid( this ).name();
	generatorReturnType_ = gentypes::PITCH;
	generatorReturnOrientation_ = gentypes::HORIZONTAL;
	processType_ = mutator::PITCH;
}

int Counterpoint::process() {
	std::vector<int> pitchesToProcess = getPitches();
	std::vector<int>::iterator pos;
	for( pos = pitchesToProcess.begin(); pos != pitchesToProcess.end(); ++pos ) {
		addPitch( ( * pos ) + 7 );
	}
	return 1;
}

Counterpoint::~Counterpoint() {
}

} /* namespace counterpoint */
