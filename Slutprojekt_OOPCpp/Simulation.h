/*
* Simulation.h
* Gustaf Holst, guho1700
* 2018-05-26
* v1.0
*
* Declares the Simulation class.
*
*/

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

	// ------ GETTERS ------
	Time getCurrentTime() const { return m_currentTime; }
	Time getCurrentInterval() const { return m_interval; }
	Time getStartTime() const { return m_startTime; }
	Time getEndTime() const { return m_endTime; }
	LogLevel getLogLevel() const { return m_logLevel; }
	std::shared_ptr<Event> getNextEvent();
	std::vector<std::shared_ptr<Event>> getNextInterval();
	const std::vector<std::shared_ptr<Event>> getAllEvents() const { return m_eventsHistory; }
	const std::vector<std::shared_ptr<Event>> getTrainEvents(const int trainId) const;
	const std::vector<std::shared_ptr<Event>> getVehicleEvents(const int vehicleId) const;

	// ------ SETTERS ------
	void setInterval(const Time &p_newInterval) { m_interval = p_newInterval; }
	void setLogLevel(LogLevel p_logLevel) { m_logLevel = p_logLevel; }
	// returns false if time is after end time, true otherwise
	bool setStartTime(const Time newTime);
	// returns false if time is before start time, true otherwise
	bool setEndTime(const Time newTime);

	// ------ LOGIC ------

	/*
	Places assembly events 30 min before departure for all trains departing before simulation end time.

	@param p_railway the RailwayCompany object controlling all stations
	*/
	void setupSimulation(RailwayCompany *p_railway);

	/*
	Processes all events up until simulation start time. All processed events are stored in a event history 
	data structure for access afterwards.
	*/
	void startSimulation();

	/*
	Adds an event to the event queue.

	@param p_event the event to be added
	*/
	void scheduleEvent(std::shared_ptr<Event> p_event) { m_eventQueue.push(p_event); }

	/*
	Processes all remaining events and stores them in event history.
	*/
	void finishSimulation();

	/*
	Returns true if no more events in events queue.
	*/
	bool isFinished() { return m_finished; }

	/*
	Writes all events in the events history to file.
	*/
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