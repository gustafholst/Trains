


#include "Event.h"
#include "Simulation.h"
#include "RailwayCompany.h"
#include "TrainStation.h"

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
	}
	else
	{
		m_train->setState(TrainState::INCOMPLETE);
		m_train->increaseDelay(10);
		Time newTime = m_time + Time(10);  // next try in 10 minutes
		std::shared_ptr<Event> newEvent = std::shared_ptr<Event>(new AssemblyEvent(m_simulation, m_railway, newTime, m_train));
		m_simulation->scheduleEvent(newEvent);
	}
}

void ReadyEvent::processEvent()
{
}
