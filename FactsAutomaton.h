//
// Created by austi_eef6ewn on 9/15/2022.
//

#ifndef PROJECT1_STARTER_CODE_FACTSAUTOMATON_H
#define PROJECT1_STARTER_CODE_FACTSAUTOMATON_H

#include "Automaton.h"

class FactsAutomaton : public Automaton
{
public:
	FactsAutomaton() : Automaton(TokenType::FACTS) {}  // Call the base constructor

	void S0(const std::string& input) {
		if (input[index] == 'F') {
			inputRead++;
			index++;
			S1(input);
		} else {
			Serr();
		}
	}

	void S1(const std::string& input) {
		if (input[index] == 'a') {
			inputRead++;
			index++;
			S2(input);
		} else {
			Serr();
		}
	}

	void S2(const std::string& input) {
		if (input[index] == 'c') {
			inputRead++;
			index++;
			S3(input);
		} else {
			Serr();
		}
	}

	void S3(const std::string& input) {
		if (input[index] == 't') {
			inputRead++;
			index++;
			S4(input);
		} else {
			Serr();
		}
	}

	void S4(const std::string& input) {
		if (input[index] == 's') {
			inputRead++;
			index++;
		} else {
			Serr();
		}
	}
};

#endif //PROJECT1_STARTER_CODE_FACTSAUTOMATON_H
