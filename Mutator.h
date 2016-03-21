/*
 * Mutator.h
 *
 *  Created on: May 2, 2014
 *      Author: edwinrietmeijer
 */

#ifndef MUTATOR_H_
#define MUTATOR_H_

#include "Generator.h"

namespace mutator {

enum NoteVars {
	NONE, PITCH, DURATION, VELOCITY, NOTE
};

class Mutator : virtual public generator::Generator {
protected:
	NoteVars processType_;
public:
	Mutator();
	virtual ~Mutator();
};

} /* namespace mutator */

#endif /* MUTATOR_H_ */
