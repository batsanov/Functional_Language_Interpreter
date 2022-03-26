#include "Tokenizer.h"
#include "InterpreterException.h"
size_t Tokenizer::line = 0;

 Tokenizer::Tokenizer(const std::string input) : input(input), index(0) {
	++line;
}

 Token Tokenizer::next()
{
	std::string fullString = input;

	while (index < input.size())
	{
		char c = peek();

		switch (c)
		{
		case '\n':
			line++;
			break;
		case ' ':
		case '\t':
			break;
		case ',':
			index++;
			return Token(line, TokenType::COMMA, ",");
		case '[':
			index++;
			return Token(line, TokenType::LEFT_SQUARE_BRACKET, "[");
		case ']':
			index++;
			return Token(line, TokenType::RIGHT_SQUARE_BRACKET, "]");
		case '(':
			index++;
			return Token(line, TokenType::LEFT_PAREN, "(");
		case ')':
			index++;
			return Token(line, TokenType::RIGHT_PAREN, ")");
		case '#':
			index++;
			return Token(line, TokenType::ARGUMENT, fullString.substr(index++, 1));
		case '-':

			index++;
			if (isDigit(peek()))
				return Token(line, TokenType::NUMBER, readNumber(true));

			else if (isArrow(peek())) return Token(line, TokenType::ARROW, fullString.substr(index++ - 1, 2));
			else
			{
				index++;
				throw new InterpreterException("Invalid minus at input!", line);
			}
		default:
			if (isDigit(c))
			{
				return Token(line, TokenType::NUMBER, readNumber(false));
			}
			else if (isAlpha(c))
			{
				return Token(line, TokenType::IDENTIFIER, readIdentifier());
			}
			
			else throw new InterpreterException("Invalid argument!", line); 
			index++;
		}
		index++;
	}

	return Token(line, TokenType::END, "");
}

bool Tokenizer::isArrow(char c) {
	 return c == '>';
 }

  bool Tokenizer::isDigit(char c) {
	 return c >= '0' && c <= '9';
 }

  char Tokenizer::peekNext() {
	 if (index + 1 >= input.length()) return '\0';
	 return input[index + 1];
 }

  char Tokenizer::peek() {
	 if (index >= input.length()) return '\0';
	 return input[index];
 }

  bool Tokenizer::isAlpha(char c) {
	 return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
 }

    std::string Tokenizer::readNumber(bool isNegative) {
	 int start = index;
	 while (isDigit(peek())) index++;

	 if (peek() == '.' && isDigit(peekNext())) {

		 index++;

		 while (isDigit(peek())) index++;
	 }

	 if (isNegative)
		 return input.substr(start - 1, index - start + 1);

	 return input.substr(start, index - start);
 }

   bool Tokenizer::isAlphaNumeric(char c) {
	  return isAlpha(c) || isDigit(c);
  }

    std::string Tokenizer::readIdentifier()
 {
		 int start = index;
		 while (isAlphaNumeric(peek())) index++;

		 return input.substr(start, index - start);
 }

   Token::Token(int line, TokenType type, std::string lexeme) : line(line), type(type), lexeme(lexeme) {}

   std::string Token::getLine() const {
	  std::ostringstream temp;
	  temp << line;

	  return temp.str();
  }

   double Token::toNumber() const {
	  if (type == TokenType::NUMBER || type == TokenType::ARGUMENT)
	  {
		  return std::stod(lexeme);
	  }

	  else throw std::exception("INVALID TRY TO CAST!");
  }

   void Token::printLine()
  {
	  std::cout << line << " ";
  }

   void Token::printType()
  {
	  switch (type)
	  {
	  case TokenType::COMMA: std::cout << "COMMA ";
		  break;
	  case TokenType::LEFT_SQUARE_BRACKET: std::cout << "LEFT_SQUARE_BRACKET ";
		  break;
	  case TokenType::RIGHT_SQUARE_BRACKET:std::cout << "RIGHT_SQUARE_BRACKET ";
		  break;
	  case TokenType::LEFT_PAREN:std::cout << "LEFT_PAREN ";
		  break;
	  case TokenType::RIGHT_PAREN:std::cout << "RIGHT_PAREN ";
		  break;
	  case TokenType::ARGUMENT:std::cout << "ARGUMENT ";
		  break;
	  case TokenType::ARROW:std::cout << "ARROW ";
		  break;
	  case TokenType::IDENTIFIER:std::cout << "IDENTIFIER ";
		  break;
	  case TokenType::END:std::cout << "END ";
		  break;
	  default:
		  break;
	  }
  }

   std::string Token::toString()
  {
	  return lexeme;
  }
