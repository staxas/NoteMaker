/*
 * GenAdmin.h
 *
 *  Created on: Feb 19, 2014
 *      Author: edwinrietmeijer
 */

#ifndef GENADMIN_H_
#define GENADMIN_H_

#include <vector>
#include <string>

#include "CustomTypes.h"
#include "Config.h"
#include "Generator.h"
#include "Serialism.h"
#include "PerNorgard.h"
#include "MelodyGen.h"
#include "Counterpoint.h"

const std::string allGenScriptNames[] = { "serialism", "pernorgard", "melodygen", "counterpoint" };
const std::vector<std::string> generatorScriptNames( std::begin( allGenScriptNames ), std::end( allGenScriptNames ) );

// Function for adding and administrating generators to the generator stack
void addGen( generator::Generator *, std::vector<generator::Generator *> &, std::vector<customtypes::GenId> & );

// Find and (if it exists) return an instance of a generator based on its scripting name
generator::Generator * findGenScriptName( std::string );

int getNrOfGens( generator::Generator * & );

int getGenStackIndex( generator::Generator * &, int );

#endif /* GENADMIN_H_ */
