//
// Created by austi_eef6ewn on 9/16/2022.
//

#ifndef PROJECT1_STARTER_CODE_EOFAUTOMATON_H
#define PROJECT1_STARTER_CODE_EOFAUTOMATON_H
#include "Automaton.h"

class EOFAutomaton : public Automaton
{
public:
	EOFAutomaton() : Automaton(TokenType::EOF_TOKEN) {}  // Call the base constructor

	void S0(const std::string& input) {
		if (input[index] == EOF) {
			inputRead = 1;
		} else {
			Serr();
		}
	}
};

#endif //PROJECT1_STARTER_CODE_EOFAUTOMATON_H
