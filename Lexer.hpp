#ifndef LEXER_HPP
#define LEXER_HPP

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "Operator.hpp"

class Lexer
{
	friend std::ostream& operator<<(std::ostream& os, const Lexer& lex);

public:
	Lexer(const std::string& expression);

	std::vector<std::string> getTokens() const;
	bool is_operator(const std::string& str) const;
	int get_precedence(const std::string& op) const;
	bool get_assoc(const std::string& op) const;

private:
	std::vector<Operator> operators;
	const std::string& expression;

	std::vector<std::string> tokens;

	std::vector<std::string> split_tokens(const std::string& input) const;
	std::string::size_type find_next_operator(const std::string& input, const std::string::size_type& start) const;
	void tokenize(void);
};

#endif
