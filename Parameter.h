//
// Created by austi_eef6ewn on 9/28/2022.
//

#ifndef PROJECT1_STARTER_CODE_PARAMETER_H
#define PROJECT1_STARTER_CODE_PARAMETER_H

#include <string>

class Parameter {
public:
	Parameter(std::string p) {
		this->p = p;
	}

	std::string toString() {
		return p;
	}

private:
	std::string p;
};


#endif //PROJECT1_STARTER_CODE_PARAMETER_H
