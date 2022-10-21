//
// Created by austi_eef6ewn on 10/20/2022.
//

#ifndef PROJECT1_STARTER_CODE_HEADER_H
#define PROJECT1_STARTER_CODE_HEADER_H

#include <vector>
#include <string>


class Header {
private:
	std::vector<std::string> attributes;
public:
	void addAttribute(std::string attribute) {
		attributes.push_back(attribute);
	}

	int getNumAttributes() {
		return attributes.size();
	}

	std::string getAttributeAtIndex(int index) {
		return attributes.at(index);
	}
};


#endif //PROJECT1_STARTER_CODE_HEADER_H
