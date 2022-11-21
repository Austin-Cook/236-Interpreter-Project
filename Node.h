//
// Created by austi_eef6ewn on 11/19/2022.
//

#ifndef PROJECT1_STARTER_CODE_NODE_H
#define PROJECT1_STARTER_CODE_NODE_H

#include <string>
#include <set>

class Node {
private:
	int nodeNumber;
	std::set<int> adjacentNodeSet;
public:
	Node(int nodeNumber) {
		this->nodeNumber = nodeNumber;
	}

	void insertAdjacentNode(int node) {
		adjacentNodeSet.insert(node);
	}

	std::string toString() {
		std::string stringToReturn = std::to_string(nodeNumber) + ": ";
		for(auto adjacentNode : adjacentNodeSet) {
			stringToReturn += std::to_string(adjacentNode) + ", ";
		}

		return stringToReturn;
	}

	int getNodeNumber() {
		return nodeNumber;
	}
};


#endif //PROJECT1_STARTER_CODE_NODE_H
