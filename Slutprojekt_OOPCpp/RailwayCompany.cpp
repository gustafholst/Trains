
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
		}		
	}
	else {
		std::cout << "TrainStations.txt could not be opened" << std::endl;  //throw exception instead
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
		std::cout << "Trains.txt could not be opened" << std::endl;  //throw exception
}


std::tuple<std::shared_ptr<Vehicle>, std::shared_ptr<Train>, TrainStation*> RailwayCompany::locateVehicle(const int id)
{
	for (TrainStation &station : m_stations)  //search all stations
	{
		std::shared_ptr<Vehicle> found = station.locateVehicle(id);
		if (found != nullptr)
			return std::make_tuple(found, nullptr, &station);
	}
	for (std::shared_ptr<Train> train : m_trainsInTraffic)  //search all mounted trains
	{
		std::shared_ptr<Vehicle> found = train->locateVehicle(id);
		if (found != nullptr)
			return std::make_tuple(found, train, nullptr);
	}

	return { nullptr, nullptr, nullptr };  //vehicle does not exist
}
