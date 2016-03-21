/*
 * CustomTypes.h
 *
 *  Created on: Jan 28, 2014
 *      Author: edwinrietmeijer
 */

#ifndef CUSTOMTYPES_H_
#define CUSTOMTYPES_H_

#include <string>

#include "CommonFunctions.h"
#include "Generator.h"

namespace customtypes {

template<typename T> void print( const T& val)
{
	std::cout << val << ' ';
}

struct toScreen
{
	template <typename T>
	void operator() ( const T& val ) const {
		print( val );
	}
};

typedef struct {
	std::string genType;
	std::string scriptName;
	int instanceNo;
	int vectorIndex;
} GenId;

//typedef struct {
//	int pitch;
//	double duration;
//	double velocity;
//	bool rest;
//} Note;

enum NoteVars {
	PITCH, DURATION, VELOCITY
};

enum NoteBlockFunc {
	NO_NB_FUNC, PLAY, CLEAR, ADD_START, ADD_END, ADD_OVER_START, ADD_OVER_END, REPLACE_START, REPLACE_END, MUTATE, MERGE_HORIZONTAL, MERGE_VERTICAL
};

enum GeneratorFunc {
	NO_GEN_FUNC, INIT, SET, GET, GET_INT, NEXT, NEXT_INT, PROCESS
};

enum InterpMode {
	CONFIG_MODE, INIT_MODE, PLAY_MODE
};

const NoteBlockFunc allNBFuncs[] = { NO_NB_FUNC, PLAY, CLEAR, ADD_START, ADD_END, ADD_OVER_START, ADD_OVER_END, REPLACE_START, REPLACE_END, MUTATE, MERGE_HORIZONTAL, MERGE_VERTICAL };
const std::vector<NoteBlockFunc> allNoteBlockFuncs(std::begin( allNBFuncs ), std::end( allNBFuncs ) );

const std::string nbFuncScriptNames[] = { "no_nb_func", "play", "clear", "add_start", "add_end", "add_over_start", "add_over_end", "replace_start", "replace_end", "mutate", "merge_vertical", "merge_horizontal" };
const std::vector<std::string> noteBlockFuncScriptNames(std::begin( nbFuncScriptNames ), std::end( nbFuncScriptNames ) );

const NoteBlockFunc nonGenNBFuncs[] = { NO_NB_FUNC, PLAY, CLEAR, MUTATE, MERGE_HORIZONTAL, MERGE_VERTICAL };
const std::vector<NoteBlockFunc> nonGeneratorNoteBlockFuncs(std::begin( nonGenNBFuncs ), std::end( nonGenNBFuncs ) );

const NoteBlockFunc NBtoNBFuncs[] = { MUTATE, MERGE_HORIZONTAL, MERGE_VERTICAL };
const std::vector<NoteBlockFunc> noteBlockToNoteBlockFuncs( std::begin( NBtoNBFuncs ), std::end( NBtoNBFuncs ) );

const std::string NBtoNBFuncScriptNames[] = { "mutate", "merge_vertical", "merge_horizontal" };
const std::vector<std::string> nnoteBlockToNoteBlockFuncScriptNames(std::begin( nbFuncScriptNames ), std::end( nbFuncScriptNames ) );

const GeneratorFunc allGenFuncs[] = { NO_GEN_FUNC, INIT, SET, GET, GET_INT, NEXT, NEXT_INT, PROCESS };
const std::vector<GeneratorFunc> allGeneratorFuncs( std::begin( allGenFuncs ), std::end( allGenFuncs ) );

const std::string genFuncScriptNames[] = { "no_gen_func", "init", "set", "get", "get_int", "next", "next_int", "process" };
const std::vector<std::string> generatorFuncScriptNames(std::begin( genFuncScriptNames ), std::end( genFuncScriptNames ) );

const GeneratorFunc nonNBGenFuncs[] = { INIT, SET };
const std::vector<GeneratorFunc> nonNoteBlockGeneratorFuncs(std::begin( nonNBGenFuncs ), std::end( nonNBGenFuncs ) );

const std::string nonNBGenFuncScriptNames[] = { "init", "set" };
const std::vector<std::string> nonNoteBlockGeneratorFuncsScriptNames(std::begin( nonNBGenFuncScriptNames ), std::end( nonNBGenFuncScriptNames ) );

const GeneratorFunc mutatorGenFuncs[] = { PROCESS };
const std::vector<GeneratorFunc> mutatorGeneratorFuncs(std::begin( mutatorGenFuncs ), std::end( mutatorGenFuncs ) );

const std::string mutatorGenFuncScriptNames[] = { "process" };
const std::vector<std::string> mutatorGeneratorFuncsScriptNames(std::begin( genFuncScriptNames ), std::end( genFuncScriptNames ) );


} // namespace customtypes

#endif /* CUSTOMTYPES_H_ */
