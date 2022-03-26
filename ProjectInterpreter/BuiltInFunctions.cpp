#include "BuiltInFunctions.h"
#include "InterpreterException.h"
#include <iostream>
#include <cmath>

 Expression* BuiltInFunctions::eq(double first, double second)
{
	bool equal = first == second;

	if (equal)
		return new Number(Token(0, TokenType::NUMBER, "1"), equal);
	else
		return new Number(Token(0, TokenType::NUMBER, "0"), equal);
}


 Expression* BuiltInFunctions::eq(const std::vector<Expression*>& first, const std::vector<Expression*>& second)
{
	if (first.size() == second.size())
	{
		for (size_t i = 0; i < first.size(); i++)
		{
			if (first[i]->getToken().toNumber() != second[i]->getToken().toNumber())
				return new Number(Token(0, TokenType::NUMBER, "0"), false);
		}
		return new Number(Token(0, TokenType::NUMBER, "1"), true);
	}
	return new Number(Token(0, TokenType::NUMBER, "0"), false);
}

 Expression* BuiltInFunctions::eq(double first, const std::vector<Expression*>& second)
{
	bool equal = (second.size() == 1 && first == second[0]->getToken().toNumber());
	if (equal)
		return new Number(Token(0, TokenType::NUMBER, "1"), equal);
	else
		return new Number(Token(0, TokenType::NUMBER, "0"), equal);
}

 Expression* BuiltInFunctions::le(double first, double second)
{
	bool lessThan = first < second;

	if (lessThan)
		return new Number(Token(0, TokenType::NUMBER, "1"), lessThan);
	else
		return new Number(Token(0, TokenType::NUMBER, "0"), lessThan);
}

 Expression* BuiltInFunctions::le(const std::vector<Expression*>& first, const std::vector<Expression*>& second)
{
	bool lessThan = first.size() < second.size();

	if (lessThan)
		return new Number(Token(0, TokenType::NUMBER, "1"), lessThan);
	else
		return new Number(Token(0, TokenType::NUMBER, "0"), lessThan);
}

 Expression* BuiltInFunctions::nand(double first, double second)
{
	bool isNand = !first || !second;

	if (isNand)
		return new Number(Token(0, TokenType::NUMBER, "1"), isNand);
	else
		return new Number(Token(0, TokenType::NUMBER, "0"), isNand);
}

 Expression* BuiltInFunctions::nand(const std::vector<Expression*>& first, const std::vector<Expression*>& second)
{
	bool firstExpr, secondExpr;
	firstExpr = first.size();
	secondExpr = second.size();
	bool isNand = !firstExpr || !secondExpr;

	if (isNand)
		return new Number(Token(0, TokenType::NUMBER, "1"), isNand);
	else
		return new Number(Token(0, TokenType::NUMBER, "0"), isNand);	
}

  Expression* BuiltInFunctions::length(const std::vector<Expression*>& list, int)
{
	return new Number(Token(0, TokenType::NUMBER, std::to_string(list.size())), list.size());
}

 Expression* BuiltInFunctions::length(double num)
{
	return new Number(Token(0, TokenType::NUMBER, std::to_string(-1)), -1);
}

  Expression* BuiltInFunctions::head(const std::vector<Expression*>& list, int)
{
	if (list[0]->getToken().type == TokenType::NUMBER)
	{
		return new Number(Token(0, TokenType::NUMBER, list[0]->getToken().lexeme), list[0]->getToken().toNumber());
	}
}

  Expression* BuiltInFunctions::tail(const std::vector<Expression*>& list, int)
  {
	  std::vector<Expression*> result;

	  if (list[0]->getToken().type == TokenType::NUMBER)
	  {
		  for (size_t i = 1; i < list.size(); i++)
		  {
			  result.push_back(new Number(Token(0, TokenType::NUMBER, list[i]->getToken().lexeme), list[i]->getToken().toNumber()));
		  }
		  return  new FiniteListLiteral(Token(0, TokenType::LIST, "list"), result);
	  }
  }

 Expression* BuiltInFunctions::list(double firstElement)
{
	return new InfiniteListLiteral(Token(0, TokenType::LIST, "list"), firstElement, 1);
}

 Expression* BuiltInFunctions::list(double firstElement, double step)
{
	return new InfiniteListLiteral(Token(0, TokenType::LIST, "list"), firstElement, step);
}

 Expression* BuiltInFunctions::list(double firstElement, double step, double maxElements)
{
	std::vector<Expression*> result;

	for (size_t i = 0; i < maxElements; i++)
	{
		result.push_back(new Number(Token(0, TokenType::NUMBER, std::to_string(firstElement + i * step)), firstElement + i * step));
	}
	return new FiniteListLiteral(Token(0, TokenType::LIST, "list"), result);
}

 Expression* BuiltInFunctions::concat(const std::vector<Expression*>& first, const std::vector<Expression*>& second)
{
	std::vector<Expression*> result;

	if (first[0]->getToken().type == TokenType::NUMBER && second[0]->getToken().type == TokenType::NUMBER)
	{

		for (int i = 0; i < first.size(); i++)
		{
			result.push_back(new Number(Token(0, TokenType::NUMBER, first[i]->getToken().lexeme), first[i]->getToken().toNumber()));
		}

		for (int i = 0; i < second.size(); i++)
		{
			result.push_back(new Number(Token(0, TokenType::NUMBER, second[i]->getToken().lexeme), second[i]->getToken().toNumber()));
		}

		return  new FiniteListLiteral(Token(0, TokenType::LIST, "list"), result);
	}
}

 Expression* BuiltInFunctions::toInt(double num)
{
	return new Number(Token(0, TokenType::NUMBER, std::to_string(int(num))), double(int(num)));
}

 Expression* BuiltInFunctions::add(double first, double second)
{
	return new Number(Token(0, TokenType::NUMBER, std::to_string(first + second)), first + second);
}

 Expression* BuiltInFunctions::sub(double first, double second)
{
	return new Number(Token(0, TokenType::NUMBER, std::to_string(first - second)), first - second);
}

 Expression* BuiltInFunctions::mul(double first, double second)
{
	return new Number(Token(0, TokenType::NUMBER, std::to_string(first * second)), first * second);
}

 Expression* BuiltInFunctions::div(double first, double second)
{
	return new Number(Token(0, TokenType::NUMBER, std::to_string(first / second)), first / second);
}

  Expression* BuiltInFunctions::sqrt(double num)
{
	return new Number(Token(0, TokenType::NUMBER, std::to_string(std::sqrt(num))), std::sqrt(num));
}

  Expression* BuiltInFunctions::ifStmt(Expression* expr, double first, double second)
{
	if (expr->getToken().type == TokenType::NUMBER)
	{
		if (expr->getToken().toNumber())
			return new Number(Token(expr->getToken().line, TokenType::NUMBER, std::to_string(first)), first);
		else
			return new Number(Token(expr->getToken().line, TokenType::NUMBER, std::to_string(second)), second);
	}
	else if (expr->getToken().type == TokenType::LIST)
	{
		if (static_cast<FiniteListLiteral*> (expr)->expressions.size() != 0)
			return new Number(Token(expr->getToken().line, TokenType::NUMBER, std::to_string(first)), first);
		else
			return new Number(Token(expr->getToken().line, TokenType::NUMBER, std::to_string(second)), second);
	}

}

 Expression* BuiltInFunctions::ifStmt(Expression* expr, const std::vector<Expression*>& first, const std::vector<Expression*>& second)
{
	if (expr->getToken().type == TokenType::NUMBER)
	{
		if (expr->getToken().toNumber())
			return new FiniteListLiteral(Token(0, TokenType::LIST, "list"), first);
		else
			return new FiniteListLiteral(Token(0, TokenType::LIST, "list"), second);
	}
	else if (expr->getToken().type == TokenType::LIST)
	{
		if (static_cast<FiniteListLiteral*> (expr)->expressions.size() != 0)
			return new FiniteListLiteral(Token(0, TokenType::LIST, "list"), first);
		else
			return new FiniteListLiteral(Token(0, TokenType::LIST, "list"), second);
	}

}

 Expression* BuiltInFunctions::mod(int first, int second)
{
	int result = first % second;
	return new Number(Token(0, TokenType::NUMBER, std::to_string(result)), result);
};

 string_code hashit(std::string const& inString) {
	if (inString == "eq") return string_code::eq;
	if (inString == "le") return string_code::le;
	if (inString == "nand") return string_code::nand;
	if (inString == "length") return string_code::length;
	if (inString == "head") return string_code::head;
	if (inString == "tail") return string_code::tail;
	if (inString == "list") return string_code::list;
	if (inString == "concat") return string_code::concat;
	if (inString == "if") return string_code::ifStmt;
	if (inString == "read") return string_code::read;
	if (inString == "write") return string_code::write;
	if (inString == "int") return string_code::toInt;
	if (inString == "add") return string_code::add;
	if (inString == "sub") return string_code::sub;
	if (inString == "mul") return string_code::mul;
	if (inString == "div") return string_code::div;
	if (inString == "mod") return string_code::mod;
	if (inString == "sqrt") return string_code::sqrt;

	return string_code::NULLCODE;
}

 string_code BuiltInFunctions::find(std::string funcName)
{
	return hashit(funcName);
}

 Expression* BuiltInFunctions::execute(string_code fncName, std::vector<Expression*> params, int line)
{
	 if (params.size() == 0 && fncName != string_code::read)
	 {
		 throw new InterpreterException("Invalid number of parameters for function call!", line);
	 }
	switch (fncName)
	{
	case string_code::eq:
		return eq(params);
		break;
	case string_code::le:
		return le(params);
		break;
	case string_code::nand:
		return nand(params);
		break;
	case string_code::length:
		return length(params);
		break;
	case string_code::head:
		return head(params);
		break;
	case string_code::tail:
		return tail(params);
		break;
	case string_code::list:
		return list(params);
		break;
	case string_code::read:
		return read(params);
		break;
	case string_code::concat:
		return concat(params);
		break;
	case string_code::toInt:
		return toInt(params);
		break;
	case string_code::add:
		return add(params);
		break;
	case string_code::sub:
		return sub(params);
		break;
	case string_code::mul:
		return mul(params);
		break;
	case string_code::div:
		return div(params);
		break;
	case string_code::sqrt:
		return sqrt(params);
		break;
	case string_code::ifStmt:
		return ifStmt(params);
		break;
	case string_code::mod:
		return mod(params);
		break;
	case string_code::write:
		return write(params);
		break;

	default:
		return nullptr;
		break;
	}
}

  Expression* BuiltInFunctions::eq(std::vector<Expression*> params)
{

	if (params.size() != 2)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"eq\"!", params[0]->getToken().line);
	}
	TokenType firstParamType = params[0]->getToken().type;
	TokenType secondParamType = params[1]->getToken().type;


	Expression* result = nullptr; 

	if (firstParamType == TokenType::NUMBER && secondParamType == TokenType::NUMBER)
	{
		result = eq(params[0]->getToken().toNumber(), params[1]->getToken().toNumber());
	}
	else if (firstParamType == TokenType::LIST && secondParamType == TokenType::LIST)
	{
		result = eq(static_cast<FiniteListLiteral*> (params[0])->expressions, static_cast<FiniteListLiteral*> (params[1])->expressions);
	}
	else if (firstParamType == TokenType::LIST && secondParamType == TokenType::NUMBER)
	{
		result = eq(params[1]->getToken().toNumber(), static_cast<FiniteListLiteral*> (params[0])->expressions);
	}
	else if (firstParamType == TokenType::NUMBER && secondParamType == TokenType::LIST)
	{
		result = eq(params[0]->getToken().toNumber(), static_cast<FiniteListLiteral*> (params[1])->expressions);
	}
	
	return result;
}

  

 Expression* BuiltInFunctions::le(std::vector<Expression*> params)
{

	if (params.size() != 2)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"le\"!", params[0]->getToken().line);
	}

	
	Expression* result = nullptr;

	TokenType firstParamType = params[0]->getToken().type;
	TokenType secondParamType = params[1]->getToken().type;
	if (firstParamType == TokenType::NUMBER && secondParamType == TokenType::NUMBER)
	{
		result = le(params[0]->getToken().toNumber(), params[1]->getToken().toNumber());
	}
	else if (firstParamType == TokenType::LIST && secondParamType == TokenType::LIST)
	{
		result = le(static_cast<FiniteListLiteral*> (params[0])->expressions, static_cast<FiniteListLiteral*> (params[1])->expressions);
	}
	else
		throw new InterpreterException("Parameters must be of type: 2xLIST/2xNUMBER for function call \"le\"!", params[0]->getToken().line);

	return result;
}

  Expression* BuiltInFunctions::nand(std::vector<Expression*> params)
{
	if (params.size() != 2)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"nand\"!", params[0]->getToken().line);
	}


	Expression* result = nullptr;

	TokenType firstParamType = params[0]->getToken().type;
	TokenType secondParamType = params[1]->getToken().type;
	if (firstParamType == TokenType::NUMBER && secondParamType == TokenType::NUMBER)
	{
		result = nand(params[0]->getToken().toNumber(), params[1]->getToken().toNumber());
	}
	else if (firstParamType == TokenType::LIST && secondParamType == TokenType::LIST)
	{
		result = nand(static_cast<FiniteListLiteral*> (params[0])->expressions, static_cast<FiniteListLiteral*> (params[1])->expressions);
	}
	else
		throw new InterpreterException("Parameters must be of type: 2xLISTS/2xNUMBER for function call \"nand\"!", params[0]->getToken().line);

	return result;
}

  Expression* BuiltInFunctions::length(std::vector<Expression*> params)
{
	if (params.size() != 1)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"length\"!", params[0]->getToken().line);
	}

	Expression* result = nullptr;

	TokenType paramType = params[0]->getToken().type;

	if (paramType == TokenType::NUMBER)
	{
		result = length(params[0]->getToken().toNumber());
	}
	else if (paramType == TokenType::LIST)
	{
		result = length(static_cast<FiniteListLiteral*> (params[0])->expressions, 0);
	}
	else
		throw new InterpreterException("Parameters must be of type: LIST/NUMBER for function call \"length\"!", params[0]->getToken().line);


	return result;
}

 Expression* BuiltInFunctions::head(std::vector<Expression*> params)
{
	if (params.size() != 1)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"head\"!", params[0]->getToken().line);
	}

	Expression* result = nullptr;
	TokenType paramType = params[0]->getToken().type;

	if (paramType == TokenType::LIST)
	{
		result = head(static_cast<FiniteListLiteral*> (params[0])->expressions, 0);
	}
	else
		throw new InterpreterException("Parameters must be of type: LIST for function call \"head\"!", params[0]->getToken().line);

	return result;
}

  Expression* BuiltInFunctions::tail(std::vector<Expression*> params)
{
	if (params.size() != 1)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"tail\"!", params[0]->getToken().line);
	}

	Expression* result = nullptr;

	TokenType paramType = params[0]->getToken().type;

	if (paramType == TokenType::LIST)
	{
		result = tail(static_cast<FiniteListLiteral*> (params[0])->expressions, 0);
	}
	else
		throw new InterpreterException("Parameters must be of type: LIST for function call \"tail\"!", params[0]->getToken().line);\

	return result;
}

 Expression* BuiltInFunctions::list(std::vector<Expression*> params)
{
	if (params.size() > 3 || params.size() == 0)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"list\"!", params[0]->getToken().line);
	}

	Expression* result = nullptr;

	if (params.size() == 1)
	{
		TokenType paramType = params[0]->getToken().type;

		if (paramType == TokenType::NUMBER)
		{
			result = list(params[0]->getToken().toNumber());
		}
		else
			throw new InterpreterException("Parameters must be of type: NUMBER for function call \"list\"!", params[0]->getToken().line);
	}
	else if (params.size() == 2)
	{
		TokenType firstParamType = params[0]->getToken().type;
		TokenType secParamType = params[1]->getToken().type;

		if (firstParamType == TokenType::NUMBER && secParamType == TokenType::NUMBER)
		{
			result = list(params[0]->getToken().toNumber(), params[1]->getToken().toNumber());
		}
		else
			throw new InterpreterException("Parameters must be of type: NUMBER for function call \"list\"!", params[0]->getToken().line);
	}
	else if (params.size() == 3)
	{
		TokenType firstParamType = params[0]->getToken().type;
		TokenType secParamType = params[1]->getToken().type;
		TokenType thirdParamType = params[2]->getToken().type;

		if (firstParamType == TokenType::NUMBER && secParamType == TokenType::NUMBER && thirdParamType == TokenType::NUMBER)
		{
			result = list(params[0]->getToken().toNumber(), params[1]->getToken().toNumber(), params[2]->getToken().toNumber());
		}
		else
			throw new InterpreterException("Parameters must be of type: NUMBER for function call \"list\"!", params[0]->getToken().line);
	}

	return result;

}

 Expression* BuiltInFunctions::read(std::vector<Expression*> params)
{
	if (params.size() != 0)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"read\"!", params[0]->getToken().line);
	}

	Expression* result = nullptr;

	double num;
	std::cin >> num;
	std::cin.ignore();

	result = new Number(Token(0, TokenType::NUMBER, std::to_string(num)), num);

	return result;
}

  Expression* BuiltInFunctions::concat(std::vector<Expression*> params)
{
	if (params.size() != 2)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"concat\"!", params[0]->getToken().line);
	}

	Expression* result = nullptr;

	if (params[0]->getToken().type == TokenType::LIST && params[1]->getToken().type == TokenType::LIST)
	{
		result = concat(static_cast<FiniteListLiteral*> (params[0])->expressions, static_cast<FiniteListLiteral*> (params[1])->expressions);
	}
	else
		throw new InterpreterException("Parameters must be of type: LIST for function call \"concat\"!", params[0]->getToken().line);

	return result;
}

 Expression* BuiltInFunctions::toInt(std::vector<Expression*> params)
{
	if (params.size() != 1)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"int\"!", params[0]->getToken().line);
	}
	Expression* result = nullptr;

	result = toInt(params[0]->getToken().toNumber());

	return result;
}

 Expression* BuiltInFunctions::add(std::vector<Expression*> params)
{
	if (params.size() != 2)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"add\"!", params[0]->getToken().line);
	}

	Expression* result = nullptr;

	result = add(params[0]->getToken().toNumber(), params[1]->getToken().toNumber());

	return result;
}

 Expression* BuiltInFunctions::sub(std::vector<Expression*> params)
{
	if (params.size() != 2)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"sub\"!", params[0]->getToken().line);
	}

	Expression* result = nullptr;

	result = sub(params[0]->getToken().toNumber(), params[1]->getToken().toNumber());

	return result;
}

  Expression* BuiltInFunctions::mul(std::vector<Expression*> params)
{
	if (params.size() != 2)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"mul\"!", params[0]->getToken().line);
	}

	Expression* result = nullptr;
	result = mul(params[0]->getToken().toNumber(), params[1]->getToken().toNumber());

	return result;
}

 Expression* BuiltInFunctions::div(std::vector<Expression*> params)
{
	if (params.size() != 2)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"div\"!", params[0]->getToken().line);
	}
	if (params[1]->getToken().toNumber() == 0)
	{
		throw new InterpreterException("Cannot divide by 0!", params[0]->getToken().line);
	}

	Expression* result = nullptr;

	result = div(params[0]->getToken().toNumber(), params[1]->getToken().toNumber());

	return result;
}

  Expression* BuiltInFunctions::sqrt(std::vector<Expression*> params)
{
	if (params.size() != 1)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"sqrt\"!", params[0]->getToken().line);
	}
	Expression* result = nullptr;

	result = sqrt(params[0]->getToken().toNumber());

	return result;
}

  Expression* BuiltInFunctions::ifStmt(std::vector<Expression*> params)
{
	if (params.size() != 3)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"if\"!", params[0]->getToken().line);
	}
	TokenType secParamType = params[1]->getToken().type;
	TokenType thirdParamType = params[2]->getToken().type;

	Expression* result = nullptr;

	if (secParamType == TokenType::NUMBER && thirdParamType == TokenType::NUMBER)
	{
		result = ifStmt(params[0], params[1]->getToken().toNumber(), params[2]->getToken().toNumber());
	}
	else if (secParamType == TokenType::LIST && thirdParamType == TokenType::LIST)
	{
		result = ifStmt(params[0], static_cast<FiniteListLiteral*> (params[1])->expressions, static_cast<FiniteListLiteral*> (params[2])->expressions);
	}
	else
		throw new InterpreterException("Second parameter and third parameter must be the same type for function call \"if\"!", params[0]->getToken().line);

	return result;

}

  Expression* BuiltInFunctions::mod(std::vector<Expression*> params)
{
	if (params.size() != 2)
	{
		throw new InterpreterException("Invalid number of parameters for function call \"mod\"!", params[0]->getToken().line);
	}
	double firstNum = params[0]->getToken().toNumber();
	double secondNum = params[1]->getToken().toNumber();

	Expression* result = nullptr;

	if (firstNum == (int)firstNum && secondNum == (int)secondNum)
	{
		result = mod((int)firstNum, (int)secondNum);
	}
	else
		throw new InterpreterException("Operation mod only available for INTEGERS!", params[0]->getToken().line);

	return result;
}

  Expression* BuiltInFunctions::write(std::vector<Expression*> params)
  {

	  if (params.size() != 1)
	  {
		  throw new InterpreterException("Invalid number of parameters for function call \"write\"!", params[0]->getToken().line);
	  }

	  Expression* result = nullptr;

	  if (params[0]->getToken().type == TokenType::LIST)
	  {

		  result = static_cast<FiniteListLiteral*> (params[0])->getCopy();
	  }
	  else if (params[0]->getToken().type == TokenType::NUMBER)
	  {
		  result = params[0]->getCopy();
	  }
	  else 
		  throw new InterpreterException("Not valid argument for \"write\"!", params[0]->getToken().line);

	  return result;
  }
