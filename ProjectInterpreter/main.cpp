#include <iostream>
#include <fstream>
#include <streambuf>
#include <string>
#include "Reader.h"
#include "Parser.h"
#include "Interpreter.h"


void run(std::string input, Reader& reader, Parser& parser, Interpreter& interpreter)
{
	reader.updateSource(input);
	std::vector<Token> tokens = reader.tokenize();

	if (tokens.size() == 0)
		return;
	parser.updateTokens(tokens);
	interpreter.updateAST(parser.isDeclaration(), parser.parseLine());
	interpreter.interpret();
	
}

void runPrompt() {
	Reader reader;
	Parser parser;
	Interpreter interpreter;
	std::string input;
	for (; ;)
	{
		interpreter.clear();
		reader.clear();
		parser.clear();

		std::cout << "user> ";
		if (!std::getline(std::cin, input))
			break;
		try
		{
			run(input, reader, parser, interpreter);
		}
		catch (const std::exception* except)
		{
			std::cout << except->what();
			delete except;
		}
	}

}

void runFile(char* argv) {
	std::ifstream file;
	file.open(argv);

	if (file.is_open())
	{
		try
		{
			Reader reader;
			Parser parser;
			Interpreter interpreter;
			std::string currentLine;

			while (std::getline(file, currentLine))
			{
				reader.clear();
				parser.clear();
				interpreter.clear();
				run(currentLine, reader, parser, interpreter);
			}
		}
		catch (const std::exception* except)
		{
			std::cout << except->what();
			delete except;
		}
	}
	else
		throw std::runtime_error("Unable to open file!");
}

int main(int args, char* argv[])
{
	if (args == 1)
	{
		runPrompt();
	}
	else
	{
		runFile(argv[1]);
	}

	return 0;
}


