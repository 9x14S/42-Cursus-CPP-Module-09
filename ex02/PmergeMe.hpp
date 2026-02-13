#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <iostream>
# include <string>
# include <vector>
# include <deque>
# include <ctime>
# include <cstdlib>
# include <sys/time.h>

class PmergeMe
{
private:
	std::vector<int>	_vec;
	std::deque<int>		_deq;
	double				_vectime;
	double				_deqtime;

	void				sort_vec(std::vector<int>& arr);
	void				insert_vec(std::vector<int>& mainChain, int val, size_t limit);

	void				sort_deque(std::deque<int>& arr);
	void				insert_deque(std::deque<int>& mainChain, int val, size_t limit);

	size_t				get_jacob_num(size_t n);

public:
	// Orthodox Canonical Form
	PmergeMe( void );
	PmergeMe( const PmergeMe& other );
	PmergeMe& operator=( const PmergeMe& other );
	~PmergeMe( void );

	void	parse( int argc, char** argv );
	void	execute( void );

	template <typename T>
	void	print_seq( const T& container, const std::string& prefix )
	{
		std::cout << prefix;
		size_t limit = (container.size() > 5) ? 5 : container.size();
		for (size_t i = 0; i < limit; i++)
			std::cout << container[i] << " ";
		if (container.size() > 5)
			std::cout << "[...]";
		std::cout << std::endl;
	}
};

#endif // PMERGEME_HPP
