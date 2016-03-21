/*
 * NoteBlock.h
 *
 *  Created on: Jan 28, 2014
 *      Author: edwinrietmeijer
 */

#ifndef NOTEBLOCK_H_
#define NOTEBLOCK_H_

#include <vector>

#include "NoteStack.h"
#include "CustomTypes.h"

namespace noteblock {

class NoteBlock {
private:
	std::vector<notestack::NoteStack *> noteStackList_;
	customtypes::NoteVars addAllOfThisVector_;
	std::vector<notestack::NoteStack *>::iterator sPos_;
	bool isLastStackClosed_;

	// Internal function for calculating size of main vector to add
	int addThisVector ( const std::vector<int> &, const std::vector<double> &, const std::vector<double> & );

public:
	NoteBlock();

	// Add a new empty stack to the end of the noteStackList_
	void newStack();

	// Set the main note variable ( pitch, duration, velocity ) to include all values of its vector ( init is PITCH )
	// loop other values if necessary
	void setMainVar( const customtypes::NoteVars & );
	// Add a single note to the current active stack, or is last stack is closed,
	// add a new stack, and add the note to that stack
	void add( int &, double &, double & );

//	void add( customtypes::Note );
	// Close the current stack
	void close();
	// Add notes to the start of the noteStackList_ ( append )
//	void addStartHorizontal( const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );
//	void addStartVertical( const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );

	// Add notes over the start of the noteStackList_ ( layer )
//	void addOverStartHorizontal( const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );
//	void addOverStartVertical( const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );

	// Add notes to the end of the noteStackList_ ( append )
	void addEndHorizontal( const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );
	void addEndVertical( const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );

	// Add notes over the end of the noteStackList_ ( layer )
	void addOverEndHorizontal(  const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );
	void addOverEndVertical(  const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );

	// Replace notes at the start of the noteStackList_ ( replace )
//	void replaceStartHorizontal( const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );
//	void replaceStartVertical( const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );

	// Replace notes at the end of the noteStackList_ ( replace )
//	void replaceEndHorizontal( const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );
//	void replaceEndVertical( const std::vector<int> *, const std::vector<double> *, const std::vector<double> * );

	// Reset getNextStack iterator
	void stackPosReset();

	// Get the note vector in the next note stack, or the first stack if the last has already been played
//	std::vector<customtypes::Note> getNextNoteVector();

	// Get the length of the longest note in the current getNextNoteVector note stack
	const double getLongestDur();

    // Return a copy of the noteStackList_ vector
	std::vector<notestack::NoteStack *> getVector();

	// Get the current size of the noteStackList_ vector
	int getSize();
	// Clear the noteStackList_ vector
	void clear();
	// Copy this noteblock to another noteblock
	void copy( noteblock::NoteBlock* & );
	// Merge a noteblock to the end of this noteblock
	void mergeHorizontal( noteblock::NoteBlock* & );

	void mergeVertical( noteblock::NoteBlock* & );

	// Append a noteStack vector
	void append( std::vector<notestack::NoteStack *> & );

	std::vector<int> getLowestPitches();
	// Internal function for the dynamic looping of negative and larger-than indexes of vectors
	int indexMod( int, int );

	void dump();
	virtual ~NoteBlock();

	// noteStackList_ iterators and typedefs
	typedef std::vector<notestack::NoteStack *>::iterator iterator;
	typedef std::vector<notestack::NoteStack *>::const_iterator const_iterator;

	iterator begin() { return noteStackList_.begin(); }
	const_iterator begin() const { return noteStackList_.begin(); }

	iterator end() { return noteStackList_.end(); }
	const_iterator end() const { return noteStackList_.end(); }
};


} // namespace noteblock

#endif /* NOTEBLOCK_H_ */
