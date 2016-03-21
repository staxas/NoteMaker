/*
 * DummyGen.cpp
 *
 *  Created on: Feb 20, 2014
 *      Author: edwinrietmeijer
 */

#include "DummyGen.h"

DummyGen::DummyGen() {
	// SETUP PROCESS MANDATORY FOR ALL GENERATOR CLASSES:
	scriptName_ = "dummygen";
	genId_ = typeid( this ).name();
	generatorReturnType_ = gentypes::EMPTY;
	generatorReturnOrientation_ = gentypes::HORIZONTAL;
}

DummyGen::~DummyGen() {
}

