#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

enum class TokenType {
    COMMA,
	PERIOD,
	Q_MARK,
	LEFT_PAREN,
	RIGHT_PAREN,
	COLON,
    COLON_DASH,
	MULTIPLY,
	ADD,
	SCHEMES,
	FACTS,
	RULES,
	QUERIES,
	ID,
	STRING,
	COMMENT,
    UNDEFINED,
	EOF_TOKEN
};

class Token
{
private:
    // Member variables for information needed by Token
	TokenType type;
	std::string description;
	int lineNumber;

public:
    Token(TokenType type, std::string description, int line);
	virtual ~Token() {}
	void toString();
	std::string TokenTypeToString(TokenType type);
	std::string getTokenTypeAsString();
	TokenType getTokenType();
};

#endif // TOKEN_H
