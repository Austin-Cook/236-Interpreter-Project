//
// Created by austi_eef6ewn on 10/20/2022.
//

#include <iostream>
#include "Relation.h"

Relation::Relation(std::string name, Header* header) {
	this->name = name;
	this->header = header;
}

void Relation::addTuple(Tuple tuple) {
	rows.insert(tuple);
}

void Relation::toString() {
	for (Tuple row : rows) {
		if(row.getNumValues() != header->getNumAttributes()) {
			std::cerr << "ERROR (in Relation.cpp): Number of values in tuple != Number of header attributes!" << std::endl << "A Relation is being created with an inconsistent number of values in a tuple";
			exit(0);
		} else {
			for (int i = 0; i < header->getNumAttributes(); i++) {
				std::cout << header->getAttributeAtIndex(i) << "=" << row.getValueAtIndex(i);
				if(i < header->getNumAttributes() - 1) {
					std::cout << ", ";
				}
			}
			std::cout << std::endl;
		}
	}
}