/*
 * DummyMut.cpp
 *
 *  Created on: May 2, 2014
 *      Author: edwinrietmeijer
 */

#include "DummyMut.h"

DummyMut::DummyMut() {
	// SETUP PROCESS MANDATORY FOR ALL GENERATOR CLASSES:
	scriptName_ = "dummymut";
	genId_ = typeid( this ).name();
	generatorReturnType_ = gentypes::EMPTY;
	generatorReturnOrientation_ = gentypes::HORIZONTAL;
	processType_ = mutator::PITCH;
}

DummyMut::~DummyMut() {
}

