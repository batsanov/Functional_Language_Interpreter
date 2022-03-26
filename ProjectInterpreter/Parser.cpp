#include "Parser.h"

 void Parser::clear() {
	tokens.clear();
	current = 0;
	isFunctionDeclaration = false;
}

 void Parser::updateTokens(std::vector<Token>& tokens) {
	this->tokens = tokens;
}

 ASTNode* Parser::parseLine()
{
	switch (tokens[current].type)
	{
	case TokenType::NUMBER:
		return readNumber();
		break;

	case TokenType::LEFT_SQUARE_BRACKET:
		return readList();
		break;

	case TokenType::IDENTIFIER:
		return checkIfDeclarationOrCall();
		break;

	case TokenType::END:
		break;
	default:
		break;
	}
}

 bool Parser::isDeclaration()
 {
	 return isFunctionDeclaration;
 }

 void Parser::advance()
{
	++current;
}

Token Parser::peek()
{
	return tokens[current + 1];
}

 ASTNode* Parser::readNumber()
{
	if (tokens.size() - current != 1)
	{
		throw new InterpreterException("Invalid input! Only one expression per row!", tokens[current].line);
	}
	else
		return parseNumber();
}

 ASTNode* Parser::readList()
{
	advance();

	ASTNode* result = parseList();

	if (tokens.size() - 1 != current && peek().type == TokenType::END)
	{
		throw new InterpreterException("Invalid input! Only one expression per row!", tokens[current].line);
	}

	return result;
}

 ASTNode* Parser::readNumberList(TokenType type)
{
	std::vector<Expression*> expressions;

	while (tokens[current].type != TokenType::RIGHT_SQUARE_BRACKET)
	{

		if (tokens.size() - 1 == current)
		{
			throw new InterpreterException("Invalid input! No closing square bracket!", tokens[current].line);
		}

		if (tokens[current].type != type)
		{
			throw new InterpreterException("Invalid input! Lists are ony-type only!", tokens[current].line);
		}

		expressions.push_back(new Number(tokens[current], tokens[current].toNumber()));

		advance();
	}



	std::string lexeme = "LIST_NUMBER_LITERAL";
	return new ASTNode(new FiniteListLiteral(Token(tokens[current - 1].line, TokenType::LIST, lexeme), expressions));
}

 ASTNode* Parser::readFuncList(TokenType type)
{
	return nullptr;
}

 ASTNode* Parser::checkIfDeclarationOrCall()
{
	if (peek().type == TokenType::ARROW)
	{
		return functionDecl();
	}
	else if (peek().type == TokenType::LEFT_PAREN)
	{
		return functionCall();
	}
	else throw new InterpreterException("Invalid input! ", tokens[current].line);
}

 ASTNode* Parser::functionCall()
{
	std::stack<ASTNode*> stack;

	for (; ;)
	{
		if (tokens[current].type == TokenType::LEFT_PAREN || tokens[current].type == TokenType::COMMA)
		{
			advance();
		}
		else if (tokens[current].type == TokenType::RIGHT_PAREN)
		{
			if (tokens.size() - 1 == current || peek().type == TokenType::END)
			{
				if (stack.size() != 1)
					throw new InterpreterException("Invalid input! ", tokens[current].line);
				ASTNode* result = stack.top();
				stack.pop();
				return result;
			}

			addFirstAsChild(stack);
			advance();
		}
		else if (tokens[current].type == TokenType::IDENTIFIER)
		{
			stack.push(parseFuncCall());
			advance();
		}
		else if (tokens[current].type == TokenType::NUMBER)
		{
			stack.top()->addChild(parseNumber());
			advance();
		}
		else if (tokens[current].type == TokenType::ARGUMENT)
		{
			stack.top()->addChild(parseArgument());
			advance();
		}
		else if (tokens[current].type == TokenType::LEFT_SQUARE_BRACKET)
		{
			advance();
			stack.top()->addChild(parseList());
			advance();
		}

		else throw new InterpreterException("Invalid input! ", tokens[current].line);
	}
	return nullptr;
}

 ASTNode* Parser::functionDecl() 
 {
	isFunctionDeclaration = true;

	std::string funcName = tokens[current].lexeme;

	advance();
	advance();

	ASTNode* func = new ASTNode(new FunctionCall(Token(tokens[current].line, TokenType::FUNC_CALL, funcName)));
	func->addChild(parseLine());

	return func;
}

 ASTNode* Parser::parseArgument()
 {
	 return new ASTNode(new Argument(tokens[current]));
 }

 ASTNode* Parser::parseNumber()
{
	return new ASTNode(new Number(tokens[current], tokens[current].toNumber()));
}

 ASTNode* Parser::parseNumber(int num)
{
	return new ASTNode(new Number(Token(tokens[current].line, TokenType::NUMBER, std::to_string(num)), num));
}

 ASTNode* Parser::parseList()
{
	TokenType listType = tokens[current].type;


	if (listType == TokenType::NUMBER)
	{
		return readNumberList(listType);
	}
	else if (listType == TokenType::RIGHT_SQUARE_BRACKET)
	{
		std::vector<Expression*> expressions;
		return new ASTNode(new FiniteListLiteral(Token(tokens[current - 1].line, TokenType::LIST, "list"), expressions));
	}
}

 ASTNode* Parser::parseFuncCall()
{
	return new ASTNode(new FunctionCall(Token(tokens[current].line, TokenType::FUNC_CALL, tokens[current].lexeme)));
}

void Parser::addFirstAsChild(std::stack<ASTNode*>& stack)
{
	ASTNode* node = stack.top();
	stack.pop();
	ASTNode* it = stack.top()->child;

	if (it == nullptr)
	{
		stack.top()->child = node;
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

 void Parser::addParam(std::stack<ASTNode*>& stack)
{
	switch (tokens[current].type)
	{
	case TokenType::NUMBER:
		stack.top()->addChild(parseNumber());
		break;
	case TokenType::LIST:
		stack.top()->addChild(parseList());
		break;
	case TokenType::FUNC_CALL:
		stack.top()->addChild(parseFuncCall());
		break;
	default:
		break;
	}
}



