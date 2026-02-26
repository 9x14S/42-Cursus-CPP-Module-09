#include <iostream>
#include <fstream>
#include <cstdlib>

#include "BitcoinExchange.hpp"

// Orthodox Canonical Form
BitcoinExchange::BitcoinExchange()
{}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{
	*this = other;
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		this->_database = other._database;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::trim(const std::string& str) const
{
	size_t first = str.find_first_not_of(" \t");
	if (std::string::npos == first)
		return str;
	size_t last = str.find_last_not_of(" \t");
	return str.substr(first, (last - first + 1));
}

bool BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.length() != 10)
		return false;
	// Assuming 1 digit days or months are formatted padded with 0
	if (date[4] != '-' || date[7] != '-')
		return false;

	int year  = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day   = std::atoi(date.substr(8, 2).c_str());

	if (year < 2009 || year > 2026)
		return false;
	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;

	if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
		return false;
	if (month == 2)
	{
		bool leap = (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
		if (day > (leap ? 29 : 28))
			return false;
	}
	return true;
}

void BitcoinExchange::loadDatabase(const std::string& filename)
{
	std::ifstream file(filename.c_str());
	if (!file.is_open())
	{
		std::cerr << "Error: could not open database file." << std::endl;
		exit(1);
	}

	std::string line;
	std::getline(file, line);

	while (std::getline(file, line))
	{
		size_t delim = line.find(',');
		if (delim == std::string::npos)
			continue;

		std::string date = trim(line.substr(0, delim));
		std::string rateStr = trim(line.substr(delim + 1));

		float rate = static_cast<float>(std::atof(rateStr.c_str()));
		_database[date] = rate;
	}
	file.close();
}

void BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream	file(filename.c_str());
	std::string		line;

	if (!file.is_open())
	{
		std::cerr << "Error: could not open file." << std::endl;
		exit(1);
	}

	std::getline(file, line);
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;

		size_t delim = line.find('|');
		if (delim == std::string::npos)
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		std::string date = trim(line.substr(0, delim));
		std::string valueStr = trim(line.substr(delim + 1));

		if (!isValidDate(date))
		{
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}

		char* end;
		double value = std::strtod(valueStr.c_str(), &end);
		if (valueStr.empty() || (*end != '\0' && *end != 'f'))
		{
			 std::cout << "Error: bad input => " << valueStr << std::endl;
			 continue;
		}

		if (value < 0)
		{
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}

		if (value > 1000)
		{
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		std::map<std::string, float>::iterator it = _database.upper_bound(date);

		if (it == _database.begin())
			std::cout << "Error: date not in database." << std::endl;
		else
		{
			it--;
			float result = static_cast<float>(value) * it->second;
			std::cout << date << " => " << value << " = " << result << std::endl;
		}
	}
	file.close();
}
