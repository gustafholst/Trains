/*
* Event.h
* Gustaf Holst, guho1700
* 2018-05-25
* v1.0
*
* Declares the Event class and all its subclasses.
*
*/

#ifndef EVENT_H
#define EVENT_H

#include <memory>
#include <sstream>
#include "Time.h"

// forward declarations (avoiding circular dependenices)
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
	virtual ~Event() {}   //virtual destructor

	/*
	Pure virtual member function that processes this event appropriately.
	*/
	virtual void processEvent() = 0;

	// ------ GETTERS ------
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

// overloaded output operator
std::ostream &operator << (std::ostream &outstream, const Event &e);

/*
Functor for comparing two instances of the Event classes by time.
*/
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

	/*
	Places train i assembly state and schedules a ready event if train is complete (and ready event is not after simulation
	end time), otherwise schedules another assembly event.
	*/
	void processEvent() override;
};

class ReadyEvent : public Event
{
public:
	ReadyEvent(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:Event(p_simulation, p_railway, p_time, p_train) {}
		
	/*
	Places train i ready state and schedules a departure event if departure is not after simulation
	end time.
	*/
	void processEvent() override;
};

class DepartureEvent : public Event
{
public:
	DepartureEvent(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:Event(p_simulation, p_railway, p_time, p_train) {}

	/*
	Places train i running state, calculates its speed and schedules an arrive event based on the speed.
	Train is removed from station and placed in railway companys data structure for running tra�ns.
	*/
	void processEvent() override;
};

class ArriveEvent : public Event
{
public:
	ArriveEvent(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:Event(p_simulation, p_railway, p_time, p_train) {}

	/*
	Places train i arrived state and schedules a finish event (disassembly).
	Train is removed from data structure for running tra�ns and placed in arrival stations datastructure for trains.
	*/
	void processEvent() override;
};

class FinishEvent : public Event
{
public:
	FinishEvent(Simulation *p_simulation, RailwayCompany *p_railway, Time &p_time, std::shared_ptr<Train> p_train)
		:Event(p_simulation, p_railway, p_time, p_train) {}

	/*
	Places train in finish state and disassembles the train. All vehicles are place in arrival stations vehicle pool.
	*/
	void processEvent() override;
};


#endif //!EVENT_H
