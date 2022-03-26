#pragma once

#include "BuiltInFunctions.h"
#include "UserGeneratedFunctions.h"
#include "Parser.h"
#include <iostream>

class Interpreter {
	bool isFunctionDeclaration = false;
	UserGeneratedFunctions userFunctions;
	BuiltInFunctions functions;
	ASTNode* root = nullptr;

	std::vector<ASTNode*> junkNodeCollector;
	std::vector<Expression*> junkExpressionCollector;

	Expression* evaluateAST(ASTNode* root);
public:
	Interpreter() = default;
	~Interpreter() = default;

	void updateAST(bool isDeclaration, ASTNode* root);
	void clearNode(ASTNode* root);
	void clear();

	Expression* evaluateAST() { return evaluateAST(this->root); };
	Expression* evaluateUserDefinedAST(ASTNode* root, std::vector<Expression*> params);

	void addFunction(ASTNode* root);
	void interpret();
	
};