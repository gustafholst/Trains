

#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include "Time.h"

Time Time::operator+(const Time &time)
{
	Time sum = time;    //according to c++ primer, this is the preferred way to implement (using compound operator)
	sum += *this;
	return sum;
}

Time Time::operator+=(const Time & time)
{
	return this->m_minutes + time.m_minutes;
}

Time Time::operator-(const Time & time)
{
	Time difference = *this;
	difference -= time;
	return difference;
}

Time Time::operator-=(const Time & time)
{
	return this->m_minutes - time.m_minutes;
}

std::istream & operator>>(std::istream & instream, Time & time)
{
	int hours, mins;
	std::string strTime;
	std::getline(instream, strTime, ' ');
	std::replace(strTime.begin(), strTime.end(), ':', ' ');
	std::istringstream is(strTime);
	is >> hours >> mins;
	time.setMins(hours * 60 + mins);
	return instream;
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
