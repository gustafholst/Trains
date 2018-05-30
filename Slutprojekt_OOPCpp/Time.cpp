

#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Time.h"

Time Time::operator+(const Time &time) const
{
	Time sum = time;    //according to c++ primer, this is the preferred way to implement (using compound operator)
	sum += *this;
	return sum;
}

Time& Time::operator+=(const Time & time)
{
	this->m_minutes = this->m_minutes + time.m_minutes;
	return *this;
}

Time Time::operator-(const Time & time) const
{
	Time difference = *this;
	difference -= time;
	return difference;
}

Time& Time::operator-=(const Time & time)
{
	this->m_minutes = this->m_minutes - time.m_minutes;
	return *this;
}

bool Time::operator<(const Time & time) const
{
	return this->m_minutes < time.m_minutes;
}

bool Time::operator>(const Time & time) const
{
	return this->m_minutes > time.m_minutes;
}

bool Time::operator<=(const Time & time) const
{
	return !(*this > time);
}

std::istream & operator>>(std::istream & instream, Time & time)
{
	int hours, mins;
	std::string strTime;
	std::getline(instream, strTime, ' ');
	std::replace(strTime.begin(), strTime.end(), ':', ' ');
	std::istringstream is(strTime);
	is.exceptions(std::ios::failbit);
	try {
		is >> hours >> mins;       //might throw failure
		time.setMins(hours * 60 + mins);
		if (hours < 0 || hours > 23 || mins < 0 || mins > 59)  
			throw std::ios_base::failure("not valid time");
	}
	catch (std::ios_base::failure e)
	{
		throw;
	}
	
	return instream;
}

std::ostream & operator<<(std::ostream & outstream, const Time & time)
{
	outstream << formatTime(time);
	return outstream;
}

std::string formatTime(const Time & time)
{
	using namespace std;
	int mins = time.getMins();
	int hours = mins / 60;
	mins = mins % 60;
	std::ostringstream timeStream;
	timeStream << setw(2) << setfill('0') << hours << setw(1) << ':' << setw(2) << mins;
	return timeStream.str();
}
