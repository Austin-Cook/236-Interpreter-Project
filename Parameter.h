//
// Created by austi_eef6ewn on 9/28/2022.
//

#ifndef PROJECT1_STARTER_CODE_PARAMETER_H
#define PROJECT1_STARTER_CODE_PARAMETER_H

#include "iostream"
#include <string>

class Parameter {
public:
	Parameter(std::string p) {
		this->p = p;
	}

	std::string toString() const {
		return p;
	}

	bool isConstant() {
		if(p.size() == 0) {
			std::cerr << "Error in isConstant(): size of parameter is 0, expected is > 0";
			exit(1);
		} else if(p[0] == '\'') {
			return true;
		} else {
			return false;
		}
	}

private:
	std::string p;
};


#endif //PROJECT1_STARTER_CODE_PARAMETER_H
