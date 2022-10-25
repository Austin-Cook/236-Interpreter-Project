//
// Created by austi_eef6ewn on 10/20/2022.
//

#ifndef PROJECT1_STARTER_CODE_TUPLE_H
#define PROJECT1_STARTER_CODE_TUPLE_H

#include "iostream"
#include <vector>
#include <string>


class Tuple {
private:
	std::vector<std::string> values;
public:
	bool operator< (const Tuple &rhs) const {
		return values < rhs.values;
	}
	void addValue(std::string value) {
		values.push_back(value);
	}
	std::string getValueAtIndex(int index) {
		return values.at(index);
	}
	int getNumValues() {
		return values.size();
	}
	void toString() {
		std::cout << "Tuple: ";
		for(int i = 0; i < int(values.size()); i++) {
			std::cout << values.at(i);
			if(i < int(values.size()) - 1) {
				std::cout << ", ";
			}
		}
		std::cout << std::endl;
	}
};


#endif //PROJECT1_STARTER_CODE_TUPLE_H
