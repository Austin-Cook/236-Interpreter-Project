//
// Created by austi_eef6ewn on 9/15/2022.
//

#ifndef PROJECT1_STARTER_CODE_IDAUTOMATON_H
#define PROJECT1_STARTER_CODE_IDAUTOMATON_H


#include "Automaton.h"

class IdAutomaton : public Automaton {
public:
	IdAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

	void S0(const std::string &input) {
		if (isalpha(input[index])) {
			inputRead++;
			index++;
			S1(input);
		} else {
			Serr();
		}
	}

	void S1(const std::string &input) {
		if (isalnum(input[index])) {
			inputRead++;
			index++;
			//Call itself
			S1(input);
		}
		//Call function to verify if string is a keyword
		S2(input);
	}

	//Checks if input string is a keyword "Schemes, Facts, Rules, or Queries
	void S2(const std::string &input) {
		if((input.substr(0, inputRead) == "Schemes") || (input.substr(0, inputRead) == "Facts") || (input.substr(0, inputRead) == "Rules") || (input.substr(0, inputRead) == "Queries")) {
			Serr();
		}
	}
};

#endif //PROJECT1_STARTER_CODE_IDAUTOMATON_H
