/*
* Menu.h
* Gustaf Holst, guho1700
* 2018-05-25
* v1.0
*
* Declares the Menu and MenuItem classes.
*
*/

#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <vector>
#include <functional>
#include "auxilliary.h"
#include "Simulation.h"

class MenuItem
{
private:
	std::string m_text;
	std::function<void()> m_function;
	bool m_enabled;

public:
	MenuItem(const std::string &p_text, const bool p_enabled, std::function<void()> p_function)
		:m_text(p_text), m_function(p_function), m_enabled(p_enabled) {}

	std::string getText() const { return m_text; }
	bool isEnabled() const { return m_enabled; }
	void disable() { m_enabled = false; }
	void enable() { m_enabled = true; }

	/*
	Call the function associated with this item.
	*/
	void doOption() { m_function(); }
};

class Menu
{
private:
	std::string m_head;
	std::vector<MenuItem> m_menuItems;
	std::vector<MenuItem*> m_enabledItems;
	
	void printHead() const;

	/*
	Prints the name of the menu followed by a numbered list of all menu items.
	*/
	void printMenuItems();

	/*
	Returns the chosen menu option. Will keep prompting the user for input until a 
	value between 1 and the amount of list items in the menu has been provided.

	return the chosen option
	*/
	unsigned getMenuChoice() const;

public:
	Menu() = default;
	Menu(std::string h);

	void setHead(const std::string &p_head) { m_head = p_head; }

	/*
	Adds a menu item to this menu.

	@param text the text of the menu item
	@param p_function pointer to the function to be associated with the item
	*/
	void addItem(const std::string &text, const bool p_enabled, std::function<void()> p_function);

	/*
	Displays the menu, collects user input and calls the appropriate function.

	@return false if the exit program option has been chosen, true otherwise
	*/
	bool display(Simulation * sim = nullptr);

	void enableItem(const size_t item);
	void disableItem(const size_t item);
};


#endif MENU_H//!MENU_H