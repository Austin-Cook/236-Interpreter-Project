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

	// evaluate rules
	std::vector<Rule*> ruleVector = datalogProgram.getRuleVector();
	bool tuplesAdded = false;
	// fixed point algorithm
	// TODO add while loop for fixed point algorithm here
		// reset the variable(s) keeping track of if new tuples were added
		tuplesAdded = false;
		// evaluate all the rules
		for(int ruleIndex = 0; ruleIndex < int(ruleVector.size()); ruleIndex++) {
			// for each rule 'r'
			if(evaluateRule(*(ruleVector.at(ruleIndex))) == true) {
				tuplesAdded = true;
			}
		}
		// TODO repeat if new tuples were added

	// for each query 'q' - Run through select, project, and rename
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

	// (2) join the relations that result
	std::vector<Predicate*> bodyPredicates = rule.getBodyPredicatesVector();
	// take the relation of the first bodyPredicate and store it as result
	Relation* result = database.getRelationByName(bodyPredicates.at(0)->getId());
	for(int bodyPredicateIndex = 1; bodyPredicateIndex < bodyPredicates.size(); bodyPredicateIndex++) {
		// for bodyPredicates at index 1 and on, join: alpha - result with beta - relation corresponding to the bodyPredicate at bodyPredicateIndex
		result = join(result, database.getRelationByName(bodyPredicates.at(bodyPredicateIndex)->getId()));
	}
	// (3) project columns that appear in the head predicate

	// (4) rename the relation to make it union-compatible

	// (5) union the relation with the database

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

Relation* Interpreter::join(Relation* alpha, Relation* beta) {
	// for testing
	std::cout << "alpha.toString():" << std::endl;
	alpha->toString();
	std::cout << "beta.toString():" << std::endl;
	beta->toString();

	// combine headers
	Header* joinedHeader = combineHeaders(alpha->getHeader(), beta->getHeader());

	// for testing
	std::cout << "joinedHeader: ";
	for(int i = 0; i < joinedHeader->getNumAttributes(); i++) {
		std::cout << joinedHeader->getAttributeAtIndex(i) << ", ";
	}
	std::cout << std::endl;

	// get the tuples containing indexes from alpha and beta that match (alphaHeaderIndex, betaHeaderIndex)
	std::set<std::pair<int, int>> matchingHeaderColumns;
	for(int alphaHeaderIndex = 0; alphaHeaderIndex < alpha->getHeader()->getNumAttributes(); alphaHeaderIndex++) {
		for(int betaHeaderIndex = 0; betaHeaderIndex < beta->getHeader()->getNumAttributes(); betaHeaderIndex++) {
			if(alpha->getHeader()->getAttributeAtIndex(alphaHeaderIndex) == beta->getHeader()->getAttributeAtIndex(betaHeaderIndex)) {
				// If the columns match - create and insert new tuple
				matchingHeaderColumns.insert(std::pair<int, int> (alphaHeaderIndex, betaHeaderIndex));		//FIXME is this syntax correct?
			}
		}
	}

	// for testing
	std::cout << "matchingHeaderColumns: " << std::endl;
	for(auto eachPair : matchingHeaderColumns) {
		std::cout << "(" << eachPair.first << ", " << eachPair.second << ")" << std::endl;
	}


	// call isJoinable
	// combineTuples
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
