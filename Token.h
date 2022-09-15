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
	COLON,			// Previously here
    COLON_DASH,		// Previously here
	MULTIPLY,
	ADD,
	SCHEMES,
	FACTS,
	RULES,
	QUERIES,
	ID,
	STRING,
	COMMENT,
    UNDEFINED,		// Previously here
	EOF_TOKEN		//FIXME watch the naming here!
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
	void toString();
	std::string TokenTypeToString(TokenType type);		//FIXME test to see if this works
};

#endif // TOKEN_H
