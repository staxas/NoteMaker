/*
 * GeneratorTypes.h
 *
 *  Created on: May 10, 2014
 *      Author: edwinrietmeijer
 */

#ifndef GENERATORTYPES_H_
#define GENERATORTYPES_H_

namespace gentypes {

typedef struct {
	std::vector< std::vector < int > > intSets;
	std::vector< std::vector < double > > doubleSets;
	std::vector< std::vector < std::string > > stringSets;
} GeneratorConfigVariables;

typedef enum {
	EMPTY, PITCH, DURATION, VELOCITY, NOTE
} GeneratorReturnType;

typedef enum {
	VERTICAL, HORIZONTAL
} GeneratorReturnOrientation;

typedef struct {
	GeneratorReturnType generatorReturnType;
	GeneratorReturnOrientation generatorReturnOrientation;
} GeneratorReturnStructure;

} /* namespace gentypes */

#endif /* GENERATORTYPES_H_ */
