/*
 * CommonFunctions.h
 *
 *  Created on: Feb 5, 2014
 *      Author: edwinrietmeijer
 */

#ifndef COMMONFUNCTIONS_H_
#define COMMONFUNCTIONS_H_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>
#include "CustomTypes.h"

 #include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>

namespace common {
// Return boolean, string convertable to double?
bool isDouble( const std::string & );
// Return boolean, string convertable to double?
bool isInt( const std::string & );
// Convert string to double
double stringToDouble ( const std::string & );
// Convert string to int
int stringToInt ( const std::string & );
// Convert string to lowercase
std::string lower( std::string toLowerCase );
// Convert vector of strings to lowercase
void strVectorToLower( std::vector<std::string> & );
// Convert vector of strings to vector of doubles ( compare vector sizes for consistancy )
std::vector<double> strVecToDoubleVec( std::vector<std::string> );
// Convert vector of strings to vector of ints ( compare vector sizes for consistancy )
std::vector<int> strVecToIntVec( std::vector<std::string> );

long getFileMutateDate( std::string );

int indexMod( int index, int size );

} // namespace common

// String to single line console output
void toConsole( std::string );
void toConsole( int );
void toConsole( double );
void boolToConsole( bool );

// Line break
void endline();

#endif /* COMMONFUNCTIONS_H_ */
