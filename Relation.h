//
// Created by austi_eef6ewn on 10/20/2022.
//

#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H

#include "Header.h"
#include "Tuple.h"
#include <set>


class Relation {
private:
	std::string name;
	Header* header;
	std::set<Tuple> rows;
public:
	Relation(std::string name, Header* header);
	void addTuple(Tuple tupleToAdd);
	void toString();
};


#endif //PROJECT1_STARTER_CODE_RELATION_H
