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
	std::vector<bool> visitedVector;
	// each int is a node, which maps to a set of adjacent nodes
	std::map<int, std::set<int>> dependencyGraph;
	std::map<int, std::set<int>> reverseDependencyGraph;
	// vector of SCC sets
	std::vector<std::set<int>> treeVector;
public:
	Graph(std::vector<Rule*> ruleVector);
	void buildDependencyGraphs();
	void addEmptyRule(int keyNode);
	void addAdjacentRule(int keyNode, int valueNode);
	int getIndexFromId(std::string id);

	std::vector<int> reverseVector(std::vector<int> vectorToReverse);

	std::vector<int> dfsf_ReturnsPostOrdering(std::vector<int> const& orderToSearchVector, std::map<int, std::set<int>>& graphToSearch);
	std::vector<int> dfs_ReturnsPostOrdering(int vertex, std::map<int, std::set<int>>& graphToSearch);
	void dfs_ReturnsPostOrdering_Helper(std::vector<int>& postorderVector, int vertex, std::map<int, std::set<int>>& graphToSearch);
	std::vector<std::set<int>> dfsf_ReturnsForest(std::vector<int> const& orderToSearchVector, std::map<int, std::set<int>>& graphToSearch);
	std::set<int> dfs_ReturnsSearchTree(int vertex, std::map<int, std::set<int>>& graphToSearch);
	void dfs_ReturnsSearchTree_Helper(std::set<int>& treeSet, int vertex, std::map<int, std::set<int>>& graphToSearch);

	std::string dependencyGraphToString();
	std::string reverseDependencyGraphToString();
	std::vector<std::set<int>> getSCCs();
	std::map<int, std::set<int>> getDependencyGraph();
};


#endif //PROJECT1_STARTER_CODE_GRAPH_H
