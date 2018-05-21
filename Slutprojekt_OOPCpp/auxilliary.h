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

///*
//Extracts an integer from the specified input stream. If a value is found that is in the specified range it will be
//stored in the output reference variable 'output' and true will be returned. If the value is out of range the value
//-1 will be stored in 'output' and false will be returned. If no integer value is found false is returned (output is not set).
//
//@param is the stream to extract from
//@param output the variable to store the output
//@param min the minimum value to accept
//@param max the maximum value to accept
//@return true if valid integer is extracted, false otherwise
//*/
//bool getInt(std::istream &is, int &output, const int &min, const int &max);

/*
Delays execution of the program for the specified amount of milliseconds.

@param millis the amount of milliseconds to pause
*/
void pause(const int millis);

/*
Clears the console.
*/
void clearScreen();

/*
Prints a 'line' of specified length useing the specified character to the console.

@param length the number a characters to print
@param c the character to print
*/
void sepLine(const int length, const char c);

/*
Returns a string with all lowercase letters. (Original string is left intact)

@param string the string to transform
*/
std::string lowercase(const std::string &string);

/*
Prints a message to the user and waits for confirmation. Accepted positive confirmations are "y" or "yes", case insensitive.
All other replies are considered negative replies.

@param message the message to display
@return true if positive reply has been given, false otherwise
*/
bool confirm(const std::string &message);

/*
'Animates' the printing of the word "PLAYING" to the screen, repeated four times.
*/
void simulatePlaying();

/*
Prints a message to the screen, waits for the user to press any key and then clears the screen.

@param message the message to be printed to the screen
*/
void goOn(const std::string &message);

/*
Prints the provided head sting decorated with some ASCII characters.

@param head the head to print
*/
void printHead(const std::string &head);




#endif //!AUXILLIARY_H