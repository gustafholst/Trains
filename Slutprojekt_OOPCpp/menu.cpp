/*
* Menu.cpp
* Gustaf Holst, guho1700
* 2018-03-02
* v1.0
*
* Defines members and functions related to the Menu class.
*
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "menu.h"
#include "auxilliary.h"

Menu::Menu(std::string h)
	:head(h)
{
}

void Menu::addItem(const std::string & text, std::function<void()> p_function)
{
	menuItems.emplace_back(text, p_function);   //construct item at the back of vector 
}

void Menu::printHead() const
{
	std::cout << head << std::endl;
	sepLine(head.size(), '=');
}

void Menu::printMenuItems() const
{
	int number = 1;
	for (const MenuItem &item : menuItems)
	{
		if (item.isEnabled())
			std::cout << std::left << std::setw(6) << number++ <<  item.getText() << std::endl;
	}
	std::cout << std::left << std::setw(6) << 0 << "Return" << std::endl;
}

unsigned Menu::getMenuChoice() const
{
	return getIntInput("Your choice: ", 0, menuItems.size());
}

bool Menu::display(Simulation * sim)
{
	clearScreen();
	printHead();
	if (sim != nullptr)
	{
		sepLine(28, '-');
		std::cout << std::left << std::setw(22) << "Current time: " << std::right << std::setw(6) << (sim->getCurrentTime()) << std::endl;
		std::cout << std::left << std::setw(22) << "Current interval: " << std::right << std::setw(6) << formatTime(sim->getCurrentInterval()) << std::endl;
		std::cout << std::left << std::setw(22) << "Start time: " << std::right << std::setw(6) << formatTime(sim->getStartTime()) << std::endl;
		std::cout << std::left << std::setw(22) << "End time: " << std::right << std::setw(6) << formatTime(sim->getEndTime()) << std::endl;
		std::cout << std::left << std::setw(22) << "Current log level: " << std::right << std::setw(6) << logLevelStrings[static_cast<size_t>(sim->getLogLevel())] << std::endl;
		sepLine(28, '-');
	}
	printMenuItems();
	unsigned choice = getMenuChoice();
	if (choice == 0)
		return false;

	menuItems[choice - 1].doOption();
	return true;
}



