#pragma once
#include "Tokenizer.h"
#include <iomanip>
#include "list"
#include <cmath>

class Expression {
protected:
	const Token operation;
public:

	Expression(Token operation) : operation(operation) {};

	const Token& getToken()
	{
		return operation;
	}

	virtual std::string print() = 0;
	virtual Expression* getCopy() = 0;
	virtual ~Expression() = default;
};

class InfiniteListLiteral : public Expression {
public:
	InfiniteListLiteral(Token operation, double firstElement, double step) : Expression(operation), firstElement(firstElement), step(step) {};

	double firstElement;
	double step;

	Expression* getCopy() override
	{
		return new InfiniteListLiteral(operation, firstElement, step);
	}

	std::string print() override
	{
		std::string result = "[ ";
		for (size_t i = 0; i < 5; i++)
		{
			std::ostringstream stream;
			stream << std::fixed;
			stream << std::setprecision(2);
			stream << (firstElement + step * i);
			
			std::string str = stream.str();
			result += str + " ";

		}
		result += "....";
			return result;
		
	}

	~InfiniteListLiteral() = default;
};

class FiniteListLiteral : public Expression {
public:
	FiniteListLiteral(Token operation, std::vector<Expression*> expr) : Expression(operation), expressions(expr) {};

	std::vector<Expression*> expressions;

	Expression* getCopy() override
	{
		std::vector<Expression*> result;

		for (size_t i = 0; i < expressions.size(); i++)
		{
			result.push_back(expressions[i]->getCopy());
		}

		return new FiniteListLiteral(Token(0, TokenType::LIST, "list"), result);
	}

	std::string print() override
	{
		std::string result = "[ ";
		for (Expression* expr : expressions)
			result = result + expr->print() + " ";
		result += "]";
		return result;
	}

	~FiniteListLiteral()
	{
		for(Expression* expr : expressions)
			delete expr;
	}
};

class Number : public Expression {
public:
	Number(Token operation, double value) : Expression(operation), value(value) {};

	double value;

	Expression* getCopy() override
	{
		return new Number(Token(operation), value);
	}

	std::string print() override
	{
		std::ostringstream stream;
		stream << std::fixed;
		stream << std::setprecision(2);
		stream << value;

		std::string str = stream.str();
		return str;
	}

	~Number() = default;
};

class FunctionCall : public Expression {
public:
	FunctionCall(Token operation) : Expression(operation) {};

	Expression* getCopy() override
	{
		return new FunctionCall(operation);
	}

	std::string print() override {
		return operation.lexeme;
	};
};

class Argument : public Expression {
public:
	Argument(Token operation) : Expression(operation) { };

	Expression* getCopy() override
	{
		return new Argument(operation);
	}

	std::string print() override {
		return "ARGUMENT";
	}
};

