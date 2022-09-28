//
// Created by austi_eef6ewn on 9/28/2022.
//

#ifndef PROJECT1_STARTER_CODE_PREDICATE_H
#define PROJECT1_STARTER_CODE_PREDICATE_H

#include "Parameter.h"
#include <string>
#include <vector>

class Predicate {
public:
	std::string toString() {
		std::string outputString = "";
		outputString.append(id + "(");
		for(int i = 0; i < parameterVector.size(); ++i) {
			outputString.append("\'" + parameterVector.at(i)->toString() + "\'");
			if(i < parameterVector.size() - 1) {
				outputString.append(",");
			}
		}
		outputString.append(")");

		return outputString;
	}

private:
	std::string id;
	std::vector<Parameter*> parameterVector;
};


#endif //PROJECT1_STARTER_CODE_PREDICATE_H