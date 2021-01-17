#ifndef OPERATOR_HPP
#define OPERATOR_HPP

#include <string>

#define LEFT true
#define RIGHT false

struct Operator
{
	std::string token;
	int type;
	int precedence;
	bool associative;
};

#endif
