//
// Created by austi_eef6ewn on 9/16/2022.
//

#ifndef PROJECT1_STARTER_CODE_LINECOMMENTAUTOMATON_H
#define PROJECT1_STARTER_CODE_LINECOMMENTAUTOMATON_H

#include "Automaton.h"

class LineCommentAutomaton : public Automaton
{
public:
	LineCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

	void S0(const std::string& input) {
		if (input[index] == '#') {
			inputRead++;
			index++;
			S1(input);
		} else {
			Serr();
		}
	}

	void S1(const std::string& input) {
		if (input[index] == '\n' || input[index] == EOF) {
			inputRead++;
			index++;
			//Instead of calling S2, it ends here because S2 doesn't do anything
		} else if (input[index] != '|') {
			inputRead++;
			index++;
			S3(input);
		}
		else {
			Serr();
		}
	}

	void S2(const std::string& input) {
		//do nothing
	}

	void S3(const std::string& input) {
		if (input[index] != '\n' && input[index] != EOF) {
			inputRead++;
			index++;
			S3(input);
		} else {
			//Instead of calling S2, it ends here because S2 doesn't do anything
		}
	}
};

#endif //PROJECT1_STARTER_CODE_LINECOMMENTAUTOMATON_H
