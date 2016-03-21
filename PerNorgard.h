/*
 * PerNorgard.h
 *
 *  Created on: Apr 3, 2014
 *      Author: edwinrietmeijer
 */

#ifndef PERNORGARD_H_
#define PERNORGARD_H_

#include "Generator.h"
#include <vector>

namespace pernorgard {

class PerNorgard : virtual public generator::Generator {
private:
	std::vector<int> prevNoteVec_;
	int firstNote_;
	int secondNote_;
	int newFirstNote_;
	int newSecondNote_;
	int noteDiff_;
public:
	PerNorgard();
	int next();
	void set( std::vector<double> );
	virtual ~PerNorgard();
};

} /* namespace pernorgard */

#endif /* PERNORGARD_H_ */
