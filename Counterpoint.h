/*
 * Counterpoint.h
 *
 *  Created on: May 2, 2014
 *      Author: edwinrietmeijer
 */

#ifndef COUNTERPOINT_H_
#define COUNTERPOINT_H_

#include "Mutator.h"

namespace counterpoint {

class Counterpoint  : virtual public mutator::Mutator {
public:
	Counterpoint();
	int process();
	virtual ~Counterpoint();
};

} /* namespace counterpoint */

#endif /* COUNTERPOINT_H_ */
