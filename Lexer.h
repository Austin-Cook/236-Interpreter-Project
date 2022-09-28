#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
	int lineNum = 1;
    void CreateAutomata();

public:
    Lexer();
    ~Lexer();
    void Run(std::string& input);
	void printTokens();
	// Similar function in Parser class - Do not use this one
	void RemoveCommentTokens();
	std::vector<Token*> getTokenVector();
};

#endif // LEXER_H

