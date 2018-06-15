/*
* Event.cpp
* Gustaf Holst, guho1700
* 2018-05-25
* v1.0
*
* Defines the Event class and all its subclasses.
*
*/

#include <cmath>
#include "Event.h"
#include "Simulation.h"
#include "RailwayCompany.h"
#include "TrainStation.h"

void printTrain(std::ostream &os, std::shared_ptr<const Train> v, LogLevel p_logLevel=LogLevel::NORMAL);

std::string Event::toString() const
{
	return m_statusStream.str();
}

std::ostream & operator<<(std::ostream & outstream, const Event & e)
{
	outstream << e.toString();    //call classmember toString in order to access m_statusStream
	return outstream;
}

void AssemblyEvent::processEvent()
{
	std::string stationName = m_train->getDepStation();
	TrainStation *station = m_railway->getStation(stationName);

	if (station->assembleTrain(m_train))
	{
		m_train->setState(TrainState::ASSEMBLED);
		Time newTime = m_time + ASSEMBLY_TIME;  // assembly takes 20 minutes
		if (newTime < m_simulation->getEndTime())   // do no schedule ready event after end time
		{
			std::shared_ptr<Event> nextEvent = std::make_shared<ReadyEvent>(m_simulation, m_railway, newTime, m_train);
			m_simulation->scheduleEvent(nextEvent);
			printTrain(m_statusStream, m_train);  //store current snapshot of train in status stream
			m_statusStream << std::endl << "now assembled, arriving to the platform at " + formatTime(newTime);
		}
		else
		{
			printTrain(m_statusStream, m_train);  //store current snapshot of train in status stream
			m_statusStream << std::endl << "now assembled, will not arrive at platform";
		}
	}
	else
	{
		m_train->setState(TrainState::INCOMPLETE);
		m_train->increaseDelay(RETRY_TIME);
		Time newTime = m_time + RETRY_TIME;  // next try in 10 minutes
		if (newTime < m_simulation->getEndTime())   // do not schedule new assembly after end time
		{
			std::shared_ptr<Event> nextEvent = std::make_shared<AssemblyEvent>(m_simulation, m_railway, newTime, m_train); 
			m_simulation->scheduleEvent(nextEvent);
			printTrain(m_statusStream, m_train);
			m_statusStream << std::endl << "now incomplete, next try at " + formatTime(newTime);
		}
		else
		{
			printTrain(m_statusStream, m_train);
			m_statusStream << std::endl << "now incomplete, no more tries";
		}
	}
}

void ReadyEvent::processEvent()
{
	m_train->setState(TrainState::READY);
	Time newTime = m_time + READY_TIME;    //train leaves in 10 minutes
	if (newTime < m_simulation->getEndTime())   // do not schedule new departure after end time
	{
		std::shared_ptr<Event> nextEvent = std::make_shared<DepartureEvent>(m_simulation, m_railway, newTime, m_train);
		m_simulation->scheduleEvent(nextEvent);
		printTrain(m_statusStream, m_train);
		m_statusStream << std::endl << "now ready, leaving station at " + formatTime(newTime);
	}
	else {
		printTrain(m_statusStream, m_train);
		m_statusStream << std::endl << "now ready, will not leave station";
	}
}

void DepartureEvent::processEvent()
{
	m_train->setState(TrainState::RUNNING);

	//get pointer to departure station
	std::string stationName = m_train->getDepStation();
	TrainStation * station = m_railway->getStation(stationName);

	//move train from station to running trains
	station->depart(m_train);   
	m_railway->placeInTransit(m_train);

	//calculate speed needed to arrive on time
	int distance = m_railway->getDistance(m_train->getDepStation(), m_train->getArrStation());   //km
	Time duration = m_train->getArrTime() - m_train->getActualDepTime();
	// if departure time is before arrival time 
	int approvedSpeed;
	if (duration > 0) 
	{
		int neededSpeed = static_cast<int>(std::round((distance / static_cast<float>(duration.getMins())) * 60));   // calculate with flotaing point for precision. km/min * 60 -> km/h
		approvedSpeed = m_train->setAvgSpeed(neededSpeed);  //setAvgSpeed returns the approved speed of specific train
	}
	else // train is very delayed
	{
		approvedSpeed = m_train->setAvgSpeed(m_train->getMaxSpeed());  // full speed ahead!
	}

	//calculate arrival time
	Time actualDuration = static_cast<int>(std::round((distance / static_cast<float>(approvedSpeed)) *60));  // km / (km/h) = h , h * 60 = minutes   using implicit conversion with constructor Time (int minutes)
	Time delay = (m_train->getActualDepTime() + actualDuration) - m_train->getArrTime();
	m_train->setDelay(delay);
	Time newTime = m_train->getActualDepTime() + actualDuration;  //time for arrival = time of departure + actual travel time

	//schedule next event
	std::shared_ptr<Event> nextEvent = std::make_shared<ArriveEvent>(m_simulation, m_railway, newTime, m_train);
	m_simulation->scheduleEvent(nextEvent);

	//store event info
	printTrain(m_statusStream, m_train);
	m_statusStream << std::endl << "has left the station, travelling at speed " + std::to_string(approvedSpeed) + " km/h (" + std::to_string(m_train->getMaxSpeed()) + ')';
}

void ArriveEvent::processEvent()
{
	m_train->setState(TrainState::ARRIVED);

	//get pointer to arrival station
	std::string stationName = m_train->getArrStation();
	TrainStation * station = m_railway->getStation(stationName);

	//move train from running trains to station
	m_railway->removeFromTransit(m_train);
	station->arrive(m_train);
	
	//calculate time for disassembly
	Time newTime = m_train->getActualArrTime() + DISASSEMBLY_TIME;   // start disassembly after 20 minutes 

	//schedule next event
	std::shared_ptr<Event> nextEvent = std::make_shared<FinishEvent>(m_simulation, m_railway, newTime, m_train);
	m_simulation->scheduleEvent(nextEvent);

	//store event info
	printTrain(m_statusStream, m_train);
	m_statusStream << std::endl << "has arrived at the platform, disassembly at " + formatTime(newTime);
}

void FinishEvent::processEvent()
{
	m_train->setState(TrainState::FINISHED);

	//get pointer to arrival station
	std::string stationName = m_train->getArrStation();
	TrainStation * station = m_railway->getStation(stationName);

	//decouple all vehicles
	while (true)
	{
		std::shared_ptr<Vehicle> vehicle = m_train->decoupleVehicle();
		if (!vehicle)
			break;

		station->parkVehicle(vehicle);
	}
		
	printTrain(m_statusStream, m_train);
	m_statusStream << std::endl << "is now disassembled";
}
