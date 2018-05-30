
#include <iostream>
#include <fstream>
#include <exception>
#include <tuple>
#include "RailwayCompany.h"


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


std::vector<std::shared_ptr<Vehicle>> RailwayCompany::getAllVehicles() const
{
	std::vector<std::shared_ptr<Vehicle>> allVehicles;
	for (const TrainStation &station : m_stations)
	{
		std::vector<std::shared_ptr<Vehicle>> vehicles = station.getAllVehicles();
		copy(vehicles.cbegin(), vehicles.cend(), std::back_inserter(allVehicles));
	}

	sort(allVehicles.begin(), allVehicles.end(), [](std::shared_ptr<Vehicle> a, std::shared_ptr<Vehicle> b) {
		return a->getId() < b->getId();
	});

	stable_sort(allVehicles.begin(), allVehicles.end(), [](std::shared_ptr<Vehicle> a, std::shared_ptr<Vehicle> b) {
		return a->getType() < b->getType();
	});  

	return allVehicles;
}

std::tuple<std::shared_ptr<Vehicle>, std::shared_ptr<Train>, TrainStation*> RailwayCompany::locateVehicle(const int id)
{
	std::shared_ptr<Vehicle> found;
	for (TrainStation &station : m_stations)  //search all stations
	{
		found = station.locateVehicle(id);
		if (found)
			return std::make_tuple(found, nullptr, &station);

		const std::vector<std::shared_ptr<Train>> mountedTrains = station.getTrains();
		for (std::shared_ptr<Train> train : mountedTrains)  //search all mounted trains on each station
		{
			found = train->locateVehicle(id);
			if (found)
				return std::make_tuple(found, train, nullptr);
		}
	}
	
	for (std::shared_ptr<Train> train : m_runningTrains)  //search all running trains
	{
		found = train->locateVehicle(id);
		if (found)
			return std::make_tuple(found, train, nullptr);
	}

	return { nullptr, nullptr, nullptr };  //vehicle does not exist
}

std::shared_ptr<Train> RailwayCompany::locateTrain(const int id)
{
	for (auto t : m_runningTrains)
	{
		if (t->getId() == id)
			return t;
	}
	for (auto s : m_stations)
	{
		std::shared_ptr<Train> train = s.locateTrain(id);
		if (train)
			return train;
	}

	return nullptr;
}

void RailwayCompany::placeInTransit(std::shared_ptr<Train> train)
{
	m_runningTrains.push_back(train);
}

void RailwayCompany::removeFromTransit(std::shared_ptr<Train> train)
{
	auto found = std::find_if(m_runningTrains.begin(), m_runningTrains.end(), [train](std::shared_ptr<Train> t) {
		return train == t;
	});

	if (found != m_runningTrains.end())
		m_runningTrains.erase(found);
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

std::vector<const TrainStation*> RailwayCompany::getAllStations() const
{
	std::vector<const TrainStation*> stationPtrs;
	for (const TrainStation &station : m_stations)
		stationPtrs.push_back(&station);

	return stationPtrs;
}

std::vector<std::string> RailwayCompany::getAllStationNames() const
{
	std::vector<std::string> names;
	for (auto &station : m_stations)
		names.push_back(station.getName());

	return names;
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
