//
// Created by austi_eef6ewn on 9/15/2022.
//

#ifndef PROJECT1_STARTER_CODE_ADDAUTOMATON_H
#define PROJECT1_STARTER_CODE_ADDAUTOMATON_H

#include "Automaton.h"

class AddAutomaton : public Automaton
{
public:
	AddAutomaton() : Automaton(TokenType::ADD) {}  // Call the base constructor

	void S0(const std::string& input) {
		if (input[index] == '+') {
			inputRead = 1;
		} else {
			Serr();
		}
	}
};

#endif //PROJECT1_STARTER_CODE_ADDAUTOMATON_H
