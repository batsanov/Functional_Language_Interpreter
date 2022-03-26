#pragma once
#include "Expressions.h"
#include "InterpreterException.h"
#include "stack"

struct ASTNode {

	Expression* expr;
	ASTNode* child;
	ASTNode* brother;
	ASTNode(Expression* expr, ASTNode* child = nullptr, ASTNode* brother = nullptr) : expr(expr), child(child), brother(brother) {};
	~ASTNode() {
		delete expr;
	}
	TokenType getType() {
		return expr->getToken().type;
	}
	void addChild(ASTNode* node)
	{
		ASTNode* it = child;

		if (it == nullptr)
		{
			child = node;
		}
		else
		{
			while (it->brother != nullptr)
			{
				it = it->brother;
			}

			it->brother = node;
		}
	}
};


class Parser {
private:
	bool isFunctionDeclaration = false;
	std::vector<Token> tokens;
	int current = 0;
public:
	Parser() = default;
	void clear();
	void updateTokens(std::vector<Token>& tokens);

	ASTNode* parseLine();
	bool isDeclaration();
private:
	void advance();
	Token peek();
	ASTNode* readNumber();
	ASTNode* readList();
	ASTNode* readNumberList(TokenType type);
	ASTNode* readFuncList(TokenType type);
	ASTNode* checkIfDeclarationOrCall();
	ASTNode* functionCall();
	ASTNode* functionDecl();
	ASTNode* parseArgument();
	ASTNode* parseNumber();
	ASTNode* parseNumber(int num);
	ASTNode* parseList();
	ASTNode* parseFuncCall();

	void addFirstAsChild(std::stack<ASTNode*>& stack);
	void addParam(std::stack<ASTNode*>& stack);
};







