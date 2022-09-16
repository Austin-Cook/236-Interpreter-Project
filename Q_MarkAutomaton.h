//
// Created by austi_eef6ewn on 9/15/2022.
//

#ifndef PROJECT1_STARTER_CODE_Q_MARKAUTOMATON_H
#define PROJECT1_STARTER_CODE_Q_MARKAUTOMATON_H

#include "Automaton.h"

class Q_MarkAutomaton : public Automaton
{
public:
	Q_MarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

	void S0(const std::string& input) {
		if (input[index] == '?') {
			inputRead = 1;
		} else {
			Serr();
		}
	}
};

#endif //PROJECT1_STARTER_CODE_Q_MARKAUTOMATON_H
