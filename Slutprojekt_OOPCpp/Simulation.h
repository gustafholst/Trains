

#ifndef SIMULATION_H
#define SIMULATION_H

#include <queue>
#include "Event.h"
#include "Time.h"


class Simulation
{
public:
	Simulation()
		:m_currentTime(0), m_interval(10), m_logLevel(LogLevel::NORMAL) {}
	~Simulation();

	Time getCurrentTime() const { return m_currentTime; }
	Time getCurrentInterval() const { return m_interval; }
	void changeInterval(const Time &p_newInterval) { m_interval = p_newInterval; }
	void scheduleEvent(std::shared_ptr<Event> p_event) { m_eventQueue.push(p_event); }

	LogLevel getLogLevel() const { return m_logLevel; }
	void setLogLevel(LogLevel p_logLevel) { m_logLevel = p_logLevel; }
	std::shared_ptr<Event> getNextEvent();
	std::vector<std::shared_ptr<Event>> getNextInterval();

private:
	Time m_currentTime;
	Time m_interval;
	LogLevel m_logLevel;

	std::priority_queue<std::shared_ptr<Event>, std::vector< std::shared_ptr<Event>>, EventComparison> m_eventQueue;
};

#endif //!SIMULATION_H