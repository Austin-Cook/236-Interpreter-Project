//
// Created by austi_eef6ewn on 9/28/2022.
//

#ifndef PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#define PROJECT1_STARTER_CODE_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include <string>
#include <vector>

class DatalogProgram {
public:
	std::string toString() {
		// Schemes
		std::string outputString = "";
		outputString.append("Schemes(" + std::to_string(schemeVector.size()) + "):\n");
		for(int i = 0; i < schemeVector.size(); ++i) {
			outputString.append("  " + schemeVector.at(i).toString());
		}
		// Facts
		outputString.append("Facts(" + std::to_string(factVector.size()) + "):\n");
		for(int i = 0; i < factVector.size(); ++i) {
			outputString.append("  " + factVector.at(i).toString() + ".");
		}
		// Rules
		outputString.append("Rules(" + std::to_string(ruleVector.size()) + "):\n");
		for(int i = 0; i < ruleVector.size(); ++i) {
			outputString.append("  " + ruleVector.at(i).toString());
		}
		// Queries
		outputString.append("Queries(" + std::to_string(queryVector.size()) + "):\n");
		for(int i = 0; i < queryVector.size(); ++i) {
			outputString.append("  " + queryVector.at(i).toString() + "?");
		}
		// Domain
		outputString.append("Domain(" + std::to_string(domainVector.size()) + "):\n");
		for(int i = 0; i < domainVector.size(); ++i) {
			outputString.append("  \'" + domainVector.at(i) + "\'");
		}

		return outputString;
	}

private:
	std::vector<Predicate> schemeVector;
	std::vector<Predicate> factVector;
	std::vector<Predicate> queryVector;
	std::vector<Rule> ruleVector;
	std::vector<std::string> domainVector;
};


#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
