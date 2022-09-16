//
// Created by austi_eef6ewn on 9/15/2022.
//

#ifndef PROJECT1_STARTER_CODE_RULESAUTOMATON_H
#define PROJECT1_STARTER_CODE_RULESAUTOMATON_H

#include "Automaton.h"

class RulesAutomaton : public Automaton
{
public:
	RulesAutomaton() : Automaton(TokenType::RULES) {}  // Call the base constructor

	void S0(const std::string& input) {
		if (input[index] == 'R') {
			inputRead++;
			index++;
			S1(input);
		} else {
			Serr();
		}
	}

	void S1(const std::string& input) {
		if (input[index] == 'u') {
			inputRead++;
			index++;
			S2(input);
		} else {
			Serr();
		}
	}

	void S2(const std::string& input) {
		if (input[index] == 'l') {
			inputRead++;
			index++;
			S3(input);
		} else {
			Serr();
		}
	}

	void S3(const std::string& input) {
		if (input[index] == 'e') {
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

#endif //PROJECT1_STARTER_CODE_RULESAUTOMATON_H
