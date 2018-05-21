

#ifndef RAILWAYCOMPANY_H
#define RAILWAYCOMPANY_H

#include <memory>
#include "TrainStation.h"
#include "Train.h"
#include "Route.h"

class RailwayCompany
{
public:
	RailwayCompany();
	~RailwayCompany();

	void loadStations();
	void loadTimetable();

	std::tuple<std::shared_ptr<Vehicle>, std::shared_ptr<Train>, TrainStation*> locateVehicle(const int id);

	void printAllStationNames() {
		for (auto &s : m_stations)
			std::cout << s.getName() << std::endl;
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
};

#endif // RAILWAYCOMPANY_H