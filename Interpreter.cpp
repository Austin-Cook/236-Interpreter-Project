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

	// FIXME DELETEME
	//database.printRelationByName("snap");

	// for each query 'q' - Run through select, project, and rename
	std::vector<Predicate*> queryVector = datalogProgram.getQueryVector();
	for(int queryIndex = 0; queryIndex < queryVector.size(); queryIndex++) {
		evaluatePredicate(*(queryVector.at(queryIndex)));		//FIXME is this right? Pass dereferenced pointer as reference
	}
}

// A Predicate is a specific query
Relation* Interpreter::evaluatePredicate(const Predicate& p) {
	// get the relation 'r' with the same name as the query 'q'
	Relation* r = database.getRelationByName(p.getId());

	// for each parameter in the query
	int numParameters = p.getParameterVector().size();
	for(int paramIndex = 0; paramIndex < numParameters; paramIndex++) {
		// select for each constant (string) in the query 'q'
		if(p.getParameterVector().at(paramIndex)->isConstant()) {
			// Do type 1 selection (For constants - 'strings')
			Relation* newRelation = new Relation(r->getName(), r->getHeader()); //FIXME CAREFUL THAT THE HEADER IS NEVER MODIFIED
			std::set<Tuple> oldRows = r->getRows();
			for(Tuple row : oldRows) {
				// if a row contains the same value at the same index as the one being searched for
				if(row.getValueAtIndex(paramIndex) == p.getParameterVector().at(paramIndex)->toString()) {
					// add it to the newRelation
					newRelation->addTuple(row);
				}
			}
		} else {
			// if we have seen it before
			// do type 2 selection ()
			// else
			// mark it to keep for the project and rename
		}

	}
	// select type 2 - for each pair of matching variables in 'q'
	// project using the positions of the variables in 'q'
	// rename to match the names of variables in 'q'
	// print the resulting relation
}
