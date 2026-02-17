#include <algorithm>
#include <iomanip>
#include <limits.h>

#include "PmergeMe.hpp"

// Orthodox Canonical Form
PmergeMe::PmergeMe() : _vectime(0), _deqtime(0)
{}

PmergeMe::PmergeMe(const PmergeMe& that)
{
	*this = that;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& that)
{
	if (this != &that)
	{
		_vec = that._vec;
		_deq = that._deq;
		_vectime = that._vectime;
		_deqtime = that._deqtime;
	}
	return *this;
}

PmergeMe::~PmergeMe()
{}

void PmergeMe::parse(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];
		if (arg.find_first_not_of("0123456789") != std::string::npos)
		{
			std::cerr << "Error: invalid input." << std::endl;
			exit(1);
		}
		long val = std::atol(arg.c_str());
		if (val < 0 || val > INT_MAX)
		{
			std::cerr << "Error: input out of range." << std::endl;
			exit(1);
		}
		_vec.push_back(static_cast<int>(val));
		_deq.push_back(static_cast<int>(val));
	}
}

size_t PmergeMe::get_jacob_num(size_t n)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;
	size_t prev = 0;
	size_t curr = 1;
	for (size_t i = 2; i <= n; ++i)
	{
		size_t next = curr + 2 * prev;
		prev = curr;
		curr = next;
	}
	return curr;
}

// Vector
void PmergeMe::insert_vec(std::vector<int>& main_chain, int val, size_t limit)
{
	std::vector<int>::iterator end = main_chain.begin() + limit;
	std::vector<int>::iterator pos = std::lower_bound(main_chain.begin(), end, val);
	main_chain.insert(pos, val);
}

void PmergeMe::sort_vec(std::vector<int>& arr)
{
	size_t n = arr.size();
	if (n < 2) return;

	bool is_uneven = (n % 2 != 0);
	int unpaired = 0;
	if (is_uneven)
	{
		unpaired = arr.back();
		arr.pop_back();
	}

	std::vector<std::pair<int, int> > pairs;
	for (size_t i = 0; i < arr.size(); i += 2)
	{
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
		else
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
	}

	std::vector<int> main_chain;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		main_chain.push_back(pairs[i].first);
	}
	sort_vec(main_chain);

	std::vector<int> pend;
	std::vector<int> result = main_chain;
	for (size_t i = 0; i < main_chain.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].first == main_chain[i])
			{
				pend.push_back(pairs[j].second);
				pairs.erase(pairs.begin() + j);
				break;
			}
		}
	}
	result.insert(result.begin(), pend[0]);
	size_t jacob_idx = 3;
	size_t inserted_count = 1;
	while (inserted_count < pend.size())
	{
		size_t next_jacobsthal = get_jacob_num(jacob_idx);
		size_t limit = next_jacobsthal - 1;

		if (limit >= pend.size()) limit = pend.size() - 1;

		size_t current = limit;
		while (current >= inserted_count)
		{
			int val = pend[current];

			std::vector<int>::iterator it = std::find(result.begin(), result.end(), main_chain[current]);
			size_t dist = std::distance(result.begin(), it);

			insert_vec(result, val, dist);

			if (current == 0)
				break; // sanity check
			current--;
		}
		inserted_count = limit + 1;
		jacob_idx++;
	}
	if (is_uneven)
		insert_vec(result, unpaired, result.size());
	arr = result;
}

// Deque
void PmergeMe::insert_deque(std::deque<int>& main_chain, int val, size_t limit)
{
	std::deque<int>::iterator end = main_chain.begin() + limit;
	std::deque<int>::iterator pos = std::lower_bound(main_chain.begin(), end, val);
	main_chain.insert(pos, val);
}

void PmergeMe::sort_deque(std::deque<int>& arr)
{
	size_t n = arr.size();
	if (n < 2) return;

	bool is_uneven = (n % 2 != 0);
	int unpaired = 0;
	if (is_uneven)
	{
		unpaired = arr.back();
		arr.pop_back();
	}

	std::deque<std::pair<int, int> > pairs;
	for (size_t i = 0; i < arr.size(); i += 2)
	{
		if (arr[i] > arr[i + 1])
			pairs.push_back(std::make_pair(arr[i], arr[i + 1]));
		else
			pairs.push_back(std::make_pair(arr[i + 1], arr[i]));
	}

	std::deque<int> main_chain;
	for (size_t i = 0; i < pairs.size(); ++i)
	{
		main_chain.push_back(pairs[i].first);
	}
	sort_deque(main_chain);

	std::deque<int> pend;
	std::deque<int> result = main_chain;

	for (size_t i = 0; i < main_chain.size(); ++i)
	{
		for (size_t j = 0; j < pairs.size(); ++j)
		{
			if (pairs[j].first == main_chain[i])
			{
				pend.push_back(pairs[j].second);
				pairs.erase(pairs.begin() + j);
				break;
			}
		}
	}

	result.insert(result.begin(), pend[0]);

	size_t jacob_idx = 3;
	size_t inserted_count = 1;

	while (inserted_count < pend.size())
	{
		size_t next_jacobsthal = get_jacob_num(jacob_idx);
		size_t limit = next_jacobsthal - 1;
		if (limit >= pend.size()) limit = pend.size() - 1;

		size_t current = limit;
		while (current >= inserted_count)
		{
			int val = pend[current];
			std::deque<int>::iterator it = std::find(result.begin(), result.end(), main_chain[current]);
			size_t dist = std::distance(result.begin(), it);
			insert_deque(result, val, dist);
			if (current == 0)
				break;
			current--;
		}
		inserted_count = limit + 1;
		jacob_idx++;
	}

	if (is_uneven)
		insert_deque(result, unpaired, result.size());
	arr = result;
}

void PmergeMe::execute()
{
	print_seq(_vec, "Before: ");

	// Vector version
	struct timeval start, end;
	gettimeofday(&start, NULL);
	sort_vec(_vec);
	gettimeofday(&end, NULL);
	long seconds = end.tv_sec - start.tv_sec;
	long micros = end.tv_usec - start.tv_usec;
	_vectime = seconds * 1000000 + micros;

	// Deque version
	gettimeofday(&start, NULL);
	sort_deque(_deq);
	gettimeofday(&end, NULL);
	seconds = end.tv_sec - start.tv_sec;
	micros = end.tv_usec - start.tv_usec;
	_deqtime = seconds * 1000000 + micros;

	print_seq(_vec, "After:  ");

	std::cout << "Time to process a range of " << _vec.size() 
		<< " elements with std::vector : " << std::fixed << std::setprecision(5) 
		<< _vectime << " us" << std::endl;

	std::cout << "Time to process a range of " << _deq.size() 
		<< " elements with std::deque  : " << std::fixed << std::setprecision(5) 
		<< _deqtime << " us" << std::endl;
}
