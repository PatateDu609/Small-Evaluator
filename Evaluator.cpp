#include "Evaluator.hpp"
#include <stack>
#include <sstream>
#include <cmath>

Evaluator::Evaluator(const std::string& expr) : expression(expr), lexer(expression)
{
	shunting_yard();
}

Fixed Evaluator::evaluate() const
{
	std::stack<std::string> values;
	std::string a;
	std::string b;
	std::deque<std::string> RPN = this->RPN;

	while (!RPN.empty())
	{
		if (!lexer.is_operator(RPN.front()))
			values.push(RPN.front());
		else
		{
			b = values.top();
			values.pop();
			a = values.top();
			values.pop();

			values.push(apply(a, RPN.front(), b));
		}
		RPN.pop_front();
	}
	return (to_scalar(values.top()));
}

void Evaluator::shunting_yard()
{
	std::vector<std::string> tokens = lexer.getTokens();
	std::stack<std::string> operators;
	int precedence;
	bool assoc;

	for (size_t i = 0; i < tokens.size(); i++)
	{
		if (!lexer.is_operator(tokens[i]))
			RPN.push_back(tokens[i]);
		else
		{
			if (operators.empty() || tokens[i] == "(" || operators.top() == "(")
			{
				operators.push(tokens[i]);
				continue ;
			}
			else if (tokens[i] == ")")
			{
				while (!operators.empty() && operators.top() != "(")
				{
					RPN.push_back(operators.top());
					operators.pop();
				}
				operators.pop();
			}
			else
			{
				precedence = lexer.get_precedence(tokens[i]);
				assoc = lexer.get_assoc(tokens[i]);
				while
				(
					!operators.empty() && operators.top() != "(" &&
					(
						(assoc == LEFT && precedence <= lexer.get_precedence(operators.top())) ||
						(assoc == RIGHT && precedence <= lexer.get_precedence(operators.top()))
					)
				)
				{
					RPN.push_back(operators.top());
					operators.pop();
				}
				operators.push(tokens[i]);
			}
		}
	}
	while (!operators.empty())
	{
		RPN.push_back(operators.top());
		operators.pop();
	}
}

Fixed Evaluator::to_scalar(const std::string& str) const
{
	std::istringstream iss(str);
	Fixed result;

	iss >> result;
	return result;
}

std::string Evaluator::apply(const std::string& a, const std::string& op, const std::string& b) const
{
	Fixed da = to_scalar(a);
	Fixed db = to_scalar(b);
	std::ostringstream oss;

	if (op == "+")
		oss << da + db;
	else if (op == "-")
		oss << da - db;
	else if (op == "*")
		oss << da * db;
	else if (op == "/")
		oss << da / db;
	else if (op == "%")
		oss << da.toInt() % db.toInt();
	else if (op == "^")
		oss << std::pow(da.toFloat(), db.toFloat());
	return oss.str();
}

std::ostream& operator<<(std::ostream& os, const Evaluator& eval)
{
	if (eval.RPN.empty())
		return (os);

	std::cout << eval.expression << " -> [ " << eval.RPN.front();
	for (size_t i = 1; i < eval.RPN.size(); i++)
		std::cout << ", " << eval.RPN[i];
	std::cout << " ]" << std::endl;
	return (os);
}
