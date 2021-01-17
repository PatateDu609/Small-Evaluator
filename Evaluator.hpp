#ifndef EVALUATOR_HPP
#define EVALUATOR_HPP

#include "Lexer.hpp"
#include "Fixed.hpp"
#include <deque>

class Evaluator
{
public:
	friend std::ostream& operator<<(std::ostream& os, const Evaluator& eval);

	Evaluator(const std::string& expr);

	Fixed evaluate() const;

private:
	const std::string& expression;

	Lexer lexer;
	std::deque<std::string> RPN;

	void shunting_yard();
	Fixed to_scalar(const std::string& str) const;
	std::string apply(const std::string& a, const std::string& op, const std::string& b) const;
};

#endif
