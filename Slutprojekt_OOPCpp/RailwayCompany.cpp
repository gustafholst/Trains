
#include <iostream>
#include <fstream>
#include <exception>
#include <tuple>
#include "RailwayCompany.h"


RailwayCompany::RailwayCompany()
{
}


RailwayCompany::~RailwayCompany()
{
}

void RailwayCompany::loadStations()
{
	std::ifstream inFile("TrainStations.txt");
	if (inFile.is_open())
	{
		TrainStation tmpStation;
		while (inFile >> tmpStation) {
			m_stations.push_back(tmpStation);
			if (inFile.eof())
				break;

			tmpStation = TrainStation();   //reinitialize in order to clear vehicle vector
		}		
	}
	else {
		throw std::ios_base::failure("File 'Trainstations.txt' could not be opened");
	}
}

void RailwayCompany::loadTimetable()
{
	std::ifstream inFile("Trains.txt");

	if (inFile.is_open())
	{
		Route tmpRoute;
		while (inFile >> tmpRoute) {
			m_timetable.push_back(tmpRoute);
			if (inFile.eof())
				break;

			tmpRoute = Route();  //reinitialize in order to clear vehicle vector
		}
	}
	else
	{
		throw std::ios_base::failure("File 'Trains.txt' could not be opened");
	}
}

void RailwayCompany::loadMap()
{
	distance.readFromFile();
}


std::tuple<std::shared_ptr<Vehicle>, std::shared_ptr<Train>, TrainStation*> RailwayCompany::locateVehicle(const int id)
{
	for (TrainStation &station : m_stations)  //search all stations
	{
		std::shared_ptr<Vehicle> found = station.locateVehicle(id);
		if (found != nullptr)
			return std::make_tuple(found, nullptr, &station);
	}
	for (std::shared_ptr<Train> train : m_runningTrains)  //search all mounted trains
	{
		std::shared_ptr<Vehicle> found = train->locateVehicle(id);
		if (found != nullptr)
			return std::make_tuple(found, train, nullptr);
	}

	return { nullptr, nullptr, nullptr };  //vehicle does not exist
}

TrainStation * RailwayCompany::getStation(std::string & sName)
{
	for (TrainStation &s : m_stations)
	{
		if (lowercase(s.getName()) == lowercase(sName))
			return &s;
	}

	return nullptr;
}

std::vector<std::string> RailwayCompany::getAllStationNames() const
{
	std::vector<std::string> names;
	for (auto &station : m_stations)
		names.push_back(station.getName());

	return names;
}

void RailwayCompany::scheduleTrains(Simulation * sim)
{
	for (TrainStation &station : m_stations)
	{
		std::vector<std::shared_ptr<Train>> trains = station.getTrains();
		for (auto train : trains)
		{
			Time assemblyStart = train->getDepTime() - 30;
			std::shared_ptr<Event> newEvent = std::shared_ptr<Event>(new AssemblyEvent(sim, this, assemblyStart, train));
			sim->scheduleEvent(newEvent);
		}
	}
}

void RailwayCompany::createTrains()
{
	for (Route &route : m_timetable)
	{
		std::string stationName = route.getDepStation();
		TrainStation *station = getStation(stationName);
		station->addTrain(route);  //implicit conversion route -> train
	}
}
