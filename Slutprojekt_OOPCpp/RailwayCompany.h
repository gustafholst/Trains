

#ifndef RAILWAYCOMPANY_H
#define RAILWAYCOMPANY_H

#include <memory>
#include "TrainMap.h"
#include "TrainStation.h"
#include "Train.h"
#include "Route.h"
#include "auxilliary.h"
#include "Simulation.h"


class RailwayCompany
{
public:
	RailwayCompany() = default;

	void loadStations();
	void loadTimetable();
	void loadMap();

	std::vector<std::shared_ptr<Vehicle>> getAllVehicles() const;
	std::tuple<std::shared_ptr<Vehicle>, std::shared_ptr<Train>, TrainStation*> locateVehicle(const int id);
	std::shared_ptr<Train> locateTrain(const int id);

	std::shared_ptr<Vehicle> findVehicleType(TrainStation *station, VehicleType type) {    //const pointer!!!
		return station->findVehicle(type);
	}

	void placeInTransit(std::shared_ptr<Train> train);
	void removeFromTransit(std::shared_ptr<Train> train);

	int getDistance(const std::string &depStation, const std::string &arrStation) { return distance(depStation, arrStation); }

	TrainStation* getStation(std::string &sName);
	
	std::vector<const TrainStation*> getAllStations() const;
	std::vector<std::string> getAllStationNames() const;

	void printTimetable() {
		std::cout << "Timetable" << std::endl;
		for (auto &r : m_timetable)
			std::cout << r << std::endl;
	}

	void createTrains();
	//void scheduleTrains(Simulation *sim);             remove!!!!!

private:
	std::vector<TrainStation> m_stations;
	std::vector<Route> m_timetable;
	std::list<std::shared_ptr<Train>> m_runningTrains;
	TrainMap distance;   //functor
};

#endif // RAILWAYCOMPANY_H