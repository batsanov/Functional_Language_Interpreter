#pragma once
#include "string"
#include "unordered_map"
#include <sstream>
#include <iostream>

enum class TokenType {
	COMMA, LEFT_SQUARE_BRACKET, RIGHT_SQUARE_BRACKET,
	LEFT_PAREN, RIGHT_PAREN, ARGUMENT,
	NUMBER,  FUNC_CALL,	LIST_NUMBER_LITERAL, LIST_LIST_LITERAL, LIST_FUNC_LITERAL,
	EQ, LE, NAND, LENGTH, HEAD, TAIL, LIST, CONCAT, IF, READ, WRITE, INT,
	ADD, SUB, MUL, DIV, MOD, SQRT, ARROW, IDENTIFIER,
	END, 
};

struct Token
{
	int line;
	TokenType type;
	std::string lexeme;

	Token() = default;
	Token(int line, TokenType type, std::string lexeme);
	Token& operator=(const Token& other) {
		if (this != &other)
		{
			line = other.line;
			type = other.type;
			lexeme = other.lexeme;
		}
		return *this;
	}

	std::string getLine() const;

	double toNumber() const;

	void printLine();
	void printType();

	std::string toString();
};

class Tokenizer {
	friend class Reader;
private:

	static size_t line;
	std::string input;
	size_t index;
	

public:
	Tokenizer(const std::string input);;
	Token next();

private:
	bool isArrow(char c);
	bool isDigit(char c);
	char peekNext();
	char peek();
	
	bool isAlpha(char c);
	bool isAlphaNumeric(char c);

	std::string readNumber(bool isNegative);
	std::string readIdentifier();
};



