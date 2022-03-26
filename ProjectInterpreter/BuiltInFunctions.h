#pragma once
#include "Expressions.h"

enum class string_code {
	eq, le, nand, length, head, tail, list, concat, ifStmt, read, write, toInt, add, sub, mul, div, mod, sqrt,
	NULLCODE
};

class BuiltInFunctions {
public:
	 string_code find(std::string funcName);
	 Expression* execute(string_code fncName, std::vector<Expression*> params, int line);

	 Expression* eq(std::vector<Expression*> params);
	 Expression* le(std::vector<Expression*> params);	
	 Expression* nand(std::vector<Expression*> params);
	 Expression* length(std::vector<Expression*> params);
	 Expression* head(std::vector<Expression*> params);
	 Expression* tail(std::vector<Expression*> params);
	 Expression* list(std::vector<Expression*> params);
	 Expression* read(std::vector<Expression*> params);
	 Expression* concat(std::vector<Expression*> params);
	 Expression* toInt(std::vector<Expression*> params);
	 Expression* add(std::vector<Expression*> params);
	 Expression* sub(std::vector<Expression*> params);
	 Expression* mul(std::vector<Expression*> params);
	 Expression* div(std::vector<Expression*> params);
	 Expression* sqrt(std::vector<Expression*> params);
	 Expression* ifStmt(std::vector<Expression*> params);
	 Expression* mod(std::vector<Expression*> params);
	 Expression* write(std::vector<Expression*> params);
	

private:
	 Expression* eq(double first, double second);
	 Expression* eq(const std::vector<Expression*>& first, const std::vector<Expression*>& second);
	 Expression* eq(double first, const std::vector<Expression*>& second);
	 Expression* le(double first, double second);
	 Expression* le(const std::vector<Expression*>& first, const std::vector<Expression*>& second);
	 Expression* nand(double first, double second);
	 Expression* nand(const std::vector<Expression*>& first, const std::vector<Expression*>& second);
	 Expression* length(const std::vector<Expression*>& list,int );
	 Expression* length(double num);
	 Expression* head(const std::vector<Expression*>& list,int);
	 Expression* tail(const std::vector<Expression*>& list, int);
	 Expression* list(double firstElement);
	 Expression* list(double firstElement, double step);
	 Expression* list(double firstElement, double step, double maxElements);
	 Expression* concat(const std::vector<Expression*>& first, const std::vector<Expression*>& second);
	 Expression* toInt(double num);
	 Expression* add(double first, double second);
	 Expression* sub(double first, double second);
	 Expression* mul(double first, double second);
	 Expression* div(double first, double second);
	 Expression* sqrt(double num);
	 Expression* ifStmt(Expression* list,double first, double second );
	 Expression* ifStmt(Expression* list, const std::vector<Expression*>& first, const std::vector<Expression*>& second);
	 Expression* mod(int first, int second);
};


