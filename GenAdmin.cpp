/*
 * GenAdmin.cpp
 *
 *  Created on: Feb 19, 2014
 *      Author: edwinrietmeijer
 */

#include "GenAdmin.h"

void addGen( generator::Generator * genObj, std::vector<generator::Generator *> & generatorStack, std::vector<customtypes::GenId> & generatorIds ) {

	// Create GenId for object to be added to stack
	customtypes::GenId newGenId;
	newGenId.scriptName = genObj -> getScriptName();
	newGenId.genType = genObj -> getGenId();

	bool foundGenType = false;
	customtypes::GenId aGenId;
	std::vector<customtypes::GenId>::reverse_iterator pos;
	for ( pos = generatorIds.rbegin(); pos != generatorIds.rend(); ++pos ) {
		aGenId = *pos;
		if ( foundGenType == false && aGenId.genType == newGenId.genType ) {
			newGenId.instanceNo = aGenId.instanceNo + 1;
			foundGenType = true;
		}
	}
	if ( foundGenType == false ) {
		newGenId.instanceNo = 0;
	}

	generatorStack.push_back( genObj );

	newGenId.vectorIndex =  generatorStack.size() - 1;
	//	std::cout << newGenId.vectorIndex << " " << newGenId.instanceNo << " " << newGenId.genType << std::endl;
	generatorIds.push_back( newGenId );
}


generator::Generator * findGenScriptName( std::string genScriptName ) {
	generator::Generator * genToReturn = new generator::Generator;
	if ( genScriptName == "serialism") {
		genToReturn = new serialism::Serialism();
	}
	if ( genScriptName == "pernorgard") {
		genToReturn = new pernorgard::PerNorgard();
	}
	if ( genScriptName == "melodygen") {
		genToReturn = new melodygen::MelodyGen();
	}
	if ( genScriptName == "counterpoint") {
		genToReturn = new counterpoint::Counterpoint();
	}
	return genToReturn;
}

int getNrOfGens( generator::Generator * & genToCheck ) {
	std::vector<generator::Generator *>::iterator pos;
	int nrOfGens = 0;
	for ( pos = config::generatorStack.begin(); pos != config::generatorStack.end(); ++pos ) {
		if( ( *pos ) -> getGenId() == genToCheck  -> getGenId() ) {
			++nrOfGens;
		}
	}
	return nrOfGens;
}

int getGenStackIndex( generator::Generator * & genToCheck, int genInstanceNo) {
	std::vector<generator::Generator *>::iterator pos;
	int nrOfGens = 0;
	int genStackIndex = -1;
	int genIndex = genStackIndex;
	for ( pos = config::generatorStack.begin(); pos != config::generatorStack.end(); ++pos ) {
		++genStackIndex;
		if( ( *pos ) -> getGenId() == genToCheck  -> getGenId() ) {
			++nrOfGens;
			if( nrOfGens == genInstanceNo ) {
				genIndex = genStackIndex;
			}
		}
	}
	return genIndex;
}

