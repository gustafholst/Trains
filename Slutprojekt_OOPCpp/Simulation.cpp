

#include "Simulation.h"
#include "TrainStation.h"
#include "RailwayCompany.h"

Simulation::~Simulation()
{
}

bool Simulation::changeStartTime(const Time newTime)
{
	if (newTime > m_endTime)
		return false;

	m_startTime = newTime;
	return true;
}

bool Simulation::changeEndTime(const Time newTime)
{
	if (newTime < m_startTime)
		return false;

	m_endTime = newTime;
	return true;
}

void Simulation::setupSimulation(RailwayCompany * p_railway)
{
	std::vector<const TrainStation*> stations = p_railway->getAllStations();

	for (const TrainStation *station : stations)
	{
		std::vector<std::shared_ptr<Train>> trains = station->getTrains();
		for (auto train : trains)
		{
			if (train->getDepTime() < m_endTime)  //only seed trains departing before simulation end time
			{
				Time assembly = train->getDepTime() - 30;
				std::shared_ptr<Event> newEvent = std::shared_ptr<Event>(new AssemblyEvent(this, p_railway, assembly, train));
				scheduleEvent(newEvent);
			}
		}
	}
}

void Simulation::startSimulation()
{
	//process all events up until start time
	while (m_eventQueue.top()->getTime() <= m_startTime)
	{
		std::shared_ptr<Event> next = m_eventQueue.top();
		m_eventQueue.pop();   //remove event from queue
		next->processEvent();
		//m_currentTime = next->getTime();   //update clock
	}
	m_currentTime = m_startTime;
}

std::shared_ptr<Event> Simulation::getNextEvent()
{
	if (!m_eventQueue.empty())
	{
		std::shared_ptr<Event> next = m_eventQueue.top();
		m_eventQueue.pop();   //remove event from queue
		next->processEvent();
		m_currentTime = next->getTime();   //update clock
		return next;
	}

	return nullptr;
}

std::vector<std::shared_ptr<Event>> Simulation::getNextInterval()
{
	std::vector<std::shared_ptr<Event>> latestEvents;
	m_currentTime += m_interval;  //update clock
	while (!m_eventQueue.empty())
	{
		std::shared_ptr<Event> next = m_eventQueue.top();
		if (next->getTime() > m_currentTime)
			break;

		m_eventQueue.pop();   //remove event from queue
		next->processEvent();
		latestEvents.push_back(next);
	}

	return latestEvents;
}
