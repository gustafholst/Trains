

#ifndef RAILWAYCOMPANY_H
#define RAILWAYCOMPANY_H

#include <memory>
#include "TrainMap.h"
#include "TrainStation.h"
#include "Train.h"
#include "Route.h"
#include "auxilliary.h"

void printVehicle(std::ostream &os, std::shared_ptr<const Vehicle> v);

class RailwayCompany
{
public:
	RailwayCompany();
	~RailwayCompany();

	void loadStations();
	void loadTimetable();
	void loadMap();

	std::tuple<std::shared_ptr<Vehicle>, std::shared_ptr<Train>, TrainStation*> locateVehicle(const int id);

	std::shared_ptr<Vehicle> findVehicleType() {
		return m_stations[4].findVehicle(VehicleType::ElectricEngine);
	}

	const TrainStation* getStation(std::string &sName)
	{
		for (auto &s : m_stations)
		{
			if (lowercase(s.getName() )== lowercase(sName))
				return &s;
		}
		
		return nullptr;
	}
	
	std::vector<std::string> getAllStationNames() {
		std::vector<std::string> names;
		for (auto &station : m_stations)
			names.push_back(station.getName());

		return names;
	}

	void printTimetable() {
		std::cout << "Timetable" << std::endl;
		for (auto &r : m_timetable)
			std::cout << r << std::endl;
	}

private:
	std::vector<TrainStation> m_stations;
	std::vector<Route> m_timetable;
	std::vector<std::shared_ptr<Train>> m_trainsInTraffic;
	TrainMap distance;   //functor
};

#endif // RAILWAYCOMPANY_H