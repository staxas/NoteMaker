/*
 * Generator.h
 *
 *  Created on: Feb 19, 2014
 *      Author: edwinrietmeijer
 */

#ifndef GENERATOR_H_
#define GENERATOR_H_

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>

#include "GeneratorMediation.h"
#include "GeneratorTypes.h"

//#include "NoteBlock.h"

namespace generator {

const int chromToDia[] = { 0, 2, 4, 5, 7, 9, 11 };

class Generator {
protected:
	std::string scriptName_;
	std::string genId_;
	bool isDia_;
	genmediate::GeneratorMediatorVariablePointers genMedVarPointers_;
	genmediate::GeneratorMediatorVariablePointers mutatorMedVarPointers_;
	gentypes::GeneratorReturnType generatorReturnType_;
	gentypes::GeneratorReturnOrientation generatorReturnOrientation_;

	int scaleSize_;
	int chordNo_;
	int calcNote( int & );
	int calcNoteOct( int & );
	void addPitch( int );
	void addPitch( std::vector<int> & );
	std::vector<int> getPitches();

	int indexMod_( int, int );

public:
	Generator();

	// GenId functions
	std::string getScriptName();
	std::string getGenId();

	// Create link to generator mediator variables
	void setMediatorPointers( genmediate::GeneratorMediatorVariables &, genmediate::GeneratorMediatorVariables &  );

	// Set the number of notes in the current scale, init() is called subsequentially.
	void setScaleSize( const int & );

	void setDia( bool );
	void setChordNo( int & );


	// -- Generator user definable functions --
	// Called when processing a ScriptCommand object.
	// All subclasses of the generator class can only use these overloaded functions 
	// for scripted function calls to generator instances on the stack.
	// Not all of these functions need to be implemented in a custom generator.
	// For example, one can choose to overload get( int ), but not next().

	// Initialize generator. In the script reading phase, this is called after all
	// other operations which are needed for adding the generator to the generator stack.
	// You can put anything you want in its overloaded version, it is empty by default.
	virtual void init();
	// Reset generator
	virtual void reset();
	// Set generator configuration
	virtual void set( std::vector<double> );

	// Get an arbitrary number of notes/pieces of data
	virtual int get();
	virtual int get( int );

	// Get next iteration of data
	virtual int next();

	// Process a noteblock in a mutator-type generator
	virtual int process();

	//	std::vector<int> getLowestPitches( noteblock::NoteBlock * );

	virtual ~Generator();
};

} // namespace generator

#endif /* GENERATOR_H_ */
