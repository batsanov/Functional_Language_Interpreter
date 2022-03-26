#pragma once
#include <exception>
#include "Tokenizer.h"

class InterpreterException : public std::exception
{
	int line;
	std::string text;
	std::string finalMessage;
public:
	InterpreterException(std::string text, int line) : text(text), line(line) 
	{
		std::ostringstream temp;
		temp << line;
	
		finalMessage = text + " Error at line " + temp.str() + "!\n";
	};

	virtual const char* what() const throw()
	{
		return finalMessage.c_str();
	}
	~InterpreterException() = default;
};