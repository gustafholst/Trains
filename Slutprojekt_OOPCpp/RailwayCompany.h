

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

	TrainStation* getStation(const std::string &sName);
	
	std::vector<const TrainStation*> getAllStations() const;
	std::vector<std::string> getAllStationNames() const;

	const std::vector<std::shared_ptr<Train>> getAllTrains() const;

	void printTimetable();
	std::vector<const Route*> getTimetable();
	void createTrains();

	void makeInitialVehicleInventory();
	const std::map<std::string, int> getInitialVehicleCount() const { return m_vehicleCount; }

private:
	std::vector<TrainStation> m_stations;
	std::vector<Route> m_timetable;
	std::list<std::shared_ptr<Train>> m_runningTrains;
	TrainMap distance;   //functor
	std::map<std::string, int> m_vehicleCount;   //keep track of how many vehicles are att the station at beginning of simulation
};

#endif // RAILWAYCOMPANY_H