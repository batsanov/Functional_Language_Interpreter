#include "../ProjectInterpreter/Interpreter.h"
#include "../ProjectInterpreter/Parser.h"
#include "../ProjectInterpreter/Reader.h"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "string"

Expression* evaluate(std::string input, Reader& reader, Parser& parser, Interpreter& interpreter) {
	reader.updateSource(input);
	std::vector<Token> tokens = reader.tokenize();

	parser.updateTokens(tokens);
	interpreter.updateAST(parser.isDeclaration(), parser.parseLine());
	Expression* result = interpreter.evaluateAST();
	return result;
}

void clear(Reader& reader, Parser& parser, Interpreter& interpreter)
{
	reader.clear();
	parser.clear();
	interpreter.clear();
}

TEST_CASE("The interpreter working correctly with built in function eq")
{
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	std::string expectedResult;
	Expression* result;

	input = "eq(1,2)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "0.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "eq(2,2)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "1.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "eq([1 2 3],[1 2 3])";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "1.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

	input = "eq([1 2 3],[1 2 3 4 5])";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "0.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

}


TEST_CASE("The interpreter working correctly with built in function le")
{
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	std::string expectedResult;
	Expression* result;

	input = "le(1,2)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "1.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "le(1,0)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "0.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "le([1 2 3],[1 2 3])";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "0.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

	input = "le([1 2 3],[1 2 3 4 5])";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "1.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

}


TEST_CASE("The interpreter working correctly with built in function nand")
{
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	std::string expectedResult;
	Expression* result;

	input = "nand(1,1)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "0.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "nand(1,0)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "1.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "nand([1 2 3],[1])";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "0.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

	input = "nand([1],[2])";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "0.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

}

TEST_CASE("The interpreter working correctly with built in function length")
{
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	std::string expectedResult;
	Expression* result;

	input = "length(1)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "-1.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "length(5)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "-1.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "length([1 2 3])";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "3.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

	input = "length([1])";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "1.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

}

TEST_CASE("The interpreter working correctly with built in function int")
{
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	std::string expectedResult;
	Expression* result;

	input = "int(1.123)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "1.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "int(123.123)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "123.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "int(-123.123)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "-123.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

}

TEST_CASE("The interpreter working correctly with built in function add")
{
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	std::string expectedResult;
	Expression* result;

	input = "add(1,2)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "3.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "add(123,3)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "126.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "add(-123,3)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "-120.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

}

TEST_CASE("The interpreter working correctly with built in function sub")
{
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	std::string expectedResult;
	Expression* result;

	input = "sub(1,2)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "-1.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "sub(123,3)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "120.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "sub(-123,3)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "-126.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

}

TEST_CASE("The interpreter working correctly with built in function mul")
{
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	std::string expectedResult;
	Expression* result;

	input = "mul(1,2)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "2.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "mul(123,3)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "369.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "mul(-123,3)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "-369.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

}

TEST_CASE("The interpreter working correctly with built in function div")
{
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	std::string expectedResult;
	Expression* result;

	input = "div(4,2)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "2.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "div(6,3)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "2.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "div(-12,3)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "-4.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

}

TEST_CASE("The interpreter working correctly with built in function sqrt")
{
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	std::string expectedResult;
	Expression* result;

	input = "sqrt(4)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "2.00";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "sqrt(6)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "2.45";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);


	input = "sqrt(12)";
	result = evaluate(input, reader, parser, interpreter);
	expectedResult = "3.46";

	REQUIRE(result->print() == expectedResult);
	clear(reader, parser, interpreter);

}


TEST_CASE("ERRORS")
{
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	std::string expectedResult;
	Expression* result;

	input = "sRWt(6)";
	REQUIRE_THROWS(evaluate(input, reader, parser, interpreter));
	clear(reader, parser, interpreter);

	input = "12 13";
	REQUIRE_THROWS(evaluate(input, reader, parser, interpreter));
	clear(reader, parser, interpreter);

	input = "eq(1)";
	REQUIRE_THROWS(evaluate(input, reader, parser, interpreter));
	clear(reader, parser, interpreter);

	input = "mod()";
	REQUIRE_THROWS(evaluate(input, reader, parser, interpreter));
	clear(reader, parser, interpreter);

	input = "length(1,2,3)";
	REQUIRE_THROWS(evaluate(input, reader, parser, interpreter));
	clear(reader, parser, interpreter);

	input = "div(5,0)";
	REQUIRE_THROWS(evaluate(input, reader, parser, interpreter));
	clear(reader, parser, interpreter);

	input = "men!o -> 15";
	REQUIRE_THROWS(evaluate(input, reader, parser, interpreter));
	clear(reader, parser, interpreter);

	input = "as&wa -> [ 1 2 3]";
	REQUIRE_THROWS(evaluate(input, reader, parser, interpreter));
	clear(reader, parser, interpreter);
}
