//
// Created by austi_eef6ewn on 11/19/2022.
//

#include "Graph.h"
#include <stack>

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

	// run dfsf on reverse dependency graph using order of low to high number
	std::vector<int> orderForFirstDFSF;	// Should be index 0 counting up to n-1
	for(int i = 0; i < ruleVector.size(); i++) {
		orderForFirstDFSF.push_back(i);
	}
	std::vector<int> postOrderVector = dfsf_ReturnsPostOrdering(orderForFirstDFSF, reverseDependencyGraph);

	// reverse the postOrder
	std::vector<int> reversedPostOrderVector = reverseVector(postOrderVector);

	// run dfsf on forward dependency graph using
	std::set<std::set<int>> forestSet = dfsf_ReturnsForest(reversedPostOrderVector, dependencyGraph);

	// FIXME DELETEME
	std::cout << "postorderVector:" << std::endl;	// FIXME DELETME
	for(int i = 0; i < postOrderVector.size(); i++) {
		std::cout << postOrderVector.at(i);
		if(i < postOrderVector.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << std::endl;

	std::cout << "reversedPostOrderVector:" << std::endl; // FIXME DELETEME
	for(int i = 0; i < reversedPostOrderVector.size(); i++) {
		std::cout << reversedPostOrderVector.at(i);
		if(i < reversedPostOrderVector.size() - 1) {
			std::cout << ", ";
		}
	}
	std::cout << std::endl;

	std::cout << "Forest:" << std::endl;
	int tempNum = 0;
	for(auto tree : forestSet) {
		std::cout << "SCC" << tempNum << ": ";
		for(auto component : tree) {
			std::cout << std::to_string(component) << ", ";
		}
		std::cout << std::endl;
		tempNum++;
	}
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

std::vector<int> Graph::reverseVector(std::vector<int> vectorToReverse) {
	std::stack<int> tempStack;
	std::vector<int> reversedVector;
	for(int i = 0; i < vectorToReverse.size(); i++) {
		tempStack.push(vectorToReverse.at(i));
	}
	while(!tempStack.empty()) {
		reversedVector.push_back(tempStack.top());
		tempStack.pop();
	}

	return reversedVector;
}

std::vector<int> Graph::dfsf_ReturnsPostOrdering(std::vector<int> const& orderToSearchVector, std::map<int, std::set<int>>& graphToSearch){
	std::vector<int> postOrderVector;
	// clear visited vector
	visitedVector.clear();
	for(int i = 0; i < ruleVector.size(); i++) {
		visitedVector.push_back(false);
	}

	// for each vertex in orderToSearchVector
	for(int vertexIndex = 0; vertexIndex < orderToSearchVector.size(); vertexIndex++) {
		// if it has NOT been visited
		if(visitedVector.at(orderToSearchVector.at(vertexIndex)) == false) {
			std::vector<int> postOrderVectorFromOneTree = dfs_ReturnsPostOrdering(vertexIndex, graphToSearch);
			// add these items to postOrderVector();
			for(int i = 0; i < postOrderVectorFromOneTree.size(); i++) {
				postOrderVector.push_back(postOrderVectorFromOneTree.at(i));
			}
		}
	}

	return postOrderVector;
}
std::vector<int> Graph::dfs_ReturnsPostOrdering(int vertex, std::map<int, std::set<int>>& graphToSearch) {
	std::vector<int> postOrderVector;
	dfs_ReturnsPostOrdering_Helper(postOrderVector, vertex, graphToSearch);
	return postOrderVector;
}
// Recursive helper function
void Graph::dfs_ReturnsPostOrdering_Helper(std::vector<int>& postOrderVector, int vertex, std::map<int, std::set<int>>& graphToSearch) {
	// mark vertex
	visitedVector.at(vertex) = true;
	//for each vertex adjacent from vertex
	for(auto adjacentVertex : graphToSearch[vertex]) {
		//if adjacentVertex is not marked
		if(visitedVector.at(adjacentVertex) == false) {
			dfs_ReturnsPostOrdering_Helper(postOrderVector, adjacentVertex, graphToSearch); // FIXME Set this = to an object of the post ordering that is returned
		}
	}

	// postorder append before popping vertex off stack
	postOrderVector.push_back(vertex);
}

std::set<std::set<int>> Graph::dfsf_ReturnsForest(std::vector<int> const& orderToSearchVector, std::map<int, std::set<int>>& graphToSearch) {
	std::set<std::set<int>> SCCSets;

	// calls the helper
	// clear visited vector
	visitedVector.clear();
	for(int i = 0; i < ruleVector.size(); i++) {
		visitedVector.push_back(false);
	}

	// for each vertex in orderToSearchVector
	for(int vertexIndex = 0; vertexIndex < orderToSearchVector.size(); vertexIndex++) {
		// if it has NOT been visited
		if(visitedVector.at(orderToSearchVector.at(vertexIndex)) == false) {
			std::cout << "Starting new tree with: " << vertexIndex << std::endl;
			SCCSets.insert(dfs_ReturnsSearchTree(orderToSearchVector.at(vertexIndex), graphToSearch));
		}
	}

	return SCCSets;
}
std::set<int> Graph::dfs_ReturnsSearchTree(int vertex, std::map<int, std::set<int>>& graphToSearch) {
	std::set<int> searchTreeSet;
	dfs_ReturnsSearchTree_Helper(searchTreeSet, vertex, graphToSearch);

	return searchTreeSet;
}
// Recursive helper function
void Graph::dfs_ReturnsSearchTree_Helper(std::set<int>& treeSet, int vertex, std::map<int, std::set<int>>& graphToSearch) {
	// mark vertex
	visitedVector.at(vertex) = true;
	//for each vertex adjacent from vertex
	for(auto adjacentVertex : graphToSearch[vertex]) {
		//if adjacentVertex is not marked
		if(visitedVector.at(adjacentVertex) == false) {
			dfs_ReturnsSearchTree_Helper(treeSet, adjacentVertex, graphToSearch);
		}
	}

	// searchTree insert before popping vertex off stack
	treeSet.insert(vertex);
	std::cout << "Inserting at: " << std::to_string(vertex) << std::endl;
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