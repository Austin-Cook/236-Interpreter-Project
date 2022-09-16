//
// Created by austi_eef6ewn on 9/15/2022.
//

#ifndef PROJECT1_STARTER_CODE_RIGHT_PARENAUTOMATON_H
#define PROJECT1_STARTER_CODE_RIGHT_PARENAUTOMATON_H

#include "Automaton.h"

class Right_ParenAutomaton : public Automaton
{
public:
	Right_ParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

	void S0(const std::string& input) {
		if (input[index] == ')') {
			inputRead = 1;
		} else {
			Serr();
		}
	}
};

#endif //PROJECT1_STARTER_CODE_RIGHT_PARENAUTOMATON_H
