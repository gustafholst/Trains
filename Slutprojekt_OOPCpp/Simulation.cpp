
#include <fstream>
#include "Simulation.h"
#include "TrainStation.h"
#include "RailwayCompany.h"

std::string LOG_FILE = "Trainsim.log";
void printEvent(std::ostream & os, std::shared_ptr<const Event> e);  //forward declaration (function def in UserInterface.cpp)

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
	while (!m_eventQueue.empty() && m_eventQueue.top()->getTime() <= m_startTime)
	{
		std::shared_ptr<Event> next = m_eventQueue.top();
		m_eventQueue.pop();   //remove event from queue
		next->processEvent();
		m_eventsHistory.push_back(next); //store a pointer to the event in history (for writing to file/presenting stats/displaying info about a specific vehicle or train)
	}
	m_currentTime = m_startTime;

	if (m_eventQueue.size() == 0)
		m_finished = true;
}

std::shared_ptr<Event> Simulation::getNextEvent()
{
	if (!m_eventQueue.empty())
	{
		std::shared_ptr<Event> next = m_eventQueue.top();
		m_eventQueue.pop();   //remove event from queue
		next->processEvent();
		m_eventsHistory.push_back(next); //store a pointer to the event in history (for writing to file/presenting stats/displaying info about a specific vehicle or train)
		m_currentTime = next->getTime();   //update clock
		return next;
	}

	m_finished = true;

	return nullptr;
}

std::vector<std::shared_ptr<Event>> Simulation::getNextInterval()
{
	std::vector<std::shared_ptr<Event>> latestEvents;
	m_currentTime += m_interval;  //update clock, run next interval

	while (!m_eventQueue.empty())
	{
		std::shared_ptr<Event> next = m_eventQueue.top();
		if (next->getTime() > m_currentTime)
			break;

		m_eventQueue.pop();   //remove event from queue
		next->processEvent();
		m_eventsHistory.push_back(next); //store a pointer to the event in history (for writing to file/presenting stats/displaying info about a specific vehicle or train)
		latestEvents.push_back(next);  //pointers for displaying to the user
	}

	if (m_eventQueue.size() == 0)
		m_finished = true;

	return latestEvents;   
}

void Simulation::finishSimulation()
{
	while (!isFinished())
	{
		std::shared_ptr<Event> next = m_eventQueue.top();
		m_eventQueue.pop();   //remove event from queue
		next->processEvent();
		m_currentTime = next->getTime(); //update clock  (so that current time displays as the time of the last event processed)
		m_eventsHistory.push_back(next); //store a pointer to the event in history (for writing to file/presenting stats/displaying info about a specific vehicle or train)
		if (m_eventQueue.empty())
			m_finished = true;
	}
}

const std::vector<std::shared_ptr<Event>> Simulation::getTrainEvents(const int trainId) const
{
	std::vector<std::shared_ptr<Event>> events;

	// find all events concerning the searched train
	for (auto e : m_eventsHistory)
	{
		auto train = e->getTrain();
		if (train->getId() == trainId)
			events.push_back(e);
	}

	return events;
}

void Simulation::writeToFile()
{
	std::ofstream outFile(LOG_FILE);

	outFile << "#############################" << std::endl;
	outFile << "Simulation log"<< std::endl;
	outFile << "start time: " + formatTime(m_startTime) << std::endl;
	outFile << "end time: " + formatTime(m_endTime) << std::endl;
	outFile << "#############################" << std::endl << std::endl;

	if (outFile)
	{
		for (auto event : m_eventsHistory)
		{
			printEvent(outFile, event);
			outFile << std::endl;
		}
	}

	outFile.close();
}
