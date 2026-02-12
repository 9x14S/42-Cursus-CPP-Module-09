#include <exception>
#include <stack>
#include <string>

#include <cctype>

#include "RPN.hpp"

// Orthodox Canonical Form (private)
/// Default Constructor
RPN::RPN( void ) {}

/// Copy Constructor
RPN::RPN( const RPN &copy )
{
	*this = copy;
}

/// Destructor
RPN::~RPN( void ) {}

/// Copy Assignment Operator
RPN	&RPN::operator=( const RPN &assign )
{
	(void)assign;
	return *this;
}

long RPN::eval( const std::string &expression )
{
	std::stack<long> stack;
	for (size_t i = 0; i < expression.length(); i++)
	{
		switch (expression[i])
		{
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (std::isdigit(expression[i]))
					stack.push(expression[i] - '0');
				break;
			{
			case '+':
			case '*':
			case '-':
			case '/':
				long a = stack.top();
				stack.pop();
				long b = stack.top();
				stack.pop();
				switch (expression[i])
				{
				case '+':
					stack.push(a + b);
					break;
				case '*':
					stack.push(a * b);
					break;
				case '-':
					stack.push(b - a);
					break;
				case '/':
					stack.push(b / a);
					break;
				}
			}
			case ' ':
				continue;
			default:
				throw (std::exception());
		}
	}
	if (stack.size() != 1)
		throw (std::exception());
	return (stack.top());
}
