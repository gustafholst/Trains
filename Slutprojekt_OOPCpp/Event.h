

#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include "Time.h"
#include "Route.h"
#include "Simulation.h"
#include "RailwayCompany.h"

class Event
{
public:
	Event(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time) 
		:m_simulation(p_simulation), m_railway(p_railway), m_time(p_time) {};
	virtual ~Event();

	virtual void processevent() = 0;

	Time getTime() const { return m_time; }

private:
	Simulation *m_simulation;  //event can not change simulation
	RailwayCompany *m_railway;
	Time m_time;
};

class EventComparison {
public:
	bool operator() (std::shared_ptr<Event> left, std::shared_ptr<Event> right) {
		return left->getTime() > right->getTime();
	}
};


class AssembleEvent : public Event
{
public:
	AssembleEvent(const Route &p_route);

	virtual void processevent() override;

private:
	Route * m_route;
};

#endif //!EVENT_H
