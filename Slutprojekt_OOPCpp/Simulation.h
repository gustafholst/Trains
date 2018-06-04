

#ifndef SIMULATION_H
#define SIMULATION_H

#include <queue>
#include "Event.h"
#include "Time.h"
#include "constants.h"


class Simulation
{
public:
	Simulation()
		:m_currentTime(0), m_interval(10), m_startTime(0), m_endTime(1439), m_logLevel(LogLevel::NORMAL) {}   //1439 -> 23:59
	~Simulation();

	Time getCurrentTime() const { return m_currentTime; }
	Time getCurrentInterval() const { return m_interval; }
	Time getStartTime() const { return m_startTime; }
	Time getEndTime() const { return m_endTime; }
	void changeInterval(const Time &p_newInterval) { m_interval = p_newInterval; }
	bool changeStartTime(const Time newTime);
	bool changeEndTime(const Time newTime);

	void setupSimulation(RailwayCompany *p_railway);
	void startSimulation();
	void scheduleEvent(std::shared_ptr<Event> p_event) { m_eventQueue.push(p_event); }

	LogLevel getLogLevel() const { return m_logLevel; }
	void setLogLevel(LogLevel p_logLevel) { m_logLevel = p_logLevel; }
	std::shared_ptr<Event> getNextEvent();
	std::vector<std::shared_ptr<Event>> getNextInterval();   
	void finishSimulation();
	const std::vector<std::shared_ptr<Event>> getAllEvents() const { return m_eventsHistory; }
	const std::vector<std::shared_ptr<Event>> getTrainEvents(const int trainId) const;
	const std::vector<std::shared_ptr<Event>> getVehicleEvents(const int vehicleId) const;

	bool isFinished() { return m_finished; }

	void writeToFile();

private:
	Time m_currentTime;
	Time m_interval;
	Time m_startTime;
	Time m_endTime;
	LogLevel m_logLevel;
	bool m_finished = false;  //use a boolean to separate the state when queue is empty at the start from when it has been emptied during simulation

	std::priority_queue<std::shared_ptr<Event>, std::vector< std::shared_ptr<Event>>, EventComparison> m_eventQueue;
	std::vector<std::shared_ptr<Event>> m_eventsHistory;
};

#endif //!SIMULATION_H