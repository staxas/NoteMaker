/*
 * Serialism.h
 *
 *  Created on: Jan 17, 2014
 *      Author: edwinrietmeijer
 *
 *      This class creates an object which can generate note pitches returned as a vector of ints. Initially the
 *      12 notes of the chromatic scale are used.
 *
 *      The generated set can be reshuffled, and a vector of possible blocks of notes to grab from the generated
 *      set can be returned.
 *
 */

#ifndef SERIALISM_H_
#define SERIALISM_H_

#define RANDOM_DEV mt19937

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include "Generator.h"
#include "GeneratorMediation.h"

namespace serialism {

class Serialism : virtual public generator::Generator {
private:
	std::random_device rd;
	const static int rev[];
	const static int inv[];
	const static int standardNoteSet[];
	std::vector<int> initNoteSet_;
	std::vector<int> noteSet_;
	std::vector<int> noteSetIndexes_;
	std::vector<int> serialSet_;
	std::vector<int> blockSizes_;
	int setIndexesSize_;

	// Internal functions
	void shuffleSetIndexes();
	void generateSet();
	void toScreen();

public:
	Serialism();

	// Script supported functions
	void init();
	int get( int );
	virtual ~Serialism();
};

} // namespace serialism

#endif /* SERIALISM_H_ */
