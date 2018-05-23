/*
* Menu.h
* Gustaf Holst, guho1700
* 2018-05-09
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

class MenuItem
{
private:
	std::string m_text;
	std::function<void()> m_function;
	bool enabled;

public:
	MenuItem(const std::string &p_text, std::function<void()> p_function)
		:m_text(p_text), m_function(p_function), enabled(true) {}

	std::string getText() const { return m_text; }
	bool isEnabled() const { return enabled; }
	void disable() { enabled = false; }

	/*
	Call the function associated with this item.
	*/
	void doOption() 
	{ 
		m_function(); 
	}
};

class Menu
{
private:
	std::string head;
	std::vector<MenuItem> menuItems;
	
	/*
	Prints the name of the menu followed by a numbered list of all menu items.
	*/
	void printMenuItems() const;

	/*
	Returns the chosen menu option. Will keep prompting the user for input until a 
	value between 1 and the amount of list items in the menu has been provided.

	return the chosen option
	*/
	unsigned getMenuChoice() const;

public:
	Menu() = default;
	Menu(std::string h);

	void setHead(const std::string &p_head) { head = p_head; }

	/*
	Adds a menu item to this menu.

	@param text the text of the menu item
	@param p_function pointer to the function to be associated with the item
	*/
	void addItem(const std::string &text, std::function<void()> p_function);

	/*
	Displays the menu, collects user input and calls the appropriate function.

	@return false if the exit program option has been chosen, true otherwise
	*/
	bool display();
};


#endif MENU_H//!MENU_H