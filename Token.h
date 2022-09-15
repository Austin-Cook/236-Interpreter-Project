#ifndef TOKEN_H
#define TOKEN_H
#include <string>

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
	//EOF	//FIXME what do I name this!??
};

class Token
{
private:
    // TODO: add member variables for information needed by Token

public:
    Token(TokenType type, std::string description, int line);

    // TODO: add other needed methods
};

#endif // TOKEN_H

