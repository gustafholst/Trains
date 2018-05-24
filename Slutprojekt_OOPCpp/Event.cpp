

#include <sstream>
#include "Event.h"
#include "Simulation.h"
#include "RailwayCompany.h"
#include "TrainStation.h"

void printTrain(std::ostream &os, std::shared_ptr<const Train> v);

Event::~Event()
{
}



void AssemblyEvent::processEvent()
{
	std::string stationName = m_train->getDepStation();
	TrainStation *station = m_railway->getStation(stationName);

	if (station->assembleTrain(m_train))
	{
		m_train->setState(TrainState::ASSEMBLED);
		Time newTime = m_time + Time(20);  // assembly takes 20 minutes
		std::shared_ptr<Event> newEvent = std::shared_ptr<Event>(new ReadyEvent(m_simulation, m_railway, newTime, m_train));
		m_simulation->scheduleEvent(newEvent);
		m_statusString = "now assembled, arriving at station at " + formatTime(newTime);
	}
	else
	{
		m_train->setState(TrainState::INCOMPLETE);
		m_train->increaseDelay(10);
		Time newTime = m_time + Time(10);  // next try in 10 minutes
		std::shared_ptr<Event> newEvent = std::shared_ptr<Event>(new AssemblyEvent(m_simulation, m_railway, newTime, m_train));
		m_simulation->scheduleEvent(newEvent);
		m_statusString = "now incomplete, next try at " + formatTime(newTime);
	}
}

std::string AssemblyEvent::toString() const
{
	std::ostringstream stream;
	printTrain(stream, m_train);
	stream << '\n' << m_statusString;
	return stream.str();
}

void ReadyEvent::processEvent()
{
	
}

std::string ReadyEvent::toString() const
{
	std::ostringstream stream;
	printTrain(stream, m_train);
	stream << '\n' << m_statusString;
	return stream.str();
}

std::ostream & operator<<(std::ostream & outstream, const Event & e)
{
	outstream << e.toString();
	return outstream;
}
