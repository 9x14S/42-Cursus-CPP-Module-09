#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <string>
# include <map>

class BitcoinExchange
{
public:
	// Orthodox Canonical Form
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& that);
	BitcoinExchange &operator=(const BitcoinExchange& that);
	~BitcoinExchange();

	// Main functionality
	void	loadDatabase(const std::string& filename);
	void	processInput(const std::string& filename);
private:
	std::map<std::string, float> _database;

	std::string trim(const std::string& str) const;
	bool		isValidDate(const std::string& date) const;
	bool		isValidValue(const float& value) const;
};

#endif // BITCOINEXCHANGE_HPP
