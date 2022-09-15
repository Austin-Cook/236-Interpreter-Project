#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"

#include <cctype>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    //set lineNumber to 1
	lineNum = 1;
    // While there are more characters to tokenize
    //loop while input.size() > 0 {
    //    set maxRead to 0
    //    set maxAutomaton to the first automaton in automata

	while(input.size() > 0) {
		int maxRead = 0;
		Automaton* maxAutomaton = automata[0];
		//FIXME should everything be in here?

		// TODO: you need to handle whitespace in between tokens

		// Here is the "Parallel" part of the algorithm
		//   Each automaton runs with the same input
		//    foreach automaton in automata {
		//        inputRead = automaton.Start(input)
		//        if (inputRead > maxRead) {
		//            set maxRead to inputRead
		//            set maxAutomaton to automaton
		//        }
		//    }
		for (int i = 0; i < automata.size(); i++) {
			int inputRead = automata[i]->Start(input);
			if(inputRead > maxRead) {
				maxRead = inputRead;
				maxAutomaton = automata[i];
			}
		}
		// Here is the "Max" part of the algorithm
		//    if maxRead > 0 {
		//        set newToken to maxAutomaton.CreateToken(...)
		//            increment lineNumber by maxAutomaton.NewLinesRead()
		//            add newToken to collection of all tokens
		//    }
		// No automaton accepted input
		// Create single character undefined token
		//    else {
		//        set maxRead to 1
		//            set newToken to a  new undefined Token
		//            (with first character of input)
		//            add newToken to collection of all tokens
		//    }
		if(maxRead > 0) {
			// Get string to add as "description" of token

			std::string description = "";				//FIXME do I remove from input each time?
			for(int i = 0; i < maxRead; i++) {
				description.push_back(input[0]);		// Append 1 char from index 0 of input to description
				input.erase(0, 1);				// Erase 1 char from index 0 of input
			}

			Token* newToken = maxAutomaton->CreateToken(description, lineNum);
			tokens.push_back(newToken);
			lineNum += maxAutomaton->NewLinesRead();	//FIXME make sure I should increment line after creating token
		}
		// UNDEFINED of whitespace
		else {
			maxRead = 1;
			std::string description = ";";
			if(!isspace(input[0])) {
				description.push_back(input[0]);		// Append 1 char from index 0 of input to description
				Token* newToken = new Token(TokenType::UNDEFINED, description, lineNum);
				tokens.push_back(newToken);
			}
			else if(input[0] == '\n') {			//FIXME '\n' here?
				lineNum++;
			}
			input.erase(0, 1);					// Erase 1 char from index 0 of input
			//FIXME get line num right
		}
		// Update `input` by removing characters read to create Token
		//    remove maxRead characters from input
		//}
		//add end of file token to all tokens
		//*/
	}
}

void Lexer::printTokens() {
	for(int i = 0; i < tokens.size(); ++i) {
		tokens[i]->toString();
	}
}