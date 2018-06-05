/*
* helpfunctions.h
* Gustaf Holst, guho1700
* 2018-03-01
* v1.0
*
* Declares a number of functions used throughout the Jukebox application.
*
*/

#ifndef AUXILLIARY_H
#define AUXILLIARY_H

// include the appropriate header and define the clearScr and Sleep functions depending on platform used
#if defined __WIN32__ || defined _WIN32
#include <windows.h>
#define clearScr() system("cls")
#else 
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#define clearScr() printf("\033[H\033[J")
#endif



#include <iostream>
#include "Time.h"

/*
Prints a message to the user then waits for a string of size larger than 0 to be input.
The input string is then trimmed of leading and trailing whitespaces.

@param message the message to prompt the user for input
@return the retrived string
*/
std::string getStringInput(const std::string &message);

/*
Removes leading and trailing whitespaces of a string.

@param s the string
@return a new string with removed whitespaces
*/
std::string trim(const std::string s);

/*
Prints a message to the user then waits for an integer value between the specified min and max value to
be provided by the user.

@param message the message to prompt the user for input
@param min the minimum value to be accepted
@param max the maximum value to be accepted
@return the retrived integer value
*/
int getIntInput(const std::string &message, const int &min = (std::numeric_limits<int>::min)(), const int &max = (std::numeric_limits<int>::max)());

Time getTimeInput(const std::string &message);


/*
Clears the console.
*/
void clearScreen();

/*
Prints a 'line' of specified length useing the specified character to the console.

@param length the number a characters to print
@param c the character to print
*/
void sepLine(std::ostream &os, const int length, const char c);

/*
Returns a string with all lowercase letters. (Original string is left intact)

@param string the string to transform
*/
std::string lowercase(const std::string &string);

/*
Prints a message to the screen, waits for the user to press any key and then clears the screen.

@param message the message to be printed to the screen
*/
void goOn(const std::string &message);


#endif //!AUXILLIARY_H