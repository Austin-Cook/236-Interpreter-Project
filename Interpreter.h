//
// Created by austi_eef6ewn on 10/20/2022.
//

#ifndef PROJECT1_STARTER_CODE_INTERPRETER_H
#define PROJECT1_STARTER_CODE_INTERPRETER_H

#include "DatalogProgram.h"
#include "Database.h"


class Interpreter {
public:
	Interpreter(DatalogProgram datalogProgram);
	Relation* evaluatePredicate(const Predicate& p);
	bool evaluateRule(const Rule& rule);
	// r is set as a temp relation in each iteration of evaluatePredicate() and is accessed by the select, project, and rename functions
	Relation* r;
	std::vector<std::string> variableVector;
	std::vector<int> variableIndexVector;
	Relation* select1(int position, std::string value);
	Relation* select2(int position1, int position2);
	Relation* project();
	Relation* rename();
	Relation* join(Relation* alpha, Relation* beta);
	Header* combineHeaders(Header* alphaHeader, Header* betaHeader);
//	bool isJoinable();
//	Tuple combineTuples();
private:
	Database database;
};


#endif //PROJECT1_STARTER_CODE_INTERPRETER_H
