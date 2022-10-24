//
// Created by austi_eef6ewn on 9/28/2022.
//

#ifndef PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
#define PROJECT1_STARTER_CODE_DATALOGPROGRAM_H

#include "Predicate.h"
#include "Rule.h"
#include "Parameter.h"
#include <string>
#include <vector>
#include <set>

class DatalogProgram {
public:
	void addScheme(std::string id, std::vector<Parameter*> parameterVector) {
		Predicate* schemeToAdd = new Predicate(id, parameterVector);
		schemeVector.push_back(schemeToAdd);
	}

	void addFact(std::string id, std::vector<Parameter*> parameterVector) {
		Predicate* predicateToAdd = new Predicate(id, parameterVector);
		factVector.push_back(predicateToAdd);
	}

	void addQuery(Predicate* predicate) {
		queryVector.push_back(predicate);
	}

	// bodyPredicates vector contains the headPredicate at index 0 and bodyPredicates from index 1 and on
	void addRule(std::vector<Predicate*> bodyPredicates) {
		std::vector<Predicate*> tempPredicates;
		// Copy all but 1st index to tempPredicates
		for(int i = 1; i < (int)bodyPredicates.size(); i++) {
			tempPredicates.push_back(bodyPredicates.at(i));
		}
		Rule* ruleToAdd = new Rule(bodyPredicates.at(0), tempPredicates); //FIXME remove first bodyPRedicate from 2nd param
		ruleVector.push_back(ruleToAdd);
	}

	void addDomain(std::string domain) {
		domainSet.insert(domain);
	}

	std::string toString() {
		// Schemes
		std::string outputString = "";
		outputString.append("Schemes(" + std::to_string(schemeVector.size()) + "):\n");
		for(int i = 0; i < (int)schemeVector.size(); ++i) {
			outputString.append("  " + schemeVector.at(i)->toString() + "\n");
		}
		// Facts
		outputString.append("Facts(" + std::to_string(factVector.size()) + "):\n");
		for(int i = 0; i < (int)factVector.size(); ++i) {
			outputString.append("  " + factVector.at(i)->toString() + "." + "\n");
		}
		// Rules
		outputString.append("Rules(" + std::to_string(ruleVector.size()) + "):\n");
		for(int i = 0; i < (int)ruleVector.size(); ++i) {
			outputString.append("  " + ruleVector.at(i)->toString() + "\n");
		}
		// Queries
		outputString.append("Queries(" + std::to_string(queryVector.size()) + "):\n");
		for(int i = 0; i < (int)queryVector.size(); ++i) {
			outputString.append("  " + queryVector.at(i)->toString() + "?" + "\n");
		}
		// Domain
		outputString.append("Domain(" + std::to_string(domainSet.size()) + "):\n");
		for(auto each : domainSet) {
			outputString.append(each + "\n");
		}

		return outputString;
	}

	std::vector<Predicate*> getSchemeVector() {
		return schemeVector;
	}

	std::vector<Predicate*> getFactVector() {
		return factVector;
	}

	std::vector<Predicate*> getQueryVector() {
		return queryVector;
	}

private:
	std::vector<Predicate*> schemeVector;
	std::vector<Predicate*> factVector;
	std::vector<Predicate*> queryVector;
	std::vector<Rule*> ruleVector;
	std::set<std::string> domainSet;
};


#endif //PROJECT1_STARTER_CODE_DATALOGPROGRAM_H
