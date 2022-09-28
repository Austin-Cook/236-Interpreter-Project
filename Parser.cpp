//
// Created by austi_eef6ewn on 9/26/2022.
//

#include "Parser.h"

// Map to return a TokenType as string
static std::string tokenToString[] = {
		"COMMA",
		"PERIOD",
		"Q_MARK",
		"LEFT_PAREN",
		"RIGHT_PAREN",
		"COLON",
		"COLON_DASH",
		"MULTIPLY",
		"ADD",
		"SCHEMES",
		"FACTS",
		"RULES",
		"QUERIES",
		"ID",
		"STRING",
		"COMMENT",
		"UNDEFINED",
		"EOF_TOKEN"
};

Parser::Parser(std::vector<Token *> tokens) {
	this->tokens = tokens;
	this->vectorIndex = 0;
}

Parser::~Parser() {
	// Do Nothing - tokens are deleted in ~Lexar()
}

void Parser::Match(TokenType expectedToken) {
	try {
		if(expectedToken == getCurrentToken()) {
			Advance();
		} else {
			throw "ERROR - Expected: " + tokenToString[(int)expectedToken] + ", Actual: " + tokenToString[(int)getCurrentToken()];
		}
	} catch(std::string error) {
		Advance();							//FIXME THIS PROBABLY SHOULDN'T BE HERE
		std::cerr << error << std::endl;
	}

}

TokenType Parser::getCurrentToken() {
	if(vectorIndex < tokens.size()) {
		return (tokens.at(vectorIndex)->getTokenType());
	} else {
		std::cerr << "ERROR in getCurrentToken() - Attempted token is out of range of tokens vector";
	}
}

void Parser::Advance() {
	if(vectorIndex < tokens.size()) {
		//std::cout << "Index: " << vectorIndex << std::endl; //FIXME DELETEME
		vectorIndex++;
	} else {
		std::cerr << "ERROR in Advance() - Attempted token is out of range of tokens vector";
	}
}

/*
 * This function facilitates parsing the Datalog Program
 */
void Parser::ParseDatalogProgram() {
	// Remove Comments Prior to Parsing
	RemoveCommentTokens();

//	PrintTokens();

	std::vector<Token*>::iterator currentToken = tokens.begin();
	//Datalog Production
	Match(TokenType::SCHEMES);
	Match(TokenType::COLON);
	ParseScheme();
	ParseSchemeList();
	Match(TokenType::FACTS);
	Match(TokenType::COLON);
	ParseFactList();
	Match(TokenType::RULES);
	Match(TokenType::COLON);
	ParseRuleList();
	Match(TokenType::QUERIES);
	Match(TokenType::COLON);
	ParseQuery();
	ParseQueryList();
	Match(TokenType::EOF_TOKEN);
}

void Parser::ParseScheme() {
	try {
		if(getCurrentToken() == TokenType::ID) {	// First (scheme -> ID)
			Match(TokenType::ID);
			Match(TokenType::LEFT_PAREN);
			Match(TokenType::ID);
			ParseIdList();
			Match(TokenType::RIGHT_PAREN);
		} else {
			throw "Error in ParseScheme() - Expected: ID, Actual: " + tokenToString[(int)getCurrentToken()];
		}
	}
	catch(std::string error) {
		std::cerr << error << std::endl;
	}
}

void Parser::ParseSchemeList() {
		if(getCurrentToken() == TokenType::ID) {	// First (schemeList -> ID)
			ParseScheme();
			ParseSchemeList();
		} else {
			// lambda - do nothing FIXME this could check for a follow set?
		}
}

void Parser::ParseFactList() {
	if(getCurrentToken() == TokenType::ID) {	// First (factList -> ID)
		ParseFact();
		ParseFactList();
	} else {
		// lambda - do nothing FIXME this could check for a follow set?
	}
}

void Parser::ParseRuleList() {
	if(getCurrentToken() == TokenType::ID) {	// First (ruleList -> ID)
		ParseRule();
		ParseRuleList();
	} else {
		// lambda - do nothing FIXME this could check for a follow set?
	}
}

void Parser::ParseQuery() {
	try {
		if(getCurrentToken() == TokenType::ID) {	// First (query -> ID)
			ParsePredicate();
			Match(TokenType::Q_MARK);
		} else {
			throw "Error in ParseQuery() - Expected: ID, Actual: " + tokenToString[(int)getCurrentToken()];
		}
	}
	catch(std::string error) {
		std::cerr << error << std::endl;
	}
}

void Parser::ParseQueryList() {
	if(getCurrentToken() == TokenType::ID) {	// First (queryList -> ID)
		ParseQuery();
		ParseQueryList();
	} else {
		// lambda - do nothing FIXME this could check for a follow set?
	}
}

void Parser::ParseIdList() {
	if(getCurrentToken() == TokenType::COMMA) {	// First (idList -> COMMA)
		Match(TokenType::COMMA);
		Match(TokenType::ID);
		ParseIdList();
	} else {
		// lambda - do nothing FIXME this could check for a follow set?
	}
}

void Parser::ParseFact() {
	try {
		if(getCurrentToken() == TokenType::ID) {	// First (fact -> ID)
			Match(TokenType::ID);
			Match(TokenType::LEFT_PAREN);
			Match(TokenType::STRING);
			ParseStringList();
			Match(TokenType::RIGHT_PAREN);
			Match(TokenType::PERIOD);
		} else {
			throw "Error in ParseFact() - Expected: ID, Actual: " + tokenToString[(int)getCurrentToken()];
		}
	}
	catch(std::string error) {
		std::cerr << error << std::endl;
	}
}

void Parser::ParseRule() {
	try {
		if(getCurrentToken() == TokenType::ID) {	// First (rule -> ID)
			ParseHeadPredicate();
			Match(TokenType::COLON_DASH);
			ParsePredicate();
			ParsePredicateList();
			Match(TokenType::PERIOD);
		} else {
			throw "Error in ParseRule() - Expected: ID, Actual: " + tokenToString[(int)getCurrentToken()];
		}
	}
	catch(std::string error) {
		std::cerr << error << std::endl;
	}
}

void Parser::ParsePredicate() {
	try {
		if(getCurrentToken() == TokenType::ID) {	// First (predicate -> ID)
			Match(TokenType::ID);
			Match(TokenType::LEFT_PAREN);
			ParseParameter();
			ParseParameterList();
			Match(TokenType::RIGHT_PAREN);
		} else {
			throw "Error in ParsePredicate() - Expected: ID, Actual: " + tokenToString[(int)getCurrentToken()];
		}
	}
	catch(std::string error) {
		std::cerr << error << std::endl;
	}
}

void Parser::ParseStringList() {
	if(getCurrentToken() == TokenType::COMMA) {	// First (stringList -> COMMA)
		Match(TokenType::COMMA);
		Match(TokenType::STRING);
		ParseStringList();
	} else {
		// lambda - do nothing FIXME this could check for a follow set?
	}
}

void Parser::ParseHeadPredicate() {
	try {
		if(getCurrentToken() == TokenType::ID) {	// First (headPredicate -> ID)
			Match(TokenType::ID);
			Match(TokenType::LEFT_PAREN);
			Match(TokenType::ID);
			ParseIdList();
			Match(TokenType::RIGHT_PAREN);
		} else {
			throw "Error in ParseHeadPredicate() - Expected: ID, Actual: " + tokenToString[(int)getCurrentToken()];
		}
	}
	catch(std::string error) {
		std::cerr << error << std::endl;
	}
}

void Parser::ParsePredicateList() {
	if(getCurrentToken() == TokenType::COMMA) {	// First (predicateList -> COMMA)
		Match(TokenType::COMMA);
		ParsePredicate();
		ParsePredicateList();
	} else {
		// lambda - do nothing FIXME this could check for a follow set?
	}
}

void Parser::ParseParameter() {
	try {
		if(getCurrentToken() == TokenType::STRING) {	// First (parameter -> STRING = {STRING})
			Match(TokenType::STRING);
		} else if(getCurrentToken() == TokenType::ID) {	// First (parameter -> ID = {ID})
			Match(TokenType::ID);
		} else {
			throw "Error in ParseParameter() - Expected: STRING or ID, Actual: " + tokenToString[(int)getCurrentToken()];
		}
	} catch(std::string error) {
		std::cerr << error << std::endl;
	}
}

void Parser::ParseParameterList() {
	if(getCurrentToken() == TokenType::COMMA) {	// First (parameterList -> COMMA)
		Match(TokenType::COMMA);
		ParseParameter();
		ParseParameterList();
	} else {
		// lambda - do nothing FIXME this could check for a follow set?
	}
}

void Parser::RemoveCommentTokens() {
	for(int i = tokens.size() - 1; i >= 0; i--) {
		if(tokens[i]->getTokenTypeAsString() == "COMMENT") {
			delete tokens[i];
			tokens.erase(tokens.begin() + i);
		}
	}
}

void Parser::PrintTokens() {
	for(int i = 0; i < (int)tokens.size(); ++i) {
		tokens[i]->toString();
	}
	std::cout << "Total Tokens = " << tokens.size() << std::endl;
}

