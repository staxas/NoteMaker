/*
 * DummyGen.h
 *
 *  Created on: Feb 20, 2014
 *      Author: edwinrietmeijer
 */

#ifndef DUMMYGEN_H_
#define DUMMYGEN_H_

#include "Generator.h"

class DummyGen : virtual public generator::Generator {
public:
	DummyGen();
	virtual ~DummyGen();
};

#endif /* DUMMYGEN_H_ */
