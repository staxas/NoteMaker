/*
 * ScriptCommandProcessor.h
 *
 *  Created on: Apr 16, 2014
 *      Author: edwinrietmeijer
 */

#ifndef SCRIPTCOMMANDPROCESSOR_H_
#define SCRIPTCOMMANDPROCESSOR_H_

#include <vector>

#include "ScriptCommand.h"
//#include "FileInterpreter.h"

namespace scprocessor {

class ScriptCommandProcessor {
private:
	std::vector<std::vector<scriptcommand::ScriptCommand *> > * aScriptStack_;
	std::vector<int> scrStackLoopSize_;
	std::vector<int> scrStackLoopPos_;
	std::vector<double> waitDur_;
	std::vector<scriptcommand::ScriptCommand *> playStacks_;
	bool isDump_;
	std::string scriptFileName_;
	scriptcommand::ScriptCommand * dummyPlayScriptCommand_;

public:
	ScriptCommandProcessor();
	ScriptCommandProcessor( std::vector<std::vector<scriptcommand::ScriptCommand *> > & );
	// Set all internal indexes to 0
	void resetStack();
	// Manually set a new stack ( resetStack() gets called automatically after )
	void setStack( std::vector<std::vector<scriptcommand::ScriptCommand *> > & );
//	// Dump all script commands
	void dumpStack();
	// Run all script command up to the next play command, then stop, saving position in scriptstack loop
	void prerunStack();
	// If there is a currently playing 'play' script command in any of the script stack loops, play it.
	void playStack( double & );
	// Choose to dump the script command to console
	void setDump( bool );
	void setScriptFileName( std::string );
	ScriptCommandVars setDummyPlaySCPointer();
	virtual ~ScriptCommandProcessor();
};

void initStack( std::vector<scriptcommand::ScriptCommand *> &, bool );

void initStack( std::vector<scriptcommand::ScriptCommand *> & );


} /* namespace scprocessor */

#endif /* SCRIPTCOMMANDPROCESSOR_H_ */
