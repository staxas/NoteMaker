/*
 * MelodyGen.h
 *
 *  Created on: May 2, 2014
 *      Author: edwinrietmeijer
 */

#ifndef MELODYGEN_H_
#define MELODYGEN_H_

#define RANDOM_DEV mt19937

#include <random>
#include <vector>
#include <iostream>

#include "Generator.h"

namespace melodygen {

class MelodyGen : virtual public generator::Generator {
private:
	std::random_device rd;
	int startNote_;
	int currNote_ ;
	int nextNote_;
	int movement_;
	int lowestNote_;
	int highestNote_;
	int melodyLeapChance_;
	bool isLastLeap_;
public:
	MelodyGen();
	void init();
	int next();
	virtual ~MelodyGen();
};

} /* namespace melodygen */

#endif /* MELODYGEN_H_ */
