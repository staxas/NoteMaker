/*
 * FileInterpreter.h
 *
 *  Created on: Jan 17, 2014
 *      Author: edwinrietmeijer
 */

#ifndef FileInterpreter_H_
#define FileInterpreter_H_

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

#include "CustomTypes.h"
#include "CommonFunctions.h"
#include "MusicalFunctions.h"
#include "NoteBlock.h"
#include "Generator.h"
#include "GenAdmin.h"
#include "Config.h"
#include "ScriptCommand.h"

void processFile( std::string, bool );
// Convert script line tokens to a SciptCommand variable struct
bool tokensToScriptVars( std::string &, std::vector<std::string> &, ScriptCommandVars &, int & );
void writeToFile( std::string, const std::string & );
void fileToScreen( std::string );

#endif /* FileInterpreter_H_ */
