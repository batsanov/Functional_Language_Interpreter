#pragma once
#include "vector"
#include "string"
#include <iostream>
#include "Tokenizer.h"
#include "list"
#include "vector"

class Reader {
private:
	std::vector<Token> tokens;
	std::string source;

public:
	Reader() = default;
	void clear();

	void updateSource(std::string source);
	std::vector<Token>& tokenize();
	int size();
}; 



