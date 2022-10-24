//
// Created by austi_eef6ewn on 10/20/2022.
//

#ifndef PROJECT1_STARTER_CODE_RELATION_H
#define PROJECT1_STARTER_CODE_RELATION_H

#include "Header.h"
#include "Tuple.h"
#include <set>


class Relation {
public:
	Relation(std::string name, Header* header);
	void addTuple(Tuple tuple);
	void toString();
	std::string getName() const;
	Header* getHeader() const;
	std::set<Tuple> getRows() const;
private:
	std::string name;
	Header* header;
	std::set<Tuple> rows;
};


#endif //PROJECT1_STARTER_CODE_RELATION_H
