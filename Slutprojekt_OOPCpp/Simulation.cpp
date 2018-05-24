

#include "Simulation.h"

Simulation::~Simulation()
{
}

std::shared_ptr<Event> Simulation::getNextEvent()
{
	std::shared_ptr<Event> next;
	if (next = m_eventQueue.top())
	{
		m_eventQueue.pop();   //remove event from queue
		next->processEvent();
		m_currentTime = next->getTime();   //update ckock
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
