//
// Created by austi_eef6ewn on 11/19/2022.
//

#ifndef PROJECT1_STARTER_CODE_GRAPH_H
#define PROJECT1_STARTER_CODE_GRAPH_H

#include <map>
#include <set>
#include "Rule.h"
#include "Node.h"

class Graph {
private:
	std::vector<Rule*> ruleVector;
	// contains the name of each node, and a pointer to the node
	std::map<std::string, int> idIndexMap;
	// each int is a node, which maps to a set of adjacent nodes
	std::map<int, std::set<int>> dependencyGraph;
	std::map<int, std::set<int>> reverseDependencyGraph;
public:
	Graph(std::vector<Rule*> ruleVector);
	void buildDependencyGraphs();
	void addEmptyRule(int keyNode);
	// adds adjacent node to both dependency and reverse dependency graphs
	void addAdjacentRule(int keyNode, int valueNode);
	std::string dependencyGraphToString();
	std::string reverseDependencyGraphToString();
	int getIndexFromId(std::string id);
};


#endif //PROJECT1_STARTER_CODE_GRAPH_H
