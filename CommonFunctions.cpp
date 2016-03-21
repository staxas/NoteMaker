/*
 * CommonFunctions.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: edwinrietmeijer
 */

#include "CommonFunctions.h"
namespace common {
bool isDouble( const std::string & fString ) {
	std::string fromString = std::string( fString );
	double f = 0.0;
	std::string s = "";
	std::stringstream ss;
	ss << fromString;
	ss >> f;
	ss.clear();
	ss << f;
	ss >> s;

	if ( f != static_cast<int>( f ) ) {
		while ( fromString.back() == '0' ) {
			fromString.pop_back();
		}
		if ( fromString.back() == '.' ) {
			fromString.pop_back();
		}
	}
	//	std::cout << "fromstring: " << fromString << " f: " << f << " abs( f ): " <<  abs( f )  << " s: " << s << " ( fromString == s ): " << ( fromString == s ) << std::endl;
	return ( fromString == s );
}

bool isInt( const std::string & fromString ) {
	int i = 0;
	std::string s = "";
	std::stringstream ss;
	ss << fromString;
	ss >> i;
	ss.clear();
	ss << i;
	ss >> s;
	return ( fromString == s );
}

double stringToDouble( const std::string & fromString ) {
	double f = 0.0;
	std::stringstream ss;
	ss << fromString;
	ss >> f;
	return f;
}

int stringToInt( const std::string & fromString ) {
	int i = 0;
	std::stringstream ss;
	ss << fromString;
	ss >> i;
	return i;
}

std::string lower( std::string toLowerCase ) {
	std::transform( toLowerCase.begin(), toLowerCase.end(), toLowerCase.begin(), ::tolower );
	return toLowerCase;
}

void strVectorToLower( std::vector<std::string> & vecToConvert ) {
	std::vector<std::string>:: iterator pos;
	for( pos = vecToConvert.begin(); pos != vecToConvert.end(); ++pos ) {
		std::transform( (*pos).begin(), (*pos).end(), (*pos).begin(), ::tolower);
	}
}

std::vector<double> strVecToDoubleVec( std::vector<std::string> inVector ) {
	std::vector<double> outVector;
	std::vector<std::string>::iterator pos;
	for( pos = inVector.begin(); pos != inVector.end(); ++pos ) {
		if ( isDouble( *pos ) ) {
			outVector.push_back( stringToDouble( *pos ) );
		}
	}
	return outVector;
}

std::vector<int> strVecToIntVec( std::vector<std::string> inVector ) {
	std::vector<int> outVector;
	std::vector<std::string>::iterator pos;
	for( pos = inVector.begin(); pos != inVector.end(); ++pos ) {
		if ( isInt( *pos ) ) {
			outVector.push_back( stringToInt( *pos ) );
		}
	}
	return outVector;
}

long getFileMutateDate( std::string fileName ) {
	struct stat buf;
	stat( fileName.c_str() ,&buf);

//	std::cout << buf.st_dev << std::endl;
//	std::cout << buf.st_ino << std::endl;
//	std::cout << buf.st_mode << std::endl;
//	std::cout << buf.st_nlink << std::endl;
//	std::cout << buf.st_uid << std::endl;
//	std::cout << buf.st_gid << std::endl;
//	std::cout << buf.st_rdev << std::endl;
//	std::cout << buf.st_size << std::endl;
//	std::cout << buf.st_blksize << std::endl;
//	std::cout << buf.st_blocks << std::endl;
//	std::cout << buf.st_atime << std::endl;
	return buf.st_mtime;
	//              std::cout << buf.st_ctime << std::endl;
}


int indexMod( int index, int size ) {
	size = ( int ) size;
	index = ( int ) index;
	int diff = 0;
	if ( index < 0 ) {
		diff = ( ( abs( static_cast<int> ( index ) ) ) / size ) + 1;
	}
	index = ( index + ( size * diff ) ) % size;
	return index;
}

} // namespace common

void toConsole( std::string aString ) {
	std::cout << aString << std::endl;
}

void toConsole( int anInt ) {
	std::cout << anInt << std::endl;
}

void toConsole( double aDouble ) {
	std::cout << aDouble << std::endl;
}

void boolToConsole( bool aBool ) {
	if ( aBool ) {
		std::cout << "true " << std::endl;
	}
	else
	{
		std::cout << "false " << std::endl;
	}

}

void endline() {
	std::cout << std::endl;
}
