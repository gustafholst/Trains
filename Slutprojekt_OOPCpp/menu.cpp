/*
* Menu.cpp
* Gustaf Holst, guho1700
* 2018-05-25
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

Menu::Menu(std::string p_head)
	:m_head(p_head)
{
}

void Menu::addItem(const std::string & text, const bool p_enabled, std::function<void()> p_function)
{
	m_menuItems.emplace_back(text, p_enabled, p_function);
}

void Menu::printHead() const
{
	std::cout << m_head << std::endl;
	sepLine(std::cout, m_head.size(), '=');
}

void Menu::printMenuItems()
{
	int number = 1;
	for (MenuItem &item : m_menuItems)
	{
		if (item.isEnabled())
		{
			std::cout << std::left << std::setw(6) << number++ << item.getText() << std::endl;
			m_enabledItems.push_back(&item);  //store pointers to all enabled items
		}	
	}

	if (m_head == "Start menu")
		std::cout << std::left << std::setw(6) << 0 << "Exit" << std::endl;
	else
		std::cout << std::left << std::setw(6) << 0 << "Return" << std::endl;
}

unsigned Menu::getMenuChoice() const
{
	return getIntInput("Your choice: ", 0, m_menuItems.size());
}

bool Menu::display(Simulation * sim)
{
	clearScreen();
	printHead();
	if (sim != nullptr)
	{
		sepLine(std::cout, 30, '-');
		if (sim->isFinished())
			std::cout << "||| SIMULATION FINISHED |||" << std::endl;
		std::cout << std::left << std::setw(22) << "Current time: " << std::right << std::setw(8) << (sim->getCurrentTime()) << std::endl;
		std::cout << std::left << std::setw(22) << "Current interval: " << std::right << std::setw(8) << formatTime(sim->getCurrentInterval()) << std::endl;
		std::cout << std::left << std::setw(22) << "Start time: " << std::right << std::setw(8) << formatTime(sim->getStartTime()) << std::endl;
		std::cout << std::left << std::setw(22) << "End time: " << std::right << std::setw(8) << formatTime(sim->getEndTime()) << std::endl;
		std::cout << std::left << std::setw(22) << "Current log level: " << std::right << std::setw(8) << logLevelStrings[static_cast<size_t>(sim->getLogLevel())] << std::endl;
		sepLine(std::cout, 30, '-');
	}
	printMenuItems();
	unsigned choice = getMenuChoice();
	if (choice == 0)
		return false;

	m_enabledItems[choice - 1]->doOption();   //chosen number will correspond to index in vector with pointers to enabled items 
	m_enabledItems.clear();    //clear list , a new list will be created every time
	return true;
}

void Menu::enableItem(const size_t item)
{
	m_menuItems[item].enable();
}

void Menu::disableItem(const size_t item)
{
	m_menuItems[item].disable();
}



