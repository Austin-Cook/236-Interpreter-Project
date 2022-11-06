//
// Created by austi_eef6ewn on 9/28/2022.
//

#ifndef PROJECT1_STARTER_CODE_RULE_H
#define PROJECT1_STARTER_CODE_RULE_H

#include "Predicate.h"
#include <vector>

class Rule {
public:
	Rule(Predicate* headPredicate, std::vector<Predicate*> bodyPredicates) {
		this->headPredicate = headPredicate;
		for(int i = 0; i < (int)bodyPredicates.size(); i++) {
			this->bodyPredicates.push_back(bodyPredicates.at(i));
		}
	}

	std::string toString() const {
		std::string outputString = "";
		outputString.append(headPredicate->toString() + " :- ");
		for(int i = 0; i < (int)bodyPredicates.size(); ++i) {
			outputString.append(bodyPredicates.at(i)->toString());
			if(i < (int)bodyPredicates.size() - 1) {
				outputString.append(",");
			}
		}
		outputString.append(".");

		return outputString;
	}

	std::vector<Predicate*> getBodyPredicatesVector() const {
		return bodyPredicates;
	}

	Predicate* getHeadPredicate() const {
		return headPredicate;
	}

private:
	Predicate* headPredicate;
	std::vector<Predicate*> bodyPredicates;
};


#endif //PROJECT1_STARTER_CODE_RULE_H
