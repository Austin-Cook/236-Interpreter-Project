//
// Created by austi_eef6ewn on 10/20/2022.
//

#include "Interpreter.h"
#include <vector>

// Create the Relations Here
Interpreter::Interpreter(DatalogProgram datalogProgram) {
	/* Note schemeVector*, factVector*, ruleVector*, and queryVector* each contain:
	   predicates - a string Id, and a vector<Parameter*>
	   Parameters are strings accessed by Parameter->toString() */

	// for each scheme 's'
	std::vector<Predicate*> schemeVector = datalogProgram.getSchemeVector();
	for(int schemeIndex = 0; schemeIndex < int(schemeVector.size()); schemeIndex++) {
		// create a relation using name and parameter values from 's'
		Header* header = new Header;
		// Create the header
		int numSchemes = schemeVector.at(schemeIndex)->getParameterVector().size();
		for(int attributeIndex = 0; attributeIndex < numSchemes; attributeIndex++) {
			header->addAttribute(schemeVector.at(schemeIndex)->getParameterVector().at(attributeIndex)->toString());
		}
		database.addRelation(schemeVector.at(schemeIndex)->getId(), header);
	}

	// for each fact 'f'
	std::vector<Predicate*> factVector = datalogProgram.getFactVector();
	for(int factIndex = 0; factIndex < int(factVector.size()); factIndex++) {
		// make a tuple 't' using the values form 'f'
		Tuple tuple;
		int numFacts = factVector.at(factIndex)->getParameterVector().size();
		for(int valueIndex = 0; valueIndex < numFacts; valueIndex++) {
			tuple.addValue(factVector.at(factIndex)->getParameterVector().at(valueIndex)->toString());
		}
		// add 't' to relation with the same name as 'f'
		database.addTupleToRelation(tuple, factVector.at(factIndex)->getId());
	}

	// for each rule 'rule'
	std::cout << "Rule Evaluation" << std::endl;
	std::vector<Rule*> ruleVector = datalogProgram.getRuleVector();
	bool tuplesAdded = true;
	int timesLooped = 0;
	// fixed point algorithm
	while(tuplesAdded == true) {
		// reset the variable(s) keeping track of if new tuples were added
		tuplesAdded = false;
		// evaluate all the rules
		for (int ruleIndex = 0; ruleIndex < int(ruleVector.size()); ruleIndex++) {
			// for each rule 'r'
			if (evaluateRule(*(ruleVector.at(ruleIndex))) == true) {
				tuplesAdded = true;
			}
		}
		timesLooped++;
	}
	std::cout << std::endl << "Schemes populated after " << timesLooped << " passes through the Rules." << std::endl << std::endl;


	// for each query 'q' - Run through select, project, and rename
	std::cout << "Query Evaluation" << std::endl;
	std::vector<Predicate*> queryVector = datalogProgram.getQueryVector();
	for(int queryIndex = 0; queryIndex < int(queryVector.size()); queryIndex++) {
		Relation* resultingRelation = evaluatePredicate(*(queryVector.at(queryIndex)));
		// print the resulting relation in specified format
		std::cout << queryVector.at(queryIndex)->getId() << "(";
		for(int i = 0; i < int(queryVector.at(queryIndex)->getParameterVector().size()); i++) {
			std::cout << queryVector.at(queryIndex)->getParameterVector().at(i)->toString();
			if(i < int(queryVector.at(queryIndex)->getParameterVector().size()) - 1) {
				std::cout << ",";
			}
		}
		std::cout << ")? ";
		if(resultingRelation->getRows().size() > 0) {
			std::cout << "Yes(" << resultingRelation->getRows().size() << ")" << std::endl;
		} else {
			std::cout << "No" << std::endl;
		}
		resultingRelation->toString();
	}
}

// A Predicate is a specific query
Relation* Interpreter::evaluatePredicate(const Predicate& p) {
	// get the relation 'r' with the same name as the query 'q'
	r = database.getRelationByName(p.getId());
	variableVector.clear();
	variableIndexVector.clear();

	// for each parameter in the query
	int numParameters = p.getParameterVector().size();
	for(int paramIndex = 0; paramIndex < numParameters; paramIndex++) {
		// select for each constant (string) in the query 'q'
		if(p.getParameterVector().at(paramIndex)->isConstant()) {
			// Do type 1 selection (For constants - 'strings')
			r = select1(paramIndex, p.getParameterVector().at(paramIndex)->toString());
		} else {
			// if we have seen it before
			int indexFoundAt = -1;

			for(int i = 0; i < int(variableVector.size()); i++) {
				// check if we have seen the variable before
				if(variableVector.at(i) == p.getParameterVector().at(paramIndex)->toString()) {
					indexFoundAt = i;
				}
			}
			if(indexFoundAt != -1) {	// We have seen it before
				// do type 2 selection ()
				r = select2(indexFoundAt, paramIndex);
			} else {
				// mark it to keep for the project and rename
				variableVector.push_back(p.getParameterVector().at(paramIndex)->toString());
				variableIndexVector.push_back(paramIndex);
			}
		}
	}
	// project using the positions of the variables in 'q'
	r = project();
	// rename to match the names of variables in 'q'
	r = rename();

	return r;
}

bool Interpreter::evaluateRule(const Rule& rule) {		// * r  is an instance data member Relation*
	// (1) evaluatePredicate (same as for queries)
	std::vector<Predicate*> bodyPredicates = rule.getBodyPredicatesVector();
	std::vector<Relation*> relationsFromBodyPredicates;
	for(int i = 0; i < bodyPredicates.size(); i++) {
		relationsFromBodyPredicates.push_back(evaluatePredicate(*(bodyPredicates.at(i))));
	}


	// (2) join the relations that result
	// take the relation of the first bodyPredicate and store it as result
	Relation* result = relationsFromBodyPredicates.at(0);
	for(int bodyPredicateIndex = 1; bodyPredicateIndex < bodyPredicates.size(); bodyPredicateIndex++) {
		// for relationsFromBodyPredicates at index 1 and on, join: alpha - result with beta - relation corresponding to the bodyPredicate at bodyPredicateIndex
		result = join(result, relationsFromBodyPredicates.at(bodyPredicateIndex), rule.getHeadPredicate()->getId());
	}
//	std::cout << "New relation after joining: " << std::endl;
//	result->toString();


	// (3) project columns that appear in the head predicate
	r = result;
	variableIndexVector.clear();
	variableVector.clear();

	// get indexes to project, and corresponding names for rename
	// for each parameter in the rule's head predicate
	for(int paramIndex = 0; paramIndex < rule.getHeadPredicate()->getParameterVector().size(); paramIndex++) {
		// for each header attribute in the resulting relation
		bool found = false;
		for(int headerIndex = 0; headerIndex < r->getHeader()->getNumAttributes(); headerIndex++) {
			// if the param in the headPredicate == the attribute name in the new relation header
			if(rule.getHeadPredicate()->getParameterVector().at(paramIndex)->toString() == r->getHeader()->getAttributeAtIndex(headerIndex)) {
				found = true;
//				std::cout << "paramIndex: " << paramIndex << std::endl;
//				std::cout << "headerIndex: " << headerIndex << std::endl;
				variableIndexVector.push_back(headerIndex);
				variableVector.push_back(database.getRelationByName(rule.getHeadPredicate()->getId())->getHeader()->getAttributeAtIndex(paramIndex));
			}
		}
		if(found == false) {
			std::cerr << "Error! - in part 3 (project) of evaluateRule(). The attribute: " << rule.getHeadPredicate()->getParameterVector().at(paramIndex)->toString() << " in the head predicate was not found in the resulting relation" <<std::endl;
		}
	}

	result = project();
//	std::cout << "Tuples in result after reject - " << std::endl;
//	for(auto tuple : result->getRows()) {
//		tuple.toString();
//	}

//	std::cout << "result after projecting: " << std::endl;
//	result->toString();


	// (4) rename the relation to make it union-compatible

//	// for testing
//	std::cout << "Header before renaming: " << std::endl;
//	for(int i = 0; i < result->getHeader()->getNumAttributes(); i++) {
//		std::cout << result->getHeader()->getAttributeAtIndex(i) << ", ";
//	}
//	std::cout << std::endl;

	r = result;
	result = rename();
//	std::cout << "Tuples in result after rename - " << std::endl;
//	for(auto tuple : result->getRows()) {
//		tuple.toString();
//	}

//	std::cout << "Header after renaming: " << std::endl;
//	for(int i = 0; i < result->getHeader()->getNumAttributes(); i++) {
//		std::cout << result->getHeader()->getAttributeAtIndex(i) << ", ";
//	}
//	std::cout << std::endl;


	// (5) union the relation with the database
	bool changed = false;
	r = database.getRelationByName(rule.getHeadPredicate()->getId());
//	std::cout << "Printing tuples in result - " << std::endl;
	std::cout << rule.toString() << std::endl;
	for(auto tuple : result->getRows()) {
		if(r->addTuple_ReturnBool(tuple)) {
			changed = true;
			// Print an added tuple
			if(tuple.getNumValues() != r->getHeader()->getNumAttributes()) {
				std::cerr << "ERROR (in Interpreter.cpp): Number of values in tuple != Number of header attributes!" << std::endl << "A Relation is being created with an inconsistent number of values in a tuple";
				exit(1);
			} else {
				if(r->getHeader()->getNumAttributes() > 0) {
					std::cout << "  ";
					for(int i = 0; i < r->getHeader()->getNumAttributes(); i++) {
						std::cout << r->getHeader()->getAttributeAtIndex(i) << "=" << tuple.getValueAtIndex(i);
						if(i < r->getHeader()->getNumAttributes() - 1) {
							std::cout << ", ";
						}
					}
					std::cout << std::endl;
				}
			}
		}
	}

//	// for testing
//	if(changed) {
//		std::cout << "It was changed!" << std::endl;
//	} else {
//		std::cout << "Nothing changed" << std::endl;
//	}
//	database.getRelationByName(rule.getHeadPredicate()->getId())->toString();

	return changed;
}

Relation* Interpreter::select1(int position, std::string value) {
	Relation* relationToReturn = new Relation(r->getName(), r->getHeader());
	std::set<Tuple> oldRows = r->getRows();
	for(Tuple row : oldRows) {
		// if a row contains the same value at the same index as the one being searched for
		if(row.getValueAtIndex(position) == value) {
			// add it to the newRelation
			relationToReturn->addTuple(row);
		}
	}
	return relationToReturn;
}

Relation* Interpreter::select2(int position1, int position2) {
	Relation* relationToReturn = new Relation(r->getName(), r->getHeader());
	std::set<Tuple> oldRows = r->getRows();
	for(Tuple row : oldRows) {
		// if the row at both positions contain the same value
		if(row.getValueAtIndex(position1) == row.getValueAtIndex(position2)) {
			// add it to the newRelation
			relationToReturn->addTuple(row);
		}
	}
	return relationToReturn;
}

Relation* Interpreter::project() {
	std::set<Tuple> oldRows = r->getRows();
	Header* newHeader = new Header;

	for(int colIndex : variableIndexVector) {
		// add selected attribute from old header to new
		newHeader->addAttribute(r->getHeader()->getAttributeAtIndex(colIndex));
	}
	Relation* relationToReturn = new Relation(r->getName(), newHeader);

	for(Tuple row : r->getRows()) {
		// for each tuple in the old relation
		// create a new tuple
		Tuple newTuple;
		for(int colIndex : variableIndexVector) {
			// add selected value from old row to new
			newTuple.addValue(row.getValueAtIndex(colIndex));
		}
		relationToReturn->addTuple(newTuple);
	}
	return relationToReturn;
}

Relation* Interpreter::rename() {
	std::set<Tuple> oldRows = r->getRows();
	Header* newHeader = new Header;

	// create the header with new names
	for(int i = 0; i < int(variableIndexVector.size()); i++) {
		newHeader->addAttribute(variableVector.at(i));
	}
	Relation* relationToReturn = new Relation(r->getName(), newHeader);
	// copy the tuples from the old relation to the new
	for(Tuple row : r->getRows()) {
		relationToReturn->addTuple(row);
	}

	return relationToReturn;
}

Relation* Interpreter::join(Relation* alpha, Relation* beta, std::string newRelationName) {
//	// for testing
//	std::cout << "alpha.toString():" << std::endl;
//	alpha->toString();
//	std::cout << "beta.toString():" << std::endl;
//	beta->toString();

	// combine headers
	Header* joinedHeader = combineHeaders(alpha->getHeader(), beta->getHeader());

	// create the new relation
	Relation* joinedRelation = new Relation(newRelationName, joinedHeader);

//	// for testing
//	std::cout << "joinedHeader: ";
//	for(int i = 0; i < joinedHeader->getNumAttributes(); i++) {
//		std::cout << joinedHeader->getAttributeAtIndex(i) << ", ";
//	}
//	std::cout << std::endl;

	// get the tuples containing indexes from alpha and beta that match (alphaHeaderIndex, betaHeaderIndex)
	matchingHeaderColumns.clear();
	for(int alphaHeaderIndex = 0; alphaHeaderIndex < alpha->getHeader()->getNumAttributes(); alphaHeaderIndex++) {
		for(int betaHeaderIndex = 0; betaHeaderIndex < beta->getHeader()->getNumAttributes(); betaHeaderIndex++) {
			if(alpha->getHeader()->getAttributeAtIndex(alphaHeaderIndex) == beta->getHeader()->getAttributeAtIndex(betaHeaderIndex)) {
				// If the columns match - create and insert new tuple
				matchingHeaderColumns.insert(std::pair<int, int> (alphaHeaderIndex, betaHeaderIndex));
			}
		}
	}

//	// for testing
//	std::cout << "matchingHeaderColumns: " << std::endl;
//	for(auto eachPair : matchingHeaderColumns) {
//		std::cout << "(" << eachPair.first << ", " << eachPair.second << ")" << std::endl;
//	}

	// for every combination of tuples in alpha and beta
	for(auto alphaTuple : alpha->getRows()) {
		for(auto betaTuple : beta->getRows()) {
			if(isJoinable(alphaTuple, betaTuple)) {
				Tuple joinedTuple = combineTuples(alphaTuple, betaTuple);
				joinedRelation->addTuple(joinedTuple);
			}
		}
	}

	return joinedRelation;
}

Header* Interpreter::combineHeaders(Header* alphaHeader, Header* betaHeader) {
	Header* joinedHeader = new Header;
	// add each attribute from alphaHeader
	for(int i = 0; i < alphaHeader->getNumAttributes(); i++) {
		joinedHeader->addAttribute(alphaHeader->getAttributeAtIndex(i));
	}
	// add unique elements from betaHeader
	for(int i = 0; i < betaHeader->getNumAttributes(); i++) {
		// if the attribute isn't in alphaHeader - add it to joinedHeader
		if(!alphaHeader->containsAttribute(betaHeader->getAttributeAtIndex(i))) {
			joinedHeader->addAttribute(betaHeader->getAttributeAtIndex(i));
		}
	}

	return joinedHeader;
}

bool Interpreter::isJoinable(Tuple alpha, Tuple beta) {
	bool canJoin = true;
	//for each pair of matchingHeaderColumns indexes
	for(auto eachPair : matchingHeaderColumns) {
		if(alpha.getValueAtIndex(eachPair.first) != beta.getValueAtIndex(eachPair.second)) {
			canJoin = false;
		}
	}

	return canJoin;
}

Tuple Interpreter::combineTuples(Tuple alpha, Tuple beta) {
	Tuple combinedTuple;

	// first, add all elements from alpha
	for(int valueIndex = 0; valueIndex < alpha.getNumValues(); valueIndex++) {
		combinedTuple.addValue(alpha.getValueAtIndex(valueIndex));
	}

	// second add tuples from the beta that are not in alpha
	// grab indexes of beta that have already been added
	std::vector<int> betaIndexesToNotAdd;
	for(auto eachPair : matchingHeaderColumns) {
		betaIndexesToNotAdd.push_back(eachPair.second);
	}
	for(int valueIndex = 0; valueIndex < beta.getNumValues(); valueIndex++) {
		bool inVector = false;
		for(int i = 0; i < betaIndexesToNotAdd.size(); i++) {
			if(valueIndex == betaIndexesToNotAdd.at(i)) {
				inVector = true;
			}
		}
		if(!inVector) {
			combinedTuple.addValue(beta.getValueAtIndex(valueIndex));
		}
	}

	return combinedTuple;
}
