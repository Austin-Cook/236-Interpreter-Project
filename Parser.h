//
// Created by austi_eef6ewn on 9/26/2022.
//

#ifndef PROJECT1_STARTER_CODE_PARSER_H
#define PROJECT1_STARTER_CODE_PARSER_H

#include "Token.h"
#include "DatalogProgram.h"
#include <vector>

class Parser {
public:
	Parser(std::vector<Token*> tokens);
	~Parser();
	void Match(TokenType expectedToken);
	TokenType getCurrentToken();
	void Advance();
	void ParseDatalogProgram();
	// Recursive Parse Functions
	void ParseScheme();
	void ParseSchemeList();
	void ParseFactList();
	void ParseRuleList();
	void ParseQuery();
	void ParseQueryList();
	void ParseIdList();
	void ParseFact();
	void ParseRule();
	void ParsePredicate();
	void ParseStringList();
	void ParseHeadPredicate();
	void ParsePredicateList();
	void ParseParameter();
	void ParseParameterList();

	void RemoveCommentTokens();
	// Function for testing
	void PrintTokens();
private:
	std::vector<Token*> tokens;
	int vectorIndex;
	DatalogProgram datalog();
};


#endif //PROJECT1_STARTER_CODE_PARSER_H
