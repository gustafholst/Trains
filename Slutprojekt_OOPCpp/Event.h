

#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include "Time.h"
#include "Train.h"

class Simulation;
class RailwayCompany;

class Event
{
public:
	Event(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time)
		:m_simulation(p_simulation), m_railway(p_railway), m_time(p_time) {};
	virtual ~Event();

	virtual void processEvent() = 0;

	Time getTime() const { return m_time; }

protected:
	Simulation *m_simulation;  
	RailwayCompany *m_railway;
	Time m_time;
};

class EventComparison 
{
public:
	bool operator() (std::shared_ptr<Event> left, std::shared_ptr<Event> right) {
		return left->getTime() > right->getTime();
	}
};


class AssemblyEvent : public Event
{
public:
	AssemblyEvent(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:Event(p_simulation, p_railway, p_time), m_train(p_train) {}

	void processEvent() override;

private:
	std::shared_ptr<Train> m_train;
};


class ReadyEvent : public Event
{
public:
	ReadyEvent(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:Event(p_simulation, p_railway, p_time), m_train(p_train) {}
		
	void processEvent() override;

private:
	std::shared_ptr<Train> m_train;
};




#endif //!EVENT_H
