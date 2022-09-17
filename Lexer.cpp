#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "Left_ParenAutomaton.h"
#include "Right_ParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"

#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IdAutomaton.h"
#include "StringAutomaton.h"
#include "LineCommentAutomaton.h"
#include "BlockCommentAutomaton.h"
#include "EOFAutomaton.h"

#include <cctype>

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    for(auto each : automata) {
		delete each;
	}
	automata.clear();
	for(auto each : tokens) {
		delete each;
	}
	tokens.clear();
}

void Lexer::CreateAutomata() {
	automata.push_back(new CommaAutomaton());
	automata.push_back(new PeriodAutomaton());
	automata.push_back(new Q_MarkAutomaton);
	automata.push_back(new Left_ParenAutomaton);
	automata.push_back(new Right_ParenAutomaton);
	automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
	automata.push_back(new MultiplyAutomaton());
	automata.push_back(new AddAutomaton());

	automata.push_back(new SchemesAutomaton());
	automata.push_back(new FactsAutomaton());
	automata.push_back(new RulesAutomaton());
	automata.push_back(new QueriesAutomaton());
	automata.push_back(new IdAutomaton);
	automata.push_back(new StringAutomaton);
	automata.push_back(new LineCommentAutomaton);
	automata.push_back(new BlockCommentAutomaton);
	automata.push_back(new EOFAutomaton);

}

void Lexer::Run(std::string& input) {
	lineNum = 1;

	// Runs the lexer with the Parallel and Max approach
	while(input.size() > 0) {
		int maxRead = 0;
		Automaton* maxAutomaton = automata[0];

		// "Parallel" part of the algorithm
		for (int i = 0; i < (int)automata.size(); i++) {
			int inputRead = automata[i]->Start(input);
			if(inputRead > maxRead) {
				maxRead = inputRead;
				maxAutomaton = automata[i];
			}
		}

		// Here is the "Max" part of the algorithm
		if(maxRead > 0) {
			// Get string to add as "description" of token
			std::string description = "";				//FIXME do I remove from input each time?
			for(int i = 0; i < maxRead; i++) {
				description.push_back(input[0]);		// Append 1 char from index 0 of input to description
				input.erase(0, 1);				// Erase 1 char from index 0 of input
			}
			Token* newToken = maxAutomaton->CreateToken(description, lineNum);
			tokens.push_back(newToken);
			lineNum += maxAutomaton->NewLinesRead();
		}
		// UNDEFINED Chars
		else {
			maxRead = 1;
			std::string description = "";
			if(input[0] == '\n') {
				lineNum++;
			} else if(!isspace(input[0])) {
				description.push_back(input[0]);		// Append 1 char from index 0 of input to description
				Token* newToken = new Token(TokenType::UNDEFINED, description, lineNum);
				tokens.push_back(newToken);
			}
			input.erase(0, 1);					// Erase 1 char from index 0 of input
		}
		//Not included - add end of file token to all tokens - EOF added to end of input string in main before passing it on here
	}
}

void Lexer::printTokens() {
	for(int i = 0; i < (int)tokens.size(); ++i) {
		tokens[i]->toString();
	}
	std::cout << "Total Tokens = " << tokens.size() << std::endl;
}