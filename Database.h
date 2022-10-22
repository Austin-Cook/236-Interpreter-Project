//
// Created by austi_eef6ewn on 10/20/2022.
//

#ifndef PROJECT1_STARTER_CODE_DATABASE_H
#define PROJECT1_STARTER_CODE_DATABASE_H

#include <map>
#include "Relation.h"
#include "Header.h"		// Only here for testing
#include "Tuple.h"		// Only here for testing

class Database {
public:
	Database();
	void addRelation(std::string name, Header* header);
	void addTupleToRelation(Tuple tuple, std::string name);
	void printRelationByName(std::string name);
	void testDatabaseClasses();
private:
	std::map<std::string, Relation*> relationMap;
};


#endif //PROJECT1_STARTER_CODE_DATABASE_H
