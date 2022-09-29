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
	this->tempID = "";
}

Parser::~Parser() {
	// Do Nothing - tokens are deleted in ~Lexar()
}

void Parser::Match(TokenType expectedToken) {
	if(expectedToken == GetCurrentToken()) {
		Advance();
	} else {
		//throw "(In Match) ERROR - Expected: " + tokenToString[(int)expectedToken] + ", Actual: " + tokenToString[(int)GetCurrentToken()];
		throw tokens[vectorIndex]->toStringObject();
	}
}

TokenType Parser::GetCurrentToken() {
	return (tokens.at(vectorIndex)->getTokenType());
}

// Returns the description of the current token
std::string Parser::GetCTDescription() {
	return (tokens.at(vectorIndex)->getTokenDescription());
}

void Parser::Advance() {
	if(vectorIndex < (int)tokens.size()) {
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
	ResetTempValues();
	if(GetCurrentToken() == TokenType::ID) {	// First (scheme -> ID)
		tempID = GetCTDescription();
		Match(TokenType::ID);
		Match(TokenType::LEFT_PAREN);
		tempParameterVector.push_back(new Parameter(GetCTDescription()));
		Match(TokenType::ID);
		ParseIdList();
		Match(TokenType::RIGHT_PAREN);

		datalog.addScheme(tempID, tempParameterVector);
	} else {
		throw tokens[vectorIndex]->toStringObject();
	}
}

void Parser::ParseSchemeList() {
		if(GetCurrentToken() == TokenType::ID) {	// First (schemeList -> ID)
			ParseScheme();
			ParseSchemeList();
		} else {
			// lambda - do nothing
		}
}

void Parser::ParseFactList() {
	if(GetCurrentToken() == TokenType::ID) {	// First (factList -> ID)
		ParseFact();
		ParseFactList();
	} else {
		// lambda - do nothing
	}
}

void Parser::ParseRuleList() {
	if(GetCurrentToken() == TokenType::ID) {	// First (ruleList -> ID)
		ParseRule();
		ParseRuleList();
	} else {
		// lambda - do nothing
	}
}

void Parser::ParseQuery() {
	ResetTempValues();
	if(GetCurrentToken() == TokenType::ID) {	// First (query -> ID)
		ParsePredicate();
		datalog.addQuery(tempBodyPredicatesVector.at(0));
		Match(TokenType::Q_MARK);
	} else {
		throw tokens[vectorIndex]->toStringObject();
	}
}

void Parser::ParseQueryList() {
	if(GetCurrentToken() == TokenType::ID) {	// First (queryList -> ID)
		ParseQuery();
		ParseQueryList();
	} else {
		// lambda - do nothing
	}
}

void Parser::ParseIdList() {
	if(GetCurrentToken() == TokenType::COMMA) {	// First (idList -> COMMA)
		Match(TokenType::COMMA);
		tempParameterVector.push_back(new Parameter(GetCTDescription()));
		Match(TokenType::ID);
		ParseIdList();
	} else {
		// lambda - do nothing
	}
}

void Parser::ParseFact() {
	ResetTempValues();
	if(GetCurrentToken() == TokenType::ID) {	// First (fact -> ID)
		tempID = GetCTDescription();
		Match(TokenType::ID);
		Match(TokenType::LEFT_PAREN);
		datalog.addDomain(GetCTDescription());
		tempParameterVector.push_back(new Parameter(GetCTDescription()));
		Match(TokenType::STRING);
		ParseStringList();
		Match(TokenType::RIGHT_PAREN);
		Match(TokenType::PERIOD);

		datalog.addFact(tempID, tempParameterVector);
	} else {
		throw tokens[vectorIndex]->toStringObject();
	}
}

void Parser::ParseRule() {
	ResetTempValues();
	if(GetCurrentToken() == TokenType::ID) {	// First (rule -> ID)
		ParseHeadPredicate();
		Match(TokenType::COLON_DASH);
		ParsePredicate();
		ParsePredicateList();
		Match(TokenType::PERIOD);

		datalog.addRule(tempBodyPredicatesVector);
	} else {
		throw tokens[vectorIndex]->toStringObject();
	}
}

void Parser::ParsePredicate() {
	ResetPredicateValues();
	if(GetCurrentToken() == TokenType::ID) {	// First (predicate -> ID)
		tempID = GetCTDescription();
		Match(TokenType::ID);
		Match(TokenType::LEFT_PAREN);
		ParseParameter();
		ParseParameterList();
		Match(TokenType::RIGHT_PAREN);

		tempBodyPredicatesVector.push_back(new Predicate(tempID, tempParameterVector));
	} else {
		throw tokens[vectorIndex]->toStringObject();
	}
}

void Parser::ParseStringList() {
	if(GetCurrentToken() == TokenType::COMMA) {	// First (stringList -> COMMA)
		Match(TokenType::COMMA);
		datalog.addDomain(GetCTDescription());
		tempParameterVector.push_back(new Parameter(GetCTDescription()));
		Match(TokenType::STRING);
		ParseStringList();
	} else {
		// lambda - do nothing
	}
}

void Parser::ParseHeadPredicate() {
	if(GetCurrentToken() == TokenType::ID) {	// First (headPredicate -> ID)
		tempID = GetCTDescription();
		Match(TokenType::ID);
		Match(TokenType::LEFT_PAREN);
		tempParameterVector.push_back(new Parameter(GetCTDescription()));
		Match(TokenType::ID);
		ParseIdList();
		Match(TokenType::RIGHT_PAREN);

		tempBodyPredicatesVector.push_back(new Predicate(tempID, tempParameterVector));
	} else {
		throw tokens[vectorIndex]->toStringObject();
	}
}

void Parser::ParsePredicateList() {
	if(GetCurrentToken() == TokenType::COMMA) {	// First (predicateList -> COMMA)
		Match(TokenType::COMMA);
		ParsePredicate();
		ParsePredicateList();
	} else {
		// lambda - do nothing
	}
}

void Parser::ParseParameter() {
	if(GetCurrentToken() == TokenType::STRING) {	// First (parameter -> STRING = {STRING, ID})
		tempParameterVector.push_back(new Parameter(GetCTDescription()));
		Match(TokenType::STRING);
	} else if(GetCurrentToken() == TokenType::ID) {	// First (parameter -> ID = {STRING, ID})
		tempParameterVector.push_back(new Parameter(GetCTDescription()));
		Match(TokenType::ID);
	} else {
		throw tokens[vectorIndex]->toStringObject();
	}
}

void Parser::ParseParameterList() {
	if(GetCurrentToken() == TokenType::COMMA) {	// First (parameterList -> COMMA)
		Match(TokenType::COMMA);
		ParseParameter();
		ParseParameterList();
	} else {
		// lambda - do nothing
	}
}

void Parser::RemoveCommentTokens() {
	for(int i = tokens.size() - 1; i >= 0; i--) {
		if(tokens[i]->getTokenTypeAsString() == "COMMENT") {
			//delete tokens[i];
			tokens.erase(tokens.begin() + i);
		}
	}
}

void Parser::PrintDatalog() {
	std::cout << datalog.toString();
}

// Resets the temp values passed into datalog
void Parser::ResetTempValues() {
	this->tempID = "";
	this->tempParameterVector.clear();
	this->tempBodyPredicatesVector.clear();
}

// Resets ONLY the values to create a predicate (Useful for rule which creates multiple predicates)
void Parser::ResetPredicateValues() {
	this->tempID = "";
	this->tempParameterVector.clear();
}

void Parser::PrintTokens() {
	for(int i = 0; i < (int)tokens.size(); ++i) {
		tokens[i]->toString();
	}
	std::cout << "Total Tokens = " << tokens.size() << std::endl;
}

