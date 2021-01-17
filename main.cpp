#include "Lexer.hpp"
#include "Evaluator.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cerr << "Usage : " << av[0] << " [expr]" << std::endl;
		std::cerr << "Only handling +, -, *, /, \% (modulos) and exponentiation." << std::endl;
		return (1);
	}
	std::string expr(av[1]);
	Evaluator ev(expr);

	std::cout << "RPN    : " << ev;
	std::cout << "Value  : " << ev.evaluate() << std::endl;
	return (0);
}
