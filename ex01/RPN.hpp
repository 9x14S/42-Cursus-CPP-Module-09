#ifndef RPN_HPP
# define RPN_HPP

# include <string>

class RPN
{
private:
	// Orthodox Canonical Form
	RPN();
	RPN(const RPN &copy);
	RPN &operator=(const RPN &assign);
	~RPN();

public:
	static long eval( const std::string &expression );
};

#endif /* RPN_HPP */
