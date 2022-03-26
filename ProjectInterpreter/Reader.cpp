#include "Reader.h"

 void Reader::clear() {
	tokens.clear();
	source.clear();
}

void Reader::updateSource(std::string source)
{
	this->source = source;
}

 std::vector<Token>& Reader::tokenize()
{
	Tokenizer tokenizer(source);

	while (tokenizer.index < tokenizer.input.size())
	{
		tokens.push_back(tokenizer.next());
	}
	return tokens;
}

 int Reader::size()
{
	return tokens.size();
}
