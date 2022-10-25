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
	for(int schemeIndex = 0; schemeIndex < schemeVector.size(); schemeIndex++) {
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
	for(int factIndex = 0; factIndex < factVector.size(); factIndex++) {
		// make a tuple 't' using the values form 'f'
		Tuple tuple;
		int numFacts = factVector.at(factIndex)->getParameterVector().size();
		for(int valueIndex = 0; valueIndex < numFacts; valueIndex++) {
			tuple.addValue(factVector.at(factIndex)->getParameterVector().at(valueIndex)->toString());
		}
		// add 't' to relation with the same name as 'f'
		database.addTupleToRelation(tuple, factVector.at(factIndex)->getId());
	}

	// for each query 'q' - Run through select, project, and rename
	std::vector<Predicate*> queryVector = datalogProgram.getQueryVector();
	for(int queryIndex = 0; queryIndex < queryVector.size(); queryIndex++) {
		evaluatePredicate(*(queryVector.at(queryIndex)));
	}
}

// A Predicate is a specific query
Relation* Interpreter::evaluatePredicate(const Predicate& p) {
	// get the relation 'r' with the same name as the query 'q'
	r = database.getRelationByName(p.getId());
	variableVector.clear();
	variableIndexVector.clear();
	int numMatches = 0;

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

			for(int i = 0; i < variableVector.size(); i++) {
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
	// print the resulting relation
	std::cout << p.getId() << "(";
	for(int i = 0; i < p.getParameterVector().size(); i++) {
		std::cout << p.getParameterVector().at(i)->toString();
		if(i < p.getParameterVector().size() - 1) {
			std::cout << ",";
		}
	}
	std::cout << ")? ";
	if(r->getRows().size() > 0) {
		std::cout << "Yes(" << r->getRows().size() << ")" << std::endl;
	} else {
		std::cout << "No" << std::endl;
	}
	r->toString();
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
	for(int i = 0; i < variableIndexVector.size(); i++) {
		newHeader->addAttribute(variableVector.at(i));
	}
	Relation* relationToReturn = new Relation(r->getName(), newHeader);
	// copy the tuples from the old relation to the new
	for(Tuple row : r->getRows()) {
		relationToReturn->addTuple(row);
	}

	return relationToReturn;
}