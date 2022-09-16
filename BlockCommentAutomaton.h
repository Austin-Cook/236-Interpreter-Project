//
// Created by austi_eef6ewn on 9/16/2022.
//

#ifndef PROJECT1_STARTER_CODE_BLOCKCOMMENTAUTOMATON_H
#define PROJECT1_STARTER_CODE_BLOCKCOMMENTAUTOMATON_H

#include "Automaton.h"

class BlockCommentAutomaton : public Automaton
{
public:
	BlockCommentAutomaton() : Automaton(TokenType::COMMENT) {}  // Call the base constructor

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
		if (input[index] == '|') {
			inputRead++;
			index++;
			S2(input);
		} else {
			Serr();
		}
	}

	void S2(const std::string& input) {
		if(input[index] == EOF) {
			//Set the token type to undefined
			this->type = TokenType::UNDEFINED;
		} else if (input[index] == '|') {
			inputRead++;
			index++;
			S3(input);
		} else {
			inputRead++;
			index++;
			S2(input);
		}
	}

	void S3(const std::string& input) {
		if(input[index] == EOF) {
			//Set the token type to undefined
			this->type = TokenType::UNDEFINED;
		} else if (input[index] == '#') {
			inputRead++;
			index++;
			// Ends here because S4 doesn't do anything
		} else {
			S2(input);
		}
	}

	void S4(const std::string& input) {
		//Do nothing
	}
};

#endif //PROJECT1_STARTER_CODE_BLOCKCOMMENTAUTOMATON_H
