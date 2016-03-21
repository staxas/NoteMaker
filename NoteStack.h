/*
 * NoteStack.h
 *
 *  Created on: Jan 28, 2014
 *      Author: edwinrietmeijer
 */

#ifndef NOTESTACK_H_
#define NOTESTACK_H_

#include <vector>
#include <algorithm>
#include <iomanip>
#include "CustomTypes.h"

namespace notestack {

class NoteStack {
private:
	std::vector<int> noteStackPitches_;
	std::vector<double> noteStackDurations_;
	std::vector<double> noteStackVelocities_;
	double longestDur_;
public:
	NoteStack();

	// Add a single note via pitch( int ), duration( double ), velocity( double )
	void addNote( const int &, const double &, const double & );

	// Get the duration of the longest note in the stack
	const double & getLongestDur();

	int getPitchVecSize();
	int getDurVecSize();
	int getVelVecSize();

	int getPitch( int );
	double getDuration( int );
	double getVelocity( int );

	int getLowestNoteIndex();

	void merge( notestack::NoteStack * );
	// Clear note stack
	void clear();

	// Dump noteStack to console
	void dump();

	virtual ~NoteStack();

};

} // namespace noteStack

#endif /* NOTESTACK_H_ */
