/*
 * DummyMut.h
 *
 *  Created on: May 2, 2014
 *      Author: edwinrietmeijer
 */

#ifndef DUMMYMUT_H_
#define DUMMYMUT_H_

#include "Mutator.h"

class DummyMut : virtual public mutator::Mutator {
public:
	DummyMut();
	virtual ~DummyMut();
};

#endif /* DUMMYMUT_H_ */
