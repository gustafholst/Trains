

#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include <sstream>
#include "Time.h"
//#include "Train.h"

class Simulation;
class RailwayCompany;
class Train;

class Event
{
public:
	Event(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:m_simulation(p_simulation), m_railway(p_railway), m_time(p_time), m_train(p_train) 
	{
		m_statusStream << formatTime(m_time) << ' ';   //put time of the event in the status stream (which is the only info known at this point)
	};
	virtual ~Event();

	virtual void processEvent() = 0;

	Time getTime() const { return m_time; }
	const std::shared_ptr<Train> getTrain() const { return m_train; }  //which train does this event handle?

	virtual std::string toString() const;

protected:
	Simulation *m_simulation;  
	RailwayCompany *m_railway;
	Time m_time;
	std::shared_ptr<Train> m_train;
	std::stringstream m_statusStream;
};

std::ostream &operator << (std::ostream &outstream, const Event &e);

class EventComparison 
{
public:
	bool operator() (std::shared_ptr<Event> left, std::shared_ptr<Event> right) {
		return left->getTime() > right->getTime();
	}
};

// --------- Derived classes -----------

class AssemblyEvent : public Event
{
public:
	AssemblyEvent(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:Event(p_simulation, p_railway, p_time, p_train) {}

	void processEvent() override;
};


class ReadyEvent : public Event
{
public:
	ReadyEvent(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:Event(p_simulation, p_railway, p_time, p_train) {}
		
	void processEvent() override;
};


class DepartureEvent : public Event
{
public:
	DepartureEvent(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:Event(p_simulation, p_railway, p_time, p_train) {}

	void processEvent() override;
};


class ArriveEvent : public Event
{
public:
	ArriveEvent(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:Event(p_simulation, p_railway, p_time, p_train) {}

	void processEvent() override;
};

class FinishEvent : public Event
{
public:
	FinishEvent(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:Event(p_simulation, p_railway, p_time, p_train) {}

	void processEvent() override;
};


#endif //!EVENT_H
