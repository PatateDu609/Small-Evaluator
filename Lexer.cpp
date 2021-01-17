#include "Lexer.hpp"
#include <algorithm>

Lexer::Lexer(const std::string &expr) : expression(expr)
{
	Operator op;

	op.token = "+";
	op.associative = LEFT;
	op.precedence = 0;
	op.type = 1;
	operators.push_back(op);

	op.token = "-";
	op.associative = LEFT;
	op.precedence = 0;
	op.type = 1;
	operators.push_back(op);

	op.token = "-";
	op.associative = RIGHT;
	op.precedence = 1;
	op.type = 0;
	operators.push_back(op);

	op.token = "*";
	op.associative = LEFT;
	op.precedence = 2;
	op.type = 1;
	operators.push_back(op);

	op.token = "/";
	op.associative = LEFT;
	op.precedence = 2;
	op.type = 1;
	operators.push_back(op);

	op.token = "%";
	op.associative = LEFT;
	op.precedence = 2;
	op.type = 1;
	operators.push_back(op);

	op.token = "^";
	op.associative = RIGHT;
	op.precedence = 3;
	op.type = 1;
	operators.push_back(op);

	op.token = "(";
	op.associative = RIGHT;
	op.precedence = 4;
	op.type = 2;
	operators.push_back(op);

	op.token = ")";
	op.associative = LEFT;
	op.precedence = 4;
	op.type = 2;
	operators.push_back(op);

	std::reverse(operators.begin(), operators.end());

	if (expression.size())
		tokenize();
}

std::string::size_type Lexer::find_next_operator(const std::string& input, const std::string::size_type& start) const
{
	std::string::size_type found;
	std::vector<std::string::size_type> all;

	found = std::string::npos;
	for (std::size_t i = 0; i < operators.size(); i++)
	{
		found = input.find(operators[i].token, start);
		if (found != std::string::npos)
			all.push_back(found);
	}
	std::sort(all.begin(), all.end());
	return all.empty() ? std::string::npos : all[0];
}

std::vector<std::string> Lexer::split_tokens(const std::string& input) const
{
	std::vector<std::string> tokens;
	std::string::size_type found;
	std::string::size_type start;
	std::string before;
	bool done;

	start = 0;
	do
	{
		done = true;
		found = find_next_operator(input, start);
		if (found != std::string::npos)
		{
			done = false;
			before = "";
			if (found - start < input.size())
				before = input.substr(start, found - start);
			// std::cout << "start : " << input.substr(start) << ", found - start - 1 = " << found - start << ", before : " << before << ", found : " << input[found] << std::endl;
			if (before != input && before.size())
				tokens.push_back(before);
			tokens.push_back(std::string(1, (char)input[found]));
			start = found + 1;
		}
	} while (start < input.size() && !done);
	if (start < input.size())
		tokens.push_back(input.substr(start));
	return (tokens);
}

void Lexer::tokenize(void)
{
	std::istringstream iss(expression);
	std::string input;
	std::vector<std::string> loc_tokens;

	while (!iss.eof())
	{
		iss >> input;
		loc_tokens = split_tokens(input);
		tokens.insert(tokens.end(), loc_tokens.begin(), loc_tokens.end());
	}
}

std::ostream &operator<<(std::ostream &os, const Lexer &lex)
{
	if (lex.expression.empty() || lex.tokens.empty())
		return (os);

	os << lex.expression << " -> [ " << lex.tokens[0];
	for (std::size_t i = 1; i < lex.tokens.size(); i++)
		os << ", " << lex.tokens[i];
	os << " ]" << std::endl;
	return os;
}

std::vector<std::string> Lexer::getTokens() const
{
	return tokens;
}

bool Lexer::is_operator(const std::string& str) const
{
	for (size_t i = 0; i < operators.size(); i++)
		if (str == operators[i].token)
			return true;
	return false;
}

int Lexer::get_precedence(const std::string& op) const
{
	for (size_t i = 0; i < operators.size(); i++)
		if (op == operators[i].token)
			return operators[i].precedence;
	return -1;
}

bool Lexer::get_assoc(const std::string& op) const
{
	for (size_t i = 0; i < operators.size(); i++)
		if (op == operators[i].token)
			return operators[i].associative;
	return -1;
}
