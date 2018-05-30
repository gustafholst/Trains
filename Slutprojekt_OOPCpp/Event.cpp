

#include "Event.h"
#include "Simulation.h"
#include "RailwayCompany.h"
#include "TrainStation.h"

void printTrain(std::ostream &os, std::shared_ptr<const Train> v, LogLevel p_logLevel);

Event::~Event()
{
}

std::string Event::toString() const
{
	/*std::ostringstream stream;
	printTrain(stream, m_train);
	stream << '\n' << m_statusString;*/
	//return stream.str();
	return m_statusStream.str();
}

std::ostream & operator<<(std::ostream & outstream, const Event & e)
{
	outstream << e.toString();
	return outstream;
}

void AssemblyEvent::processEvent()
{
	std::string stationName = m_train->getDepStation();
	TrainStation *station = m_railway->getStation(stationName);

	if (station->assembleTrain(m_train))
	{
		m_train->setState(TrainState::ASSEMBLED);
		Time newTime = m_time + 20;  // assembly takes 20 minutes
		if (newTime < m_simulation->getEndTime())   // do no schedule ready event after end time
		{
			std::shared_ptr<Event> nextEvent = std::make_shared<ReadyEvent>(m_simulation, m_railway, newTime, m_train);
			m_simulation->scheduleEvent(nextEvent);
			printTrain(m_statusStream, m_train, LogLevel::HIGH);  //store current snapshot of train in status stream
			m_statusStream << "\nnow assembled, arriving to the platform at " + formatTime(newTime);
		}
	}
	else
	{
		//if (m_train->getState() == TrainState::NOT_ASSEMBLED)
		//	m_simulation->incomplete();
		m_train->setState(TrainState::INCOMPLETE);
		m_train->increaseDelay(10);
		Time newTime = m_time + 10;  // next try in 10 minutes
		if (newTime < m_simulation->getEndTime())   // do not schedule new assembly after end time
		{
			std::shared_ptr<Event> nextEvent = std::make_shared<AssemblyEvent>(m_simulation, m_railway, newTime, m_train); 
			m_simulation->scheduleEvent(nextEvent);
			printTrain(m_statusStream, m_train, LogLevel::HIGH);
			m_statusStream << "\nnow incomplete, next try at " + formatTime(newTime);
		}
	}
}

void ReadyEvent::processEvent()
{
	m_train->setState(TrainState::READY);
	Time newTime = m_time + 10;    //train leaves in 10 minutes
	if (newTime < m_simulation->getEndTime())   // do not schedule new departure after end time
	{
		std::shared_ptr<Event> nextEvent = std::make_shared<DepartureEvent>(m_simulation, m_railway, newTime, m_train);
		m_simulation->scheduleEvent(nextEvent);
		printTrain(m_statusStream, m_train, LogLevel::HIGH);
		m_statusStream << "\nnow ready, leaving station at " + formatTime(newTime);
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

	if (m_train->getId() == 121)
		std::cout << "Gurra" << std::endl;

	//calculate speed
	int distance = m_railway->getDistance(m_train->getDepStation(), m_train->getArrStation());   //km
	Time duration = m_train->getArrTime() - m_train->getActualDepTime();
	// if departure time is before arrival time 
	int approvedSpeed;
	if (duration > 0) 
	{
		int neededSpeed = static_cast<int>((distance / static_cast<float>(duration.getMins())) * 60);   // calculate with flotaing point for precision. km/min * 60 -> km/h
		approvedSpeed = m_train->setAvgSpeed(neededSpeed);  //setAvgSpeed returns the approved speed of specific train
	}
	else // train is very delayed
	{
		approvedSpeed = m_train->setAvgSpeed(m_train->getMaxSpeed());  // full speed ahead!
	}

	//calculate arrival time
	Time actualDuration = static_cast<int>((distance / static_cast<float>(approvedSpeed)) *60);  // km / (km/h) = h , h * 60 = minutes   using implicit conversion with constructor Time (int minutes)
	Time delay = (m_train->getActualDepTime() + actualDuration) - m_train->getArrTime();
	m_train->setDelay(delay);
	Time newTime = m_train->getActualDepTime() + actualDuration;  //time for arrival = time of departure + actual travel time

	//schedule next event
	std::shared_ptr<Event> nextEvent = std::make_shared<ArriveEvent>(m_simulation, m_railway, newTime, m_train);
	m_simulation->scheduleEvent(nextEvent);

	//store event info
	printTrain(m_statusStream, m_train, LogLevel::HIGH);
	m_statusStream << "\nhas left the station, travelling at speed " + std::to_string(approvedSpeed) + " km/h (" + std::to_string(m_train->getMaxSpeed()) + ')';
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
	Time newTime = m_train->getActualArrTime() + 20;   // start disassembly after 20 minutes 

	//schedule next event
	std::shared_ptr<Event> nextEvent = std::make_shared<FinishEvent>(m_simulation, m_railway, newTime, m_train);
	m_simulation->scheduleEvent(nextEvent);

	//store event info
	printTrain(m_statusStream, m_train, LogLevel::HIGH);
	m_statusStream << "\nhas arrived at the platform, disassembly at " + formatTime(newTime);
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
		
	printTrain(m_statusStream, m_train, LogLevel::HIGH);
	m_statusStream << "\nis now disassembled";
}
