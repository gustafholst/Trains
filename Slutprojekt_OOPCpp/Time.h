

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

	Time operator+ (const Time &time) const;
	Time& operator+= (const Time &time);
	Time operator- (const Time &time) const ;
	Time& operator-= (const Time &time);
	bool operator> (const Time &time);
	bool operator<= (const Time &time);

	int getMins() const { return m_minutes; }
	void setMins(const int p_minutes) { m_minutes = p_minutes; }

private:
	int m_minutes;
};

std::istream &operator >> (std::istream &instream, Time &time);
std::ostream &operator << (std::ostream &outstream, const Time &time);

std::string formatTime(const Time &time);

#endif // TIME_H
