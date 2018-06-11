#include <string>
#include <algorithm>
#include <sstream>

#include "auxilliary.h"

std::string getStringInput(const std::string & message)
{
	std::string input = "";

	while (input.size() < 1 ) 
	{
		std::cout << message;
		getline(std::cin, input);
	}

	return trim(input);  //remove trailing whitespaces before returning
}

std::string trim(const std::string s)
{
	const std::string SPACE = " \t";  //remove both spaces and tabs
	int beg = s.find_first_not_of(SPACE);
	int end = s.find_last_not_of(SPACE);

	return s.substr(beg, (end - beg) + 1);
}

int getIntInput(const std::string &message, const int & min, const int & max)
{
	int input;
	while (true)
	{
		std::cout << message;
		std::cin >> input;
		std::cin.get();

		if (input >= min && input <= max)
			return input;
		else if (!std::cin.good()) {
			std::cin.clear();
			std::cin.ignore(std::cin.rdbuf()->in_avail());
		}

		std::cout << "Input value between " << min << " and " << max << std::endl;
	}
}

Time getTimeInput(const std::string & message)
{
	Time inputTime;

	while (true)
	{
		std::stringstream stream;
		std::string input = getStringInput(message);
		try
		{
			stream << input << ' ';
			stream >> inputTime;
			return inputTime;
		}
		catch (std::ios_base::failure &)
		{
			std::cout << "Not a valid time" << std::endl;
		}
	}
}

void clearScreen()
{
	clearScr();
}

void sepLine(std::ostream &os, const int length, const char c)
{
	std::string sepLine(length, c);
	os << sepLine << std::endl;
}

std::string lowercase(const std::string & string)
{
	std::string tmp = string;
	transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	return tmp;
}

void goOn(const std::string &message)
{
	std::cout << message << '\n' << std::endl;
	std::cin.get();
}