//
// Created by austi_eef6ewn on 11/19/2022.
//

#include "Graph.h"

Graph::Graph(std::vector<Rule*> const ruleVector) {
	// copy ruleVector and build idIndexMap
	std::cout << "idIndexMap values:" << std::endl; // FIXME DELETEME
	for(int ruleIndex = 0; ruleIndex < ruleVector.size(); ruleIndex++) {
		this->ruleVector.push_back(ruleVector.at(ruleIndex));
		idIndexMap[ruleVector.at(ruleIndex)->getHeadPredicate()->getId()] = ruleIndex;

		// FIXME DELETEME
		std::cout << "Rule index: " << std::to_string(ruleIndex) << ", Id at the index: " << ruleVector.at(ruleIndex)->getHeadPredicate()->getId() << std::endl;
	}
	std::cout << std::endl; // FIXME DELETEME

	buildDependencyGraphs();
}

void Graph::buildDependencyGraphs() {
	// for each rule/node
	for(int ruleIndex = 0; ruleIndex < ruleVector.size(); ruleIndex++) {
		// add the rule as a valid key (in case there are no adjacent nodes, the rule still must show up as a key
		addEmptyRule(ruleIndex);
	}

	// for each left rule
	for(int leftRuleIndex = 0; leftRuleIndex < ruleVector.size(); leftRuleIndex++) {
		// for each right rule corresponding to the left rule
		for(int rightRuleIndex = 0; rightRuleIndex < ruleVector.at(leftRuleIndex)->getBodyPredicatesVector().size(); rightRuleIndex++) {
			std::string rightRuleId = ruleVector.at(leftRuleIndex)->getBodyPredicatesVector().at(rightRuleIndex)->getId();
			// for all left rules
			for(int eachLeftRuleIndex = 0; eachLeftRuleIndex < ruleVector.size(); eachLeftRuleIndex++) {
				// if that left rule id is == to the right rule in 2nd for loop
				if(getIndexFromId(rightRuleId) == getIndexFromId(ruleVector.at(eachLeftRuleIndex)->getHeadPredicate()->getId())) {
					addAdjacentRule(leftRuleIndex, eachLeftRuleIndex);
				}
			}
		}
	}
}

void Graph::addEmptyRule(int keyNode) {
	dependencyGraph[keyNode];
	reverseDependencyGraph[keyNode];
}

void Graph::addAdjacentRule(int keyNode, int valueNode) {
	dependencyGraph[keyNode].insert(valueNode);
	reverseDependencyGraph[valueNode].insert(keyNode);
}

std::string Graph::dependencyGraphToString() {
	std::string stringToReturn = "";
	// for each rule
	for(auto rule : dependencyGraph) {
		stringToReturn += std::to_string(rule.first) + ": ";
		// for each adjacent rule
		for(auto adjacentRule : rule.second) {
			stringToReturn += std::to_string(adjacentRule) + ", ";
		}
		stringToReturn += "\n";
	}

	return stringToReturn;
}

std::string Graph::reverseDependencyGraphToString() {
	std::string stringToReturn = "";
	// for each rule
	for(auto rule : reverseDependencyGraph) {
		stringToReturn += std::to_string(rule.first) + ": ";
		// for each adjacent rule
		for(auto adjacentRule : rule.second) {
			stringToReturn += std::to_string(adjacentRule) + ", ";
		}
		stringToReturn += "\n";
	}

	return stringToReturn;
}

// Returns -1 if the ID does not exist in the graph of rules
// - meaning it is not a dependency and DO NOT ADD IT
int Graph::getIndexFromId(std::string id) {
	int indexToReturn = -1;

	auto foundIterator = idIndexMap.find(id);
	if(foundIterator != idIndexMap.end()) {
		indexToReturn = foundIterator->second;
	}

	return indexToReturn;
}

