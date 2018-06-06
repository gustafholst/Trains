/*
* Time.h
* Gustaf Holst, guho1700
* 2018-05-25
* v1.0
*
* Declares the Time class.
*
*/

#ifndef TIME_H
#define TIME_H

#include <iostream>
#include <exception>

class Time
{
public:
	Time() :m_minutes(0) {}
	Time(const int p_minutes) : m_minutes(p_minutes) {}
	~Time() = default;

	//overloaded operators
	Time operator+ (const Time &time) const;
	Time& operator+= (const Time &time);
	Time operator- (const Time &time) const ;
	Time& operator-= (const Time &time);
	bool operator> (const Time &time) const;
	bool operator< (const Time &time) const;
	bool operator<= (const Time &time) const;

	// get/set
	int getMins() const { return m_minutes; }
	void setMins(const int p_minutes) { m_minutes = p_minutes; }

private:
	int m_minutes;
};


std::istream &operator >> (std::istream &instream, Time &time);   // throws std::ios_base::failure
std::ostream &operator << (std::ostream &outstream, const Time &time);

/*
Returns a string representing the specified Time object. Format is [hh:mm] or [d:hh:mm] if 24 hours has passed.

@param time the time object to be formatted
@return a formatted string
*/
std::string formatTime(const Time &time);


#endif // TIME_H
