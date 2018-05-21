#include <string>
#include <algorithm>

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

//int getIntInput(const std::string & message, const int &min, const int &max)
//{
//	int input;
//	while (true)
//	{
//		std::cout << message;
//	
//		if (getInt(std::cin, input, min, max))
//			return input;
//
//		std::cout << "Choose an option between " << min << " and " << max << std::endl;
//	}
//
//	return 0;    //unreachable code
//}
//
//bool getInt(std::istream & is, int & output, const int &p_min, const int &p_max)
//{
//	int tmpInt;
//	is >> tmpInt;
//	is.get();
//
//	if (!is.good() && !is.eof())   //if not
//	{
//		is.clear();
//		is.ignore(is.rdbuf()->in_avail(), '\n'); //ignore any input that cannot be converted to int	  
//		return false;
//	}
//	else if (tmpInt >= p_min && tmpInt <= p_max)
//	{
//		output = tmpInt;
//		return true;
//	}
//	
//	output = -1;  //if integer is out of range
//	return false;
//}

void pause(const int millis)
{
	Sleep(millis);
}

void clearScreen()
{
	clearScr();
}

void sepLine(const int length, const char c)
{
	std::string sepLine(length, c);
	std::cout << sepLine << std::endl;
}

std::string lowercase(const std::string & string)
{
	std::string tmp = string;
	transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
	return tmp;
}

bool confirm(const std::string & message)
{
	std::string confirmation = lowercase(getStringInput(message + " (type y for yes)"));
	if (confirmation == "y" || confirmation == "yes")
		return true;

	return false;
}

void simulatePlaying()
{
	char chars[] = { 'P','L','A','Y','I','N','G' };
	int index = 0;
	for (int i = 0; i < 7; ++i)
	{
		std::cout << chars[index++] << " ";
		pause(300);
	}
	for (int i = 0; i < 14; ++i)
		std::cout << '\b' << '\b' << ' ';  //"delete" previous (overwrite with whitespace)
}

void goOn(const std::string &message)
{
	std::cout << message << std::endl;
	std::cin.get();
}

void printHead(const std::string & head)
{
	sepLine(14 + 14 + head.size(), '#');
	std::cout << "############# " << head << " #############" << std::endl;
	sepLine(14 + 14 + head.size(), '#');
	std::cout << std::endl;
}





