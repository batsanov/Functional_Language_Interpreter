#include "Interpreter.h"



void Interpreter::updateAST(bool isDeclaration,ASTNode* root) {
	this->root = root;
	isFunctionDeclaration = isDeclaration;
}

void Interpreter::clearNode(ASTNode* root)
{
	if (!root)
		return;

	clearNode(root->child);
	clearNode(root->brother);

	delete root;
}

 void Interpreter::clear() {

	 for (size_t i = 0; i < junkNodeCollector.size(); i++)
	 {
		 clearNode(junkNodeCollector[i]);
		 
	 }
	 junkNodeCollector.clear();

	 for (size_t i = 0; i < junkExpressionCollector.size(); i++)
	 {
		 delete junkExpressionCollector[i];
	 }
	 junkExpressionCollector.clear();
	 isFunctionDeclaration = false;

}

 Expression* Interpreter::evaluateAST(ASTNode* root)
{
	if (root->child == nullptr && root->getType() != TokenType::FUNC_CALL)
	{
		Expression* res = root->expr->getCopy();
		junkExpressionCollector.push_back(res);
		return res;
	}

	string_code code = functions.find(root->expr->getToken().lexeme);

	std::vector<Expression*> params;
	ASTNode* it = root->child;

	while (it)
	{
		params.push_back(evaluateAST(it));
		it = it->brother;
	}

	if (code != string_code::NULLCODE)
	{
		
		Expression* res = functions.execute(code, params, root->expr->getToken().line);
		junkExpressionCollector.push_back(res);

		return res;
	}


	if (userFunctions.isFunction(root->expr->getToken().lexeme)) 
	{
		ASTNode* funcBody = userFunctions.call(root->expr->getToken().lexeme);
		junkNodeCollector.push_back(funcBody);

		return evaluateUserDefinedAST(funcBody, params);
	}

	throw new InterpreterException("Invalid function call !", root->expr->getToken().line);
}

 Expression* Interpreter::evaluateUserDefinedAST(ASTNode* root, std::vector<Expression*> userParams)
 {

	 if (root->getType() == TokenType::ARGUMENT)
	 {
		 Expression* res = userParams[root->expr->getToken().toNumber()]->getCopy();
		 junkExpressionCollector.push_back(res);
		 return res;
	 }

	 if (root->child == nullptr && root->getType() != TokenType::FUNC_CALL)
	 {
		 Expression* res = root->expr->getCopy();
		 junkExpressionCollector.push_back(res);
		 return res;
	 }

	 string_code code = functions.find(root->expr->getToken().lexeme);

	 std::vector<Expression*> params;
	 ASTNode* it = root->child;
	 while (it)
	 {
		 params.push_back(evaluateUserDefinedAST(it, userParams));
		 it = it->brother;
	 }

	 if (code != string_code::NULLCODE)
	 {
		 Expression* res = functions.execute(code, params, root->expr->getToken().line);
		 junkExpressionCollector.push_back(res);

		 return res;
	 }


	 if (userFunctions.isFunction(root->expr->getToken().lexeme))
	 {
		 ASTNode* funcBody = userFunctions.call(root->expr->getToken().lexeme);
		 junkNodeCollector.push_back(funcBody);

		 Expression* result = evaluateUserDefinedAST(funcBody, params);

		 return result;
	 }
 }

 void Interpreter::addFunction(ASTNode* root)
 {
	
	 std::string funcName = root->expr->getToken().lexeme;
	 
	 ASTNode* toAdd = root->child;
	 root->child = nullptr;
	 delete root;
	 this->root = nullptr;

	 std::cout << userFunctions.add(funcName, toAdd) << std::endl;
 }

 void Interpreter::interpret()
{
	try
	{
		if (isFunctionDeclaration)
		{
			addFunction(root);
		}
		else
		{
			junkNodeCollector.push_back(root);
			Expression* result = evaluateAST();
			
			std::cout << result->print() << "\n";
		
		}

	}
	catch (std::exception* e)
	{
		std::cout << e->what();
		delete e;
	}
}
